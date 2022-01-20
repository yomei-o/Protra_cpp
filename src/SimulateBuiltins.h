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
    std::shared_ptr < Protra::Lib::Data::Brand> Brand;
    std::shared_ptr<Protra::Lib::Data::PriceList> _prices;
    int Index;

    std::string System;
    std::shared_ptr <Protra::Lib::Config::BrandList> BrandList;
	std::shared_ptr<Protra::Lib::Data::LogData> LogData;

    SimulateBuiltins()
    {
        Index=0;
    }
    std::shared_ptr<Protra::Lib::Data::PriceList> Prices(std::shared_ptr<Protra::Lib::Data::PriceList>value)
    {
        if (value != nullptr) {
            _prices = value;
            std::string code = _prices->First()->Code;
            Brand = Protra::Lib::GlobalEnv::BrandData()->Brand(code);
        }
        return _prices;
    }

    virtual std::shared_ptr<Value>  Invoke(std::string& name, std::vector<std::shared_ptr<Value> >& args, int at, std::string& ats)override
    {
        if (args.size() == 0)
        {
            if (name == "CodeList") {
                std::shared_ptr<Value>codeList = std::shared_ptr<Value>(new Value(ValueType::Int, (int)BrandList->List->size()));
                for (int i = 0; i < codeList->Length(); i++) {
                    codeList->ArrayValue->at(i) = std::shared_ptr<Value>(new Value(BrandList->List->at(i)));
                }
                return codeList;
            }
            return Builtins::Invoke(name, args, at, ats);
        }
        std::shared_ptr < Protra::Lib::Data::Brand>brand = Brand;

        if (ats != "")
        {
            if (GlobalEnv::BrandData()->Brand(ats) == nullptr) {
                std::string msg = "missing brand code " + ats;
                throw std::runtime_error(RuntimeException(msg.c_str()));
            }
            brand = GlobalEnv::BrandData()->Brand(ats);
        }

        std::string msg;
        if (args.size() == 1)
        {
            std::string prefix = "";
            if (name == "PrintLog") {
                prefix = brand->Code;
                prefix += " ";
                prefix += brand->Name;
                prefix += " ";

                char tmp[128];
                Protra::Lib::Data::DateTime d=_prices->Price(Index + at)->Date;
                sprintf(tmp,"%02d/%02d/%02d", d.Year%100,d.Month,d.Day);

                prefix += tmp;
                prefix += " ";
            }
            else {
                return Builtins::Invoke(name, args, at, ats);
            }
            if (args[0]->ValueType == ValueType::Null) {
                msg = "null";
            }
            else if (args[0]->ValueType == ValueType::Array) {
                std::string msg = "wrong type argument for " + name + "(1)";
                throw std::runtime_error(RuntimeException(msg.c_str()));
            }
            else {
                msg = args[0]->toString();
            }
            msg = prefix + msg;
            printf("%s\n", msg.c_str());
            return std::shared_ptr<Value>(new Value());
        }
        if (args.size() != 2) {
            return Builtins::Invoke(name, args, at, ats);
        }
        std::shared_ptr<Protra::Lib::Data::Log> log;
        log= std::shared_ptr<Protra::Lib::Data::Log>(new Protra::Lib::Data::Log);
        log->Date = _prices->Price(Index + at)->Date;
        log->Code = brand->Code;
        log->Price = args[0]->toInt();
        log->Quantity = args[1]->toInt();
        log->Name = brand->Name;
        //TODO
        msg = "";
        msg += brand->Code;
        msg += " ";
        msg += brand->Name;
        msg += " ";
        
        char tmp[128];
        Protra::Lib::Data::DateTime d = log->Date;
        sprintf(tmp, "%02d/%02d/%02d", d.Year % 100, d.Month, d.Day);

        msg += tmp;
        msg += " ";

        sprintf(tmp,"%d円 %d株",log->Price, log->Quantity);
        msg += tmp;
        msg += " ";

        if (name == "Buy") {
            log->Order = Protra::Lib::Data::Order::Buy;
            if (!LogData->Add(log)) {
                throw std::runtime_error("同日の売買があります。");
            }
            msg += "買";
        }
        else if (name == "Sell") {
            log->Order = Protra::Lib::Data::Order::Sell;
            if (!LogData->Add(log)) {
                throw std::runtime_error("同日の売買があります。");
            }
            msg += "売";
        }
        else {
            return Builtins::Invoke(name, args, at, ats);
        }
        printf("%s\n",msg.c_str());
        return std::shared_ptr<Value>(new Value());
	}

	static std::shared_ptr<Protra::Lib::Lang::Builtins::Builtins> Init(std::shared_ptr<Builtins> btin)
	{
		std::vector<std::string> names;
        names.push_back("Buy");
        names.push_back("Sell");
        names.push_back("CodeList");
        names.push_back("PrintLog");

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

