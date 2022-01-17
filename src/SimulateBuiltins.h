// Copyright (C) 2022 Yomei Otani <yomei.otani@gmail.com>
// Copyright (C) 2008, 2013 panacoran <panacoran@users.sourceforge.jp>
// Copyright (C) 2011 Daisuke Arai <darai@users.sourceforge.jp>
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

#ifndef DF_SIMULATEBUILTIN_H_
#define DF_SIMULATEBUILTIN_H_

#include "Builtins.h"
#include "BrandData.h"
#include "PriceData.h"
#include "Global.h"
#include "LogData.h"

namespace Protra {
namespace Lib {
namespace Lang {
namespace Builtins {

class SimulateBuiltins:public Builtins{
public:
    std::string System;
    std::shared_ptr <Protra::Lib::Config::BrandList> BrandList;
	std::shared_ptr<Protra::Lib::Data::LogData> LogData;

    virtual std::shared_ptr<Value>  Invoke(std::string& name, std::vector<std::shared_ptr<Value> >& args, int at, std::string& ats)override
    {
        return std::shared_ptr<Value>(new Value());
		return Builtins::Invoke(name, args, at, ats);
	}

	static std::shared_ptr<Protra::Lib::Lang::Builtins::Builtins> Init(std::shared_ptr<Builtins> btin)
	{
		std::vector<std::string> names;
        names.push_back("Buy");
        names.push_back("Sell");
        
        std::shared_ptr<Protra::Lib::Lang::Builtins::Builtins> tobtin;
		tobtin = std::shared_ptr<Protra::Lib::Lang::Builtins::Builtins>(new SimulateBuiltins());
		btin->Regist(names, tobtin);
		return tobtin;
	}

};



}
}
}
}

#endif

