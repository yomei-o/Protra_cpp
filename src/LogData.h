// Copyright (C) 2022 Yomei Otani <yomei.otani@gmail.com>
// Copyright(C) 2010, 2013 panacoran <panacoran@users.sourceforge.jp>
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

#ifndef DF_LOGDATA_H_
#define DF_LOGDATA_H_

#include <algorithm>
#include <vector>
#include <map>
#include <memory>
#include "DateTime.h"

namespace Protra {
namespace Lib {
namespace Data {

enum Order
{
    Buy,
    Sell
};

class Log
{
public:
    std::string Code;
    DateTime Date;
    int Price;
    int Quantity;
    int Order;
    int CompareTo(Log& other)
    {
        if (Date.Value != other.Date.Value)return 1;
        return Code == other.Code;
    }

};


class LogData
{
public:
    bool _updated;
    
    std::map <std::string,std::map<std::string, std::shared_ptr<Log> > >_data;
    LogData(std::string system, int timeFrame)
    {
        _updated = false;
    }
    bool Add(std::shared_ptr<Log> log)
    {
        if (_data.count(log->Code) == 0) {
            std::map <std::string, std::shared_ptr<Log> >tmp;
            _data[log->Code] = tmp;
        }
        if (_data[log->Code].count(log->Date.toString()) != 0) {
            return false;
        }
        _data[log->Code][log->Date.toString()] = log;
        _updated = true;
        return true;
    }
    std::vector<std::shared_ptr<Log> > GetLog(std::string code)
    {
        std::vector<std::shared_ptr<Log> > ret;
        if (_data.count(code) == 0)return ret;
        std::map<std::string, std::shared_ptr<Log> > map=_data[code];

        for (auto iter = map.begin(); iter != map.end(); ++iter) {
            ret.push_back(iter->second);
        }
        std::sort(ret.begin(), ret.end(),
            [](const std::shared_ptr<Log>& x, const std::shared_ptr<Log>& y) {return x->Date.Value < y->Date.Value; });

        return ret;

    }


};


}
}
}


#endif



