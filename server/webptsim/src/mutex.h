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


#ifndef __MUTEX_H__
#define __MUTEX_H__



#ifdef __cplusplus
extern "C"
{
#endif

typedef void* mutex_t;

mutex_t create_mutex(char *name);
void close_mutex(mutex_t vp);
void  get_mutex(mutex_t vp);
void release_mutex(mutex_t vp);
void sleep_mutex(int s);
int is_signal_mutex(mutex_t vp);

#ifdef __cplusplus
}
#endif


#endif /* __MUTEX_H__ */

