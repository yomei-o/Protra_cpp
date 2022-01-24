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

#ifndef DF_BUILTIN_H_
#define DF_BUILTIN_H_

#include <memory>
#include <vector>
#include <string>
#include "Value.h"

namespace Protra {
namespace Lib {
namespace Lang {
namespace Builtins {

class Builtins{
public:
	virtual std::shared_ptr<Value>  Invoke(std::string& name, std::vector<std::shared_ptr<Value> >& args, int at, std::string& ats)
	{
		std::string msg = "No Such a Builtin " + name;
		throw std::runtime_error(msg.c_str());
		//return std::shared_ptr<Value>(new Value(false));
	}
	virtual void Regist(std::vector<std::string>& names, std::shared_ptr<Builtins>& ptr) 
	{

	}
};


}
}
}
}
#endif


