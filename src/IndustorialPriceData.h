// Copyright (C) 2022 Yomei Otani <yomei.otani@gmail.com>
// Copyright(C) 2010, 2013, 2014 panacoran <panacoran@users.sourceforge.jp>
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
// $Id: PriceData.cs 550 2021-01-10 05:21:56Z darai $

#ifndef DF_INDUSTORIALPRICEDATA_H_
#define DF_INDUSTORIALPRICEDATA_H_

#include <string>
#include <algorithm>
#include "PriceData.h"
#include "IndustorialValue.h"

namespace Protra {
namespace Lib{
namespace Data {


class IndustorialPriceData
{
public:
    static FLOAT bai33(int idx){
        FLOAT ret = 1;
        switch (idx) {
        case 10:
        case 11:
        case 27:
        case 28:
        case 29:
        case 30:
        case 31:
        case 32:
            ret = 10;
            break;
        }
        return ret;
    }
    static FLOAT bai17(int idx) {
        FLOAT ret = 1;
        return ret;
    }
    static std::shared_ptr<PriceList> GetPricesIndustory33(int ind)
    {
        std::shared_ptr<PriceList> ret;
        std::shared_ptr<std::vector<std::shared_ptr<Price> > > prices;
        IndustorialValueData ivd;
        std::vector<std::shared_ptr <IndustorialValue> > ivs;
        std::vector<std::shared_ptr<PriceList> > pls;
        std::shared_ptr<PriceList> tpl;

        std::map<int, int> days;
        std::vector<int> sort_days;

        prices = std::shared_ptr<std::vector<std::shared_ptr<Price> > >(new(std::vector<std::shared_ptr<Price> >));

        std::shared_ptr<Protra::Lib::Data::BrandData>& bd = Protra::Lib::GlobalEnv::BrandData();
        if (bd == nullptr) {
            bd = std::shared_ptr<Protra::Lib::Data::BrandData>(new Protra::Lib::Data::BrandData());
            bd->Load();
        }
        if (bd->_data.size() == 0) {
            printf("BranData file cannot open!!\n");
            return ret;
        }

        ivd.Load();
        ivs = ivd.IndustorialValue33(ind);
        if (ivs.size() == 0)return ret;

        for (int i = 0; i < ivs.size(); i++) {
            //ivs[i]->Print();
        }

        for (int i = 0; i < ivs.size(); i++) {
            tpl=PriceData::GetPrices(ivs[i]->Code, TimeFrame::Daily);
            if (tpl == nullptr)return ret;
            pls.push_back(tpl);
        }
        for (int i = 0; i < ivs.size(); i++) {
            for (int j = 0; j < pls[i]->Count();j++) {
                days[pls[i]->Price(j)->Date.Value] = 1;
            }
        }
        for (auto iter = days.begin(); iter != days.end(); ++iter) {
            sort_days.push_back(iter->first);
        }
        std::sort(sort_days.begin(), sort_days.end());
        for (int i = 0; i < sort_days.size(); i++) {
            DateTime t(sort_days[i]);
            //printf("%04d/%02d/%02d\n",t.Year,t.Month,t.Day);
        }

        FLOAT f;
        DateTime dt;
        std::shared_ptr < Price> p;
        std::vector<int> idx;
        for (int i = 0; i < ivs.size(); i++) {
            idx.push_back(0);
        }
        for (int i = 0; i < sort_days.size(); i++) {
            ivd.ClearValue(ivs);
            dt = DateTime(sort_days[i]);
            for (int j = 0; j < ivs.size(); j++) {
                p = pls[j]->Price(idx[j]);
                if (p == nullptr)continue;
                if (p->Date.Value != dt.Value)continue;
                ivd.SetValue(ivs, p->Code, p->Close);
                idx[j]++;
            }
            f = ivd.GetIndex(ivs)*bai33(ind);
            std::shared_ptr<Price> o = std::shared_ptr<Price>(new Price);
            o->Close = f;
            o->Date = dt;
            prices->push_back(o);
        }
        ret = std::shared_ptr<PriceList>(new PriceList(prices,TimeFrame::Daily));
        return ret;
    }

    static std::shared_ptr<PriceList> GetPricesIndustory17(int ind)
    {
        std::shared_ptr<PriceList> ret;
        std::shared_ptr<std::vector<std::shared_ptr<Price> > > prices;
        IndustorialValueData ivd;
        std::vector<std::shared_ptr <IndustorialValue> > ivs;
        std::vector<std::shared_ptr<PriceList> > pls;
        std::shared_ptr<PriceList> tpl;

        std::map<int, int> days;
        std::vector<int> sort_days;

        prices = std::shared_ptr<std::vector<std::shared_ptr<Price> > >(new(std::vector<std::shared_ptr<Price> >));

        std::shared_ptr<Protra::Lib::Data::BrandData>& bd = Protra::Lib::GlobalEnv::BrandData();
        if (bd == nullptr) {
            bd = std::shared_ptr<Protra::Lib::Data::BrandData>(new Protra::Lib::Data::BrandData());
            bd->Load();
        }
        if (bd->_data.size() == 0) {
            printf("BranData file cannot open!!\n");
            return ret;
        }

        ivd.Load();
        ivs = ivd.IndustorialValue17(ind);
        if (ivs.size() == 0)return ret;

        for (int i = 0; i < ivs.size(); i++) {
            //ivs[i]->Print();
        }

        for (int i = 0; i < ivs.size(); i++) {
            tpl = PriceData::GetPrices(ivs[i]->Code, TimeFrame::Daily);
            if (tpl == nullptr)return ret;
            pls.push_back(tpl);
        }
        for (int i = 0; i < ivs.size(); i++) {
            for (int j = 0; j < pls[i]->Count(); j++) {
                days[pls[i]->Price(j)->Date.Value] = 1;
            }
        }
        for (auto iter = days.begin(); iter != days.end(); ++iter) {
            sort_days.push_back(iter->first);
        }
        std::sort(sort_days.begin(), sort_days.end());
        for (int i = 0; i < sort_days.size(); i++) {
            DateTime t(sort_days[i]);
            //printf("%04d/%02d/%02d\n",t.Year,t.Month,t.Day);
        }

        FLOAT f;
        DateTime dt;
        std::shared_ptr < Price> p;
        std::vector<int> idx;
        for (int i = 0; i < ivs.size(); i++) {
            idx.push_back(0);
        }
        for (int i = 0; i < sort_days.size(); i++) {
            ivd.ClearValue(ivs);
            dt = DateTime(sort_days[i]);
            for (int j = 0; j < ivs.size(); j++) {
                p = pls[j]->Price(idx[j]);
                if (p == nullptr)continue;
                if (p->Date.Value != dt.Value)continue;
                ivd.SetValue(ivs, p->Code, p->Close);
                idx[j]++;
            }
            f = ivd.GetIndex(ivs) * bai17(ind);
            std::shared_ptr<Price> o = std::shared_ptr<Price>(new Price);
            o->Close = f;
            o->Date = dt;
            prices->push_back(o);
        }
        ret = std::shared_ptr<PriceList>(new PriceList(prices, TimeFrame::Daily));
        return ret;
    }

};


}
}
}



#endif
