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

#ifndef DF_DUMMYBUILTIN_H_
#define DF_DUMMYBUILTIN_H_

#include "Builtins.h"

namespace Protra {
namespace Lib {
namespace Lang {
namespace Builtins {

class DummyBuiltins:public Builtins{
public:
	virtual std::shared_ptr<Value>  Invoke(std::string& name, std::vector<std::shared_ptr<Value> >& args, int at, std::string& ats)override
	{
		if (name == "Hello" && args.size()==0) {
			//std::shared_ptr<Value> val = args[0];
			printf("Hello\n");
			return std::shared_ptr<Value>(new Value());
		}
		return Builtins::Invoke(name, args, at, ats);
	}

	static std::shared_ptr<Protra::Lib::Lang::Builtins::Builtins> Init(std::shared_ptr<Builtins> btin)
	{
		std::vector<std::string> names;
		names.push_back("Hello");
		std::shared_ptr<Protra::Lib::Lang::Builtins::Builtins> tobtin;
		tobtin = std::shared_ptr<Protra::Lib::Lang::Builtins::Builtins>(new DummyBuiltins());
		btin->Regist(names, tobtin);
		return tobtin;
	}

};



}
}
}
}

#endif

