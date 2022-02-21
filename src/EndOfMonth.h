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

#ifndef DF_ENDOFMONTH_H_
#define DF_ENDOFMONTH_H_

#include<stdio.h>
#include<time.h>
#include<string>
#include<vector>
#include<memory>
#include<map>

#include"StreamReader.h"
#include"splitreplace.h"
#include"MarketValueConfig.h"

//#define ENABLE_MUJINZOU_DATA 1

namespace Protra {
namespace Lib {
namespace Data {

class EndOfMonth {
public:
    std::string Code;
    std::string Date;
    FLOAT Close;
    EndOfMonth()
    {
        Close = 0;
    }
    void Print()
    {
        printf("Code=%s\n", Code.c_str());
        printf("Date=%s\n", Date.c_str());
        printf("Close=%f\n", Close);
        printf("\n");
    }
};


class EndOfMonthData {
public:
    std::map<std::string,std::shared_ptr<class EndOfMonth> >_data;
#ifdef ENABLE_MUJINZOU_DATA
    std::string _dataFile = "T211230.csv";
#else
    std::string _dataFile = "D211230.csv";
#endif
    void Load()
    {
        char buf[256];
        _data.clear();
        std::shared_ptr<class EndOfMonth> em;
        try {
            StreamReader reader(_dataFile);
            std::string line;
            reader.ReadLine();
            while ((line = reader.ReadLine()) != "")
            {
                std::vector<std::string>entries = split(line, ",");
                if (entries.size() < 8)continue;
                std::shared_ptr<class Brand> brand;

                em = std::shared_ptr<class EndOfMonth>(new class EndOfMonth());
                em->Date = entries[0];
                em->Code = entries[1];
                try {
#ifdef ENABLE_MUJINZOU_DATA
                    em->Close = std::stod(entries[7]);
#else
                    em->Close = std::stod(entries[6]);
#endif
                }
                catch (...) {
                }
                _data[em->Code] = em;
                //tw->Print();
            };
        }
        catch (...) {
        }
    }
    std::shared_ptr<class EndOfMonth> Code(std::string code)
    {
        std::shared_ptr<class EndOfMonth> ret;
        ret = _data[code];
        return ret;
    }

};

}
}
}

#endif

