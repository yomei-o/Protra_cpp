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

#ifndef DF_REGISTERBUILTIN_H_
#define DF_REGISTERBUILTIN_H_

#include <map>
#include <string>
#include <vector>

#include "MathBuiltins.h"

namespace Protra {
namespace Lib {
namespace Lang {
namespace Builtins {

class RegisterBuiltins:public MathBuiltins{
public:
	std::map<std::string,std::shared_ptr<Builtins> > btmap;

	virtual std::shared_ptr<Value> Invoke(std::string& name, std::vector<std::shared_ptr<Value> >& args, int at, std::string& ats)override
	{
		std::shared_ptr<Builtins> tmp = btmap[name];
		if(tmp!=nullptr){
			std::shared_ptr<Value> val;
			val = tmp->Invoke(name, args, at, ats);
			return val;
		}
		return MathBuiltins::Invoke(name, args, at, ats);
	}
	virtual void Regist(std::vector<std::string>& names,std::shared_ptr<Builtins>& ptr)override
	{
		for (int i = 0; i < names.size(); i++) {
			btmap[names[i]]=ptr;
		}
	}
};


}
}
}
}
#endif

