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

#ifndef DF_INDUSTORIALVALUE_H_
#define DF_INDUSTORIALVALUE_H_

#include<stdio.h>
#include<time.h>
#include<string>
#include<vector>
#include<memory>
#include<map>

#include"Industory.h"
#include"MarketValue.h"
#include"EndOfMonth.h"
#include"TopixWait.h"
#include"MarketValueConfig.h"

namespace Protra {
namespace Lib {
namespace Data {

class IndustorialValue {
public:
    std::string Code;
    FLOAT IndRefCapital;
    FLOAT FloatStock;
    FLOAT Capital;
    FLOAT Close;
    IndustorialValue()
    {
        Close = 0;
        IndRefCapital = 0;
        FloatStock = 0;
        Capital = 0;
    }
    void Print()
    {
        printf("Code=%s\n",Code.c_str());
        printf("IndRefCapital=%g\n", IndRefCapital);
        printf("FloatStock=%g\n", FloatStock);
        printf("Close=%f\n", Close);
        printf("Capital=%g\n", Capital);
        printf("\n");
    }
};


class IndustorialValueData {
public:
    IndustoryData ind;
    MarketValueData mvd;
    TopixWaitData twd;
    EndOfMonthData emd;

    void Load()
    {
        ind.Load();
        mvd.Load();
        twd.Load();
        emd.Load();
    }
    std::vector<std::shared_ptr<class IndustorialValue> > IndustorialValue33(int idx) {
        std::vector<std::shared_ptr<class IndustorialValue> > ret;
        std::vector<std::shared_ptr<class Industory> > id;
        std::shared_ptr<class TopixWait> tw;
        std::vector<std::shared_ptr<class TopixWait>> tws;
        std::shared_ptr<class MarketValue> mv;
        std::vector<FLOAT> k;
        std::shared_ptr<class IndustorialValue> iv;
        id = ind.Industory33(idx);
        if (id.size()==0)return ret;
        for (int i = 0; i < id.size(); i++) {
            tw = twd.Code(id[i]->Code);
            if (tw == nullptr)continue;
            //tw->Print();
            tws.push_back(tw);
        }
        if (tws.size() == 0)return ret;
        mv=mvd.Industory33(idx);
        if (mv == nullptr)return ret;
        
        FLOAT keisu=0,t;
        for (int i = 0; i < tws.size(); i++) {
            keisu += tws[i]->Wait;
        }
        for (int i = 0; i < tws.size(); i++) {
            t=tws[i]->Wait/keisu;
            k.push_back(t);

        }
        for (int i = 0; i < tws.size(); i++) {
            std::shared_ptr<EndOfMonth> em = emd.Code(tws[i]->Code);
            if (em == nullptr) {
                ret.clear();
                break;
            }
            iv = std::shared_ptr<class IndustorialValue>(new IndustorialValue());
            iv->Code = tws[i]->Code;
            iv->IndRefCapital = mv->RefCapital;
            iv->FloatStock = mv->Capital * k[i] / em->Close;
            ret.push_back(iv);
        }
        return ret;
    }
    std::vector<std::shared_ptr<class IndustorialValue> > IndustorialValue17(int idx) {
        std::vector<std::shared_ptr<class IndustorialValue> > ret;
        std::vector<std::shared_ptr<class Industory> > id;
        std::shared_ptr<class TopixWait> tw;
        std::vector<std::shared_ptr<class TopixWait>> tws;
        std::shared_ptr<class MarketValue> mv;
        std::vector<FLOAT> k;
        std::shared_ptr<class IndustorialValue> iv;
        id = ind.Industory17(idx);
        if (id.size() == 0)return ret;
        for (int i = 0; i < id.size(); i++) {
            tw = twd.Code(id[i]->Code);
            if (tw == nullptr)continue;
            //tw->Print();
            tws.push_back(tw);
        }
        if (tws.size() == 0)return ret;
        mv = mvd.Industory17(idx);
        if (mv == nullptr)return ret;

        FLOAT keisu = 0, t;
        for (int i = 0; i < tws.size(); i++) {
            keisu += tws[i]->Wait;
        }
        for (int i = 0; i < tws.size(); i++) {
            t = tws[i]->Wait / keisu;
            k.push_back(t);

        }
        for (int i = 0; i < tws.size(); i++) {
            std::shared_ptr<EndOfMonth> em = emd.Code(tws[i]->Code);
            if (em == nullptr) {
                ret.clear();
                break;
            }
            iv = std::shared_ptr<class IndustorialValue>(new IndustorialValue());
            iv->Code = tws[i]->Code;
            iv->IndRefCapital = mv->RefCapital;
            iv->FloatStock = mv->Capital * k[i] / em->Close;
            ret.push_back(iv);
        }
        return ret;
    }
    static int SetValue(std::vector<std::shared_ptr<class IndustorialValue> >& ivs, std::string code, FLOAT val)
    {
        int ret = -1;
        for (int i = 0; i < ivs.size(); i++) {
            if (ivs[i]->Code == code) {
                ivs[i]->Close = val;
                ivs[i]->Capital = ivs[i]->FloatStock * ivs[i]->Close;
                return 0;
            }
        }
        return ret;
    }
    static FLOAT GetCapital(std::vector<std::shared_ptr<class IndustorialValue> >& ivs)
    {
        FLOAT ret = 0;
        for (int i = 0; i < ivs.size(); i++) {
            ret += ivs[i]->Capital;
        }
        return ret;
    }
    static FLOAT GetRefCapital(std::vector<std::shared_ptr<class IndustorialValue> >& ivs)
    {
        FLOAT ret = 0;
        if (ivs.size() < 1)return ret;
        ret = ivs[0]->IndRefCapital;
        return ret;
    }
    static FLOAT GetIndex(std::vector<std::shared_ptr<class IndustorialValue> >& ivs)
    {
        FLOAT ret = 0;
        ret = GetCapital(ivs) / GetRefCapital(ivs) * 100;
        return ret;
    }
};

}
}
}

#endif

