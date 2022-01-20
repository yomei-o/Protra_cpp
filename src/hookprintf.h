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

#ifndef DF_HOOKPRINTF_H_
#define DF_HOOKPRINTF_H_

#include <stdio.h>
#include <stdarg.h>
#include <string>

namespace hookprintf
{


enum {
	NORMAL,
	HOOK,
	BOTH,
};


class config
{
public:
	static inline int& get_mode()
	{
		static int _mode = NORMAL;
		return _mode;
	}
	static inline std::string& get_buf()
	{
		static std::string _buf;
		return _buf;
	}
	static inline void start(int mode)
	{
		int& m=get_mode();
		m = mode;
		std::string& buf = get_buf();
		buf = "";
	}
	static inline int printf(const char* fmt,...)
	{
		int ret = 0;
		va_list ap;
		char buf[1024];
		va_start(ap, fmt);
		switch (get_mode()) {
		default:
			ret = vprintf(fmt, ap);
			break;
		case BOTH:
			ret = vprintf(fmt, ap);
			// no break
		case HOOK:
			ret=vsprintf(buf, fmt, ap);
			std::string& str = get_buf();
			str += buf;
			break;
		}
		va_end(ap);
		return ret;
	}
};



}




#define printf hookprintf::config::printf

#endif

