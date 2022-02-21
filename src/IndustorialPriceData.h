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
#include "PriceData.h"
#include "IndustorialValue.h"

namespace Protra {
namespace Lib{
namespace Data {


class IndustorialPriceData
{
public:
    static std::shared_ptr<PriceList> GetPricesIndustory33(int ind)
    {
        std::shared_ptr<PriceList> ret;
        std::shared_ptr<std::vector<std::shared_ptr<Price> > > prices;
        IndustorialValueData ivd;
        std::vector<std::shared_ptr <IndustorialValue> > ivs;
        std::vector<std::shared_ptr<PriceList> > pls;
        std::shared_ptr<PriceList> tpl;
        std::vector<int> idx;

        prices = std::shared_ptr<std::vector<std::shared_ptr<Price> > >(new(std::vector<std::shared_ptr<Price> >));


        ivd.Load();
        ivs = ivd.IndustorialValue33(ind);
        if (ivs.size() == 0)return ret;

        for (int i = 0; i < ivs.size(); i++) {
            tpl=PriceData::GetPrices(ivs[i]->Code, TimeFrame::Daily);
            if (tpl == nullptr)return ret;
            pls.push_back(tpl);
        }
        int val = 0;
        for (int i = 0; i < ivs.size(); i++) {
            if(val<pls[i]->First()->Date.Value)val= pls[i]->First()->Date.Value;
            //printf("%d  %d\n", i, val);
        }
    restart:
        idx.clear();
        DateTime dt = DateTime(val);
        int fval = pls[0]->SearchByDate(dt);
        int lval=pls[0]->SearchByDate(pls[0]->Last()->Date);
        int ct = lval - fval+1;
        for (int i = 0; i < ivs.size(); i++) {
                int id = pls[i]->SearchByDate(dt);
                //printf("i=%d  idx=%d\n",i,id);
                idx.push_back(id);
        }
        FLOAT f;
        for (int i = 0; i < ct; i++) {
            dt = DateTime(fval+i);
            std::vector<std::shared_ptr < Price>> p;
            p.clear();
            for (int j = 0; j < ivs.size(); j++) {
                p.push_back(pls[j]->Price(i + idx[j]));
            }
            for (int j = 1; j < ivs.size(); j++) {
                if (p[0]->Date.Value != p[j]->Date.Value) {
                    prices->clear();
                    val = std::max(p[0]->Date.Value, p[j]->Date.Value);
                    goto restart;
                }
            }
            for (int j = 0; j < ivs.size(); j++) {
                //printf("%04d/%02d/%02d  code=%s  close=%f\n",
                //    p[j]->Date.Year, p[j]->Date.Month, p[j]->Date.Day,
                //    p[j]->Code.c_str(), (float)p[j]->Close);
                ivd.SetValue(ivs, p[j]->Code, p[j]->Close);
            }
            //printf("\n");
            f=ivd.GetIndex(ivs);
            std::shared_ptr<Price> o = std::shared_ptr<Price>(new Price);
            o->Close = f;
            o->Date = p[0]->Date;
            prices->push_back(o);
        }
        ret = std::shared_ptr<PriceList>(new PriceList(prices,TimeFrame::Daily));
        return ret;
    }


};


}
}
}



#endif
