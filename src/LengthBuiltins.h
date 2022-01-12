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

#ifndef DF_LENGTHBUILTIN_H_
#define DF_LENGTHBUILTIN_H_

#include "Builtins.h"

namespace Protra {
namespace Lib {
namespace Lang {
namespace Builtins {

class LengthBuiltins:public Builtins{
public:
	virtual std::shared_ptr<Value>  Invoke(std::string& name, std::vector<std::shared_ptr<Value> >& args, int at, std::string& ats)override
	{
		if (name == "Length" && args.size()==1) {
			std::shared_ptr<Value> val = args[0];
			Value* p = val.get();
			int len = p->Length();
			return std::shared_ptr<Value>(new Value(len));
		}
		return Builtins::Invoke(name, args, at, ats);
	}
};


}
}
}
}
#endif

