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

#ifndef DF_INDUSTORY_H_
#define DF_INDUSTORY_H_

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

class Industory {
public:
    std::string Code;
    std::string Name;
    std::string Ind33;
    std::string Ind17;
    int Code33;
    int Code17;
    int Index33;
    int Index17;
    Industory()
    {
        Code33 = 0;
        Code17 = 0;
        Index33 = 0;
        Index17 = 0;
    }
    void Print()
    {
        printf("Code=%s\n",Code.c_str());
        printf("Name=%s\n", Name.c_str());
        printf("Ind33=%s(%d)\n", Ind33.c_str(),Code33);
        printf("Ind17=%s(%d)\n", Ind17.c_str(),Code17);
        printf("Index33=%d\n", Index33);
        printf("Index17=%d\n", Index17);
        printf("\n");
    }
    static int Code33ToIndex33(int code33) {
        int ret = 0;
        switch (code33) {
        case 50:
            ret = 1;
            break;
        case 3050:
            ret = 2;
            break;
        case 1050:
            ret = 3;
            break;
        case 3300:
            ret = 4;
            break;
        case 2050:
            ret = 5;
            break;
        case 3550:
            ret = 6;
            break;
        case 3400:
            ret = 7;
            break;
        case 3100:
            ret = 8;
            break;
        case 3150:
            ret = 9;
            break;
        case 3200:
            ret = 10;
            break;
        case 3250:
            ret = 11;
            break;
        case 3350:
            ret = 12;
            break;
        case 3700:
            ret = 13;
            break;
        case 3450:
            ret = 14;
            break;
        case 3500:
            ret = 15;
            break;
        case 3600:
            ret = 16;
            break;
        case 3650:
            ret = 17;
            break;
        case 3750:
            ret = 18;
            break;
        case 3800:
            ret = 19;
            break;
        case 5250:
            ret = 20;
            break;
        case 9050:
            ret = 21;
            break;
        case 4050:
            ret = 22;
            break;
        case 5050:
            ret = 23;
            break;
        case 5100:
            ret = 24;
            break;
        case 5150:
            ret = 25;
            break;
        case 5200:
            ret = 26;
            break;
        case 6050:
            ret = 27;
            break;
        case 6100:
            ret = 28;
            break;
        case 7050:
            ret = 29;
            break;
        case 7100:
            ret = 30;
            break;
        case 7150:
            ret = 31;
            break;
        case 7200:
            ret = 32;
            break;
        case 8050:
            ret = 33;
            break;
        }
        return ret;
    }
    static int Code17ToIndex17(int code17) {
        int ret = 0;
        switch (code17) {
        case 1:
            ret = 1;
            break;
        case 2:
            ret = 2;
            break;
        case 3:
            ret = 3;
            break;
        case 4:
            ret = 4;
            break;
        case 5:
            ret = 5;
            break;
        case 6:
            ret = 6;
            break;
        case 7:
            ret = 7;
            break;
        case 8:
            ret = 8;
            break;
        case 9:
            ret = 9;
            break;
        case 10:
            ret = 10;
            break;
        case 11:
            ret = 11;
            break;
        case 12:
            ret = 12;
            break;
        case 13:
            ret = 13;
            break;
        case 14:
            ret = 14;
            break;
        case 15:
            ret = 15;
            break;
        case 16:
            ret = 16;
            break;
        case 17:
            ret = 17;
            break;
        }
        return ret;
    }
};


class IndustoryData {
public:
    std::map<std::string, std::shared_ptr<class Industory> > _data;
    std::string _dataFile = "data_j.csv";
    void Load()
    {
        char buf[256];
        _data.clear();
        std::shared_ptr<class Industory> ind;
        try {
            StreamReader reader(_dataFile);
            std::string line;
            reader.ReadLine();
            while ((line = reader.ReadLine()) != "")
            {
                std::vector<std::string>entries = split(line, ",");
                if (entries.size() < 8)continue;
                std::shared_ptr<class Brand> brand;

                ind = std::shared_ptr<class Industory>(new class Industory());
                ind->Code = entries[1];
                ind->Name = entries[2];
                buf[0] = 0;
                sscanf(entries[5].c_str(), "%[^ ]", buf);
                ind->Ind33 = buf;
                buf[0] = 0;
                sscanf(entries[7].c_str(), "%[^ ]", buf);
                ind->Ind17 = buf;
                try {
                    ind->Code33 = std::stoi(entries[4]);
                    ind->Code17 = std::stoi(entries[6]);
                }
                catch (...) {
                }
                if (ind->Code17 == 0 || ind->Code33 == 0)continue;
                ind->Index17 = Industory::Code17ToIndex17(ind->Code17);
                ind->Index33 = Industory::Code33ToIndex33(ind->Code33);
                _data[ind->Code] = ind;
                //ind->Print();

            };
        }
        catch (...) {
        }
    }
    std::vector<std::shared_ptr<class Industory> > Industory33(int idx)
    {
        std::vector<std::shared_ptr<class Industory> > r;
        auto begin = _data.begin(), end = _data.end();
        for (auto iter = begin; iter != end; iter++) {
            std::shared_ptr<class Industory> ind = iter->second;
            if (ind->Index33==idx) {
                r.push_back(ind);
            }
        }
        return r;
    }
    std::vector<std::shared_ptr<class Industory> > Industory17(int idx)
    {
        std::vector<std::shared_ptr<class Industory> > r;
        auto begin = _data.begin(), end = _data.end();
        for (auto iter = begin; iter != end; iter++) {
            std::shared_ptr<class Industory> ind = iter->second;
            if (ind->Index17 == idx) {
                r.push_back(ind);
            }
        }
        return r;
    }

    std::shared_ptr<class Industory> Industory(std::string code)
    {
        std::shared_ptr<class Industory> r;
        auto begin = _data.begin(), end = _data.end();
        for (auto iter = begin; iter != end; iter++) {
            std::shared_ptr<class Industory> ind = iter->second;
            if (ind->Code== code) {
                r=ind;
                return r;
            }
        }
        return r;
    }

};

}
}
}

#endif

