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

#ifndef DF_BASICBUILTIN_H_
#define DF_BASICBUILTIN_H_

#include "Builtins.h"
#include "BrandData.h"
#include "PriceData.h"
#include "Global.h"

namespace Protra {
namespace Lib {
namespace Lang {
namespace Builtins {

class BasicBuiltins:public Builtins{
public:
    std::shared_ptr<Protra::Lib::Data::PriceList> _prices;
    std::shared_ptr< Protra::Lib::Data::Brand> Brand;
    int Index;
    int RightIndex;

    std::map<std::string, std::shared_ptr<Protra::Lib::Data::PriceList> >_priceDataCache;
    std::map<std::string, int> _indexAdjustmentCache;

    BasicBuiltins()
    {
        Index = 0;
        RightIndex = 0;
    }

    std::shared_ptr<Protra::Lib::Data::PriceList> Prices(std::shared_ptr<Protra::Lib::Data::PriceList>value)
    {
        if (value != nullptr) {
            _prices = value;
            std::string code = _prices->First()->Code;
            Brand=Protra::Lib::GlobalEnv::BrandData()->Brand(code);
        }
        return _prices;
    }

    virtual std::shared_ptr<Value>  Invoke(std::string& name, std::vector<std::shared_ptr<Value> >& args, int at, std::string& ats)override
    {
        if (args.size() != 0) {
            return Builtins::Invoke(name, args, at, ats);
        }
        std::shared_ptr<Protra::Lib::Data::PriceList>prices = _prices;
        int index = Index;
        int rightIndex = RightIndex;
        std::shared_ptr< Protra::Lib::Data::Brand>brand = Brand;
        if (prices == nullptr) {
            throw std::runtime_error("BasicBuiltins prices is null");
        }
        if (Brand == nullptr) {
            throw std::runtime_error("BasicBuiltins Brand is null");
        }
        if (ats != "")
        {
            if (_priceDataCache[ats] != nullptr) {
                    _priceDataCache[ats] = Protra::Lib::Data::PriceData::GetPrices(ats, prices->TimeFrame);
            }
            prices = _priceDataCache[ats];
            if (prices == nullptr) {
                return std::shared_ptr<Value>(new Value());
            }
            if (_indexAdjustmentCache.count(ats)!=0)
            {
                index = Index + _indexAdjustmentCache[ats];
                if (index < 0 || index >= prices->Count() || prices->Price(index)->Date != _prices->Price(Index)->Date)
                {
                    _indexAdjustmentCache.erase(ats);
                }
            }
            if (_indexAdjustmentCache.count(ats)==0)
            {
                index = prices->SearchByDate(_prices->Price(Index)->Date);
                if (index < 0) {
                    return std::shared_ptr<Value>(new Value());
                }
                _indexAdjustmentCache[ats] = index - Index;
            }
            rightIndex = RightIndex + index - Index;
            brand = Protra::Lib::GlobalEnv::BrandData()->Brand(ats);
        }
        if (name == "Index") {
            return std::shared_ptr<Value>(new Value(index + at));
        }
        else if (name == "RightIndex") {
            return std::shared_ptr<Value>(new Value(rightIndex));
        }
        else if (name == "Code") {
            return std::shared_ptr<Value>(new Value(brand->Code));
        }
        else if (name == "Market") {
            return std::shared_ptr<Value>(new Value(brand->Market));
        }
        else if (name == "Unit") {
            return std::shared_ptr<Value>(new Value(brand->Unit));
        }
        if (index + at < 0 || index + at >= prices->Count()) {
            return std::shared_ptr<Value>(new Value());
        }
        std::shared_ptr< Protra::Lib::Data::Price>price;
        price= prices->Price(index + at);
        
        if (name == "Year") {
            return std::shared_ptr<Value>(new Value(price->Date.Year));
        }
        else if (name == "Month") {
            return std::shared_ptr<Value>(new Value(price->Date.Month));
        }
        else if (name == "Day") {
            return std::shared_ptr<Value>(new Value(price->Date.Day));
        }
        else if (name == "DayOfWeek") {
            return std::shared_ptr<Value>(new Value((int)price->Date.DayOfWeek));
        }
        else if (name == "Open") {
            return std::shared_ptr<Value>(new Value(price->Open));
        }
        else if (name == "High") {
            return std::shared_ptr<Value>(new Value(price->High));
        }
        else if (name == "Low") {
            return std::shared_ptr<Value>(new Value(price->Low));
        }
        else if (name == "Close") {
            return std::shared_ptr<Value>(new Value(price->Close));
        }
        else if (name == "Volume"){
            return std::shared_ptr<Value>(new Value(price->Volume));
        }
		return Builtins::Invoke(name, args, at, ats);
	}

	static std::shared_ptr<Protra::Lib::Lang::Builtins::Builtins> Init(std::shared_ptr<Builtins> btin)
	{
		std::vector<std::string> names;
        names.push_back("Index");
        names.push_back("RightIndex");
        names.push_back("Code");
        names.push_back("Market");
        names.push_back("Unit");
        names.push_back("Year");
        names.push_back("Month");
        names.push_back("Day");
        names.push_back("DayOfWeek");
        names.push_back("Open");
        names.push_back("High");
        names.push_back("Low");
        names.push_back("Close");
        names.push_back("Volume");
        
        std::shared_ptr<Protra::Lib::Lang::Builtins::Builtins> tobtin;
		tobtin = std::shared_ptr<Protra::Lib::Lang::Builtins::Builtins>(new BasicBuiltins());
		btin->Regist(names, tobtin);
		return tobtin;
	}

};



}
}
}
}

#endif

