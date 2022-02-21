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

#ifndef DF_TOPIXWAIT_H_
#define DF_TOPIXWAIT_H_

#include<stdio.h>
#include<time.h>
#include<string>
#include<vector>
#include<memory>
#include<map>

#include"StreamReader.h"
#include"splitreplace.h"
#include"MarketValueConfig.h"

namespace Protra {
namespace Lib {
namespace Data {

class TopixWait {
public:
    std::string Name;
    std::string Date;
    std::string Code;
    std::string Industory;

    FLOAT Wait;
    TopixWait()
    {
        Wait = 0;
    }
    void Print()
    {
        printf("Code=%s\n", Code.c_str());
        printf("Name=%s\n",Name.c_str());
        printf("Date=%s\n", Date.c_str());
        printf("Wait=%f\n", Wait);
        printf("\n");
    }
};


class TopixWaitData {
public:
    std::map<std::string,std::shared_ptr<class TopixWait> >_data;
    std::string _dataFile = "TOPIX_weight_jp.csv";
    void Load()
    {
        char buf[256];
        _data.clear();
        std::shared_ptr<class TopixWait> tw;
        try {
            StreamReader reader(_dataFile);
            std::string line;
            reader.ReadLine();
            while ((line = reader.ReadLine()) != "")
            {
                std::vector<std::string>entries = split(line, ",");
                if (entries.size() < 5)continue;
                std::shared_ptr<class Brand> brand;

                tw = std::shared_ptr<class TopixWait>(new class TopixWait());
                tw->Date = entries[0];
                tw->Name = entries[1];
                tw->Code = entries[2];
                try {
                    tw->Wait = std::stod(entries[4]);
                }
                catch (...) {
                }
                _data[tw->Code] = tw;
                //tw->Print();
            };
        }
        catch (...) {
        }
    }
    std::shared_ptr<class TopixWait> Code(std::string code)
    {
        std::shared_ptr<class TopixWait> ret;
        ret = _data[code];
        return ret;
    }

};

}
}
}

#endif

