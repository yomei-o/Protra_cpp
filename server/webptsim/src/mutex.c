// Copyright (C) 2022 Yomei Otani <yomei.otani@gmail.com>
// 
// This program is part of Protra.
//
// Protra is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
// 

#ifdef _MSC_VER
#if _MSC_VER >= 1400
#pragma warning( disable : 4996 )
#pragma warning( disable : 4819 )
#endif
#endif


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(_WIN32) || defined(__CYGWIN__)
#include <windows.h>
#include <winbase.h>
#endif

#if defined(unix) && !defined(__CYGWIN__)
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/fcntl.h>
#include <sys/file.h>
#include <errno.h>
#include <unistd.h>
#endif

#include "mutex.h"

mutex_t create_mutex(char *name)
{
#if defined(unix) && !defined(__CYGWIN__)
	void* fd;
	char tmp[1024];
#endif

	if(name==NULL)return NULL;

#if defined(unix) && !defined(__CYGWIN__)
	strcpy(tmp,"/win32mutex_");
	strcat(tmp,name);
#endif

#if defined(unix) && !defined(__CYGWIN__)
	fd=(void*)shm_open(tmp,O_CREAT | O_RDWR,0666);
	if((int)fd==-1)return NULL;
	return fd;
#endif

#if defined(_WIN32) || defined(__CYGWIN__)
	return CreateMutexA(NULL,FALSE,name);
#endif

	return NULL;
}



void close_mutex(mutex_t vp)
{
	if(vp==NULL)return;
#if defined(unix) && !defined(__CYGWIN__)
	close((int)vp);
#endif
#if defined(_WIN32) || defined(__CYGWIN__)
	CloseHandle((HANDLE)vp);
#endif
	return;
}



void  get_mutex(mutex_t vp)
{
	if(vp==NULL)return;

#if defined(unix) && !defined(__CYGWIN__)
	flock((int)vp,LOCK_EX);
#endif	
#if defined(_WIN32) || defined(__CYGWIN__)
	WaitForSingleObject((HANDLE)vp,INFINITE);
#endif
}

void release_mutex(mutex_t vp)
{
	if(vp==NULL)return;
#if defined(unix) && !defined(__CYGWIN__)
	flock((int)vp,LOCK_UN);
#endif	
#if defined(_WIN32) || defined(__CYGWIN__)
	ReleaseMutex((HANDLE)vp);
#endif
}


void sleep_mutex(int s)
{
#if defined(_WIN32) || defined(__CYGWIN__)
	Sleep(s*1000);
#endif
#if defined(unix) && !defined(__CYGWIN__)
	sleep(s);
#endif
}


int is_signal_mutex(mutex_t vp)
{
	int ret;

	if(vp==NULL)return 0;

#if defined(unix) && !defined(__CYGWIN__)
	ret=flock((int)vp,LOCK_EX | LOCK_NB);
	if(ret!=0)
	{
		return 0;
	}
	flock((int)vp,LOCK_UN);
	return 1;
#endif	
#if defined(_WIN32) || defined(__CYGWIN__)
	ret=WaitForSingleObject((HANDLE)vp,0);
	if(ret!=WAIT_TIMEOUT)
	{
		ReleaseMutex((HANDLE)vp);
		return 1;
	}
#endif
	return 0;
}


/*

テストコード

*/


#if 0

int main(int argc,char *argv[])
{
	void *h=NULL;
	char* fname="mutextest";
	int ret;

	h=create_mutex(fname);
	if(h==NULL)
	{
		printf("fail to create mutex!!\n");
		return 0;
	}
	ret=is_signal_mutex(h);
	printf("is_signal_mutex=%d\n",ret);
	get_mutex(h);
	printf("got mutex\n");

	sleep_mutex(10);

	printf("released mutex\n");
	release_mutex(h);

	close_mutex(h);
	return 1;
}


#endif
