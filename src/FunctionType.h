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

#ifndef DF_FUNCTIONTYPE_H_
#define DF_FUNCTIONTYPE_H_

#include <string>

namespace Protra {
namespace Lib {
namespace Lang {


class FunctionType
{
public:
	std::string _name;
	int _num;
	
	FunctionType()
	{
		_name = "";
		_num = 0;
	}
	FunctionType(std::string name, int num)
	{
		_name = name;
		_num = num;
	}
	FunctionType(const FunctionType& o)
	{
		_name = o._name;
		_num = o._num;
	}
	FunctionType& operator=(const FunctionType& o) 
	{
		_name = o._name;
		_num = o._num;
	}
		std::string Name()
	{
		return _name;
	}
	int ArgumentNum()
	{
		return _num;
	}
};


}
}
}

#endif


