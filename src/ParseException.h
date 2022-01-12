// Copyright (C) 2003, 2005 Daisuke Arai <darai@users.sourceforge.jp>
// Copyright (C) 2008, 2013 panacoran <panacoran@users.sourceforge.jp>
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

#ifndef DF_PARSEEXCEPTION_H_
#define DF_PARSEEXCEPTION_H_


#include <string>
#include <string.h>

#include "Token.h"

namespace Protra {
namespace Lib {
namespace Lang {


#ifdef PROTRA_LANG_IMPL
const char* ParseException(const char* msg, Token& token)
{
	static char buf[1024];
	sprintf(buf, "%s in %s: %d",msg,token.Filename.c_str(),token.LineNo );
	return buf;
}
#else
	const char* ParseException(const char* msg, Token& token);
#endif

}
}
}


#endif


