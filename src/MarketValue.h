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

#ifndef DF_MARKETVALUE_H_
#define DF_MARKETVALUE_H_

#include<stdio.h>
#include<time.h>
#include<string>
#include<vector>
#include<memory>
#include<map>

#include"StreamReader.h"
#include"splitreplace.h"

namespace Protra {
namespace Lib {
namespace Data {

class MarketValue {
public:
    std::string Name;
    std::string Date;
    int NumBrand;
    double Capital;
    double RefCapital;
    MarketValue()
    {
        RefCapital = 0;
        Capital = 0;
        NumBrand = 0;
    }
    void Print()
    {
        printf("Name=%s\n",Name.c_str());
        printf("NumBrand=%d\n",NumBrand);
        printf("Capitalization=%f\n",Capital);
        printf("Reference Capitalization=%f\n", RefCapital);
        printf("\n");
    }
};


class MarketValueData {
public:
    std::vector<std::shared_ptr<class MarketValue> > _data;
    std::string _dataFile = "marketvalues_202112.csv";
    void Load()
    {
        char buf[256];
        _data.clear();
        std::shared_ptr<class MarketValue> mv;
        try {
            StreamReader reader(_dataFile);
            std::string line;
            reader.ReadLine();
            while ((line = reader.ReadLine()) != "")
            {
                std::vector<std::string>entries = split(line, ",");
                if (entries.size() < 6)continue;
                std::shared_ptr<class Brand> brand;

                mv = std::shared_ptr<class MarketValue>(new class MarketValue());
                mv->Date = entries[0];
                mv->Name = entries[1];
                try {
                    mv->Capital = std::stod(entries[4]);
                    mv->RefCapital = std::stod(entries[5]);
                    mv->NumBrand = std::stod(entries[6]);
                }
                catch (...) {
                }
                _data.push_back(mv);
                //mv->Print();
            };
        }
        catch (...) {
        }
    }
    static int idx17_to_vecidx(int idx) {
        int ret = 0;
        switch (idx) {
        case 1:
            ret = 52;
            break;
        case 2:
            ret = 53;
            break;
        case 3:
            ret = 54;
            break;
        case 4:
            ret = 55;
            break;
        case 5:
            ret = 56;
            break;
        case 6:
            ret = 57;
            break;
        case 7:
            ret = 58;
            break;
        case 8:
            ret = 59;
            break;
        case 9:
            ret = 60;
            break;
        case 10:
            ret = 61;
            break;
        case 11:
            ret = 62;
            break;
        case 12:
            ret = 63;
            break;
        case 13:
            ret = 64;
            break;
        case 14:
            ret = 65;
            break;
        case 15:
            ret = 66;
            break;
        case 16:
            ret = 67;
            break;
        case 17:
            ret = 68;
            break;
        }
        return ret;
    }
    static int idx33_to_vecidx(int idx) {
        int ret = 0;
        switch (idx) {
        case 1:
            ret = 19;
            break;
        case 2:
            ret = 22;
            break;
        case 3:
            ret = 20;
            break;
        case 4:
            ret = 27;
            break;
        case 5:
            ret = 21;
            break;
        case 6:
            ret = 32;
            break;
        case 7:
            ret =29;
            break;
        case 8:
            ret = 23;
            break;
        case 9:
            ret = 24;
            break;
        case 10:
            ret = 25;
            break;
        case 11:
            ret = 26;
            break;
        case 12:
            ret = 28;
            break;
        case 13:
            ret = 35;
            break;
        case 14:
            ret = 30;
            break;
        case 15:
            ret = 31;
            break;
        case 16:
            ret = 33;
            break;
        case 17:
            ret = 34;
            break;
        case 18:
            ret = 36;
            break;
        case 19:
            ret = 37;
            break;
        case 20:
            ret = 43;
            break;
        case 21:
            ret = 51;
            break;
        case 22:
            ret = 38;
            break;
        case 23:
            ret = 39;
            break;
        case 24:
            ret = 40;
            break;
        case 25:
            ret = 41;
            break;
        case 26:
            ret = 42;
            break;
        case 27:
            ret = 44;
            break;
        case 28:
            ret = 45;
            break;
        case 29:
            ret = 46;
            break;
        case 30:
            ret = 47;
            break;
        case 31:
            ret = 48;
            break;
        case 32:
            ret = 49;
            break;
        case 33:
            ret = 50;
            break;
        }
        return ret;
    }
    std::shared_ptr<class MarketValue> Industory33(int idx)
    {
        int t;
        std::shared_ptr<class MarketValue> r;
        t = idx33_to_vecidx(idx);
        if (t == 0 || t>=_data.size())return r;
        r = _data[t];
        return r;
    }
    std::shared_ptr<class MarketValue> Industory17(int idx)
    {
        int t;
        std::shared_ptr<class MarketValue> r;
        t = idx17_to_vecidx(idx);
        if (t == 0 || t >= _data.size())return r;
        r = _data[t];
        return r;
    }
    std::shared_ptr<class MarketValue> Topix()
    {
        std::shared_ptr<class MarketValue> r;
        if (_data.size() < 1)return r;
        r = _data[0];
        return r;
    }

};

}
}
}

#endif

