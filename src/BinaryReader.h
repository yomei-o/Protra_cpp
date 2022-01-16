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

#ifndef DF_BINARYREADER_H_
#define DF_BINARYREADER_H_

#include <stdio.h>
#include <string.h>
#include <string>

#include "zengoopen.h"

class BinaryReader {
public:
	BinaryReader()
	{
		fp = NULL;
		len = 0;
	}
	virtual ~BinaryReader()
	{
		Close();
	}
	BinaryReader(const char* nm)
	{
		fp = NULL;
		len = 0;
		filename = nm;
	}
	BinaryReader(std::string& nm)
	{
		fp = NULL;
		len = 0;
		filename = nm;
	}
	void Close()
	{
		if (fp)fclose(fp);
		fp = NULL;
	}
	int isExist()
	{
		if (fp)return true;
		fp=zengo_price_open(filename.c_str(),"rb","data");
		if (fp) {
			fseek(fp, 0, SEEK_END);
			len=ftell(fp);
			fseek(fp, 0, SEEK_SET);
			return true;
		}
		return false;
	}
	void Seek(int pos)
	{
		isExist();
		if (fp) {
			fseek(fp, pos, SEEK_SET);
		}
	}
	int Length()
	{
		isExist();
		return len;
	}
	int Position()
	{
		isExist();
		if (fp == NULL)return -1;
		return (int)ftell(fp);
	}
	int ReadInt32() {
		unsigned char buf[4];
		int ret = -1;
		int sz;
		if(fp==NULL)return ret;
		sz=(int)fread(buf, 1, 4, fp);
		if (sz < 4)return ret;
		ret = 0;
		ret |= buf[3];
		ret <<= 8;
		ret |= buf[2];
		ret <<= 8;
		ret |= buf[1];
		ret <<= 8;
		ret |= buf[0];
		return ret;
	}
	double ReadDouble() {
		unsigned char buf[8];
		double  ret = -1;
		long long t;
		int sz;
		if (fp == NULL)return ret;
		sz = (int)fread(buf, 1, 8, fp);
		if (sz < 8)return ret;
		t = 0;
		t |= buf[7];
		t <<= 8;
		t |= buf[6];
		t <<= 8;
		t |= buf[5];
		t <<= 8;
		t |= buf[4];
		t <<= 8;
		t |= buf[3];
		t <<= 8;
		t |= buf[2];
		t <<= 8;
		t |= buf[1];
		t <<= 8;
		t |= buf[0];
		ret=*((double*)&t);
		return ret;
	}

private:
	FILE* fp;
	std::string filename;
	int len;
};


#endif

