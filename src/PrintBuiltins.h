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

#ifndef DF_PRINTBUILTIN_H_
#define DF_PRINTBUILTIN_H_

#include "LengthBuiltins.h"

namespace Protra {
namespace Lib {
namespace Lang {
namespace Builtins {

class PrintBuiltins:public LengthBuiltins{
public:
	virtual std::shared_ptr<Value>  Invoke(std::string& name, std::vector<std::shared_ptr<Value> >& args, int at, std::string& ats)override
	{
		if (name == "Print" && args.size()==1) {
			std::shared_ptr<Value> val = args[0];
			Value* p = val.get();
			printf("%s\n",p->toString().c_str());
			return std::shared_ptr<Value>(new Value());
		}
		return LengthBuiltins::Invoke(name, args, at, ats);
	}
};


}
}
}
}
#endif


