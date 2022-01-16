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
// $Id: Global.cs 389 2010-11-28 06:45:45Z panacoran $

#ifndef DF_DATETIME_H_
#define DF_DATETIME_H_

#define UTC_OFFSET 719162

#include<stdio.h>
#include<time.h>
#include<string>

#define timegm _mkgmtime

namespace Protra{
namespace Lib {
namespace Data {


class DateTime
{
public:
    int Year;
    int Month;
    int Day;
    int Value;
    DateTime() 
    {
        Year = 0;
        Month = 0;
        Day = 0;
        Value = 0;
    }
    DateTime(int ik_)
    {
        struct tm* tm;
        time_t ik = ik_;
 
        Year = 0;
        Month = 0;
        Day = 0;
        Value = ik_;
    
        if (ik_ == 0)return;

        ik -= UTC_OFFSET;
        ik *= 86400;
        tm = gmtime(&ik);
        if (tm == nullptr)return;

        Year = tm->tm_year + 1900;
        Month = tm->tm_mon + 1;
        Day = tm->tm_mday;
    }
    DateTime(int y,int m,int d)
    {
        struct tm tm;
        time_t t;
        memset(&tm, 0, sizeof(tm));
        Year = y;
        Month = m;
        Day = d;
        tm.tm_year = y - 1900;
        tm.tm_mon = m - 1;
        tm.tm_mday = d;
        t = timegm(&tm);
        Value = (int)(t / 86400)+UTC_OFFSET;

    }
    DateTime(const DateTime &d)
    {
        Year = d.Year;
        Month = d.Month;
        Day = d.Day;
        Value = d.Value;
    }
    DateTime& operator =(DateTime& d)
    {
        Year = d.Year;
        Month = d.Month;
        Day = d.Day;
        Value = d.Value;
        return *this;
    }
    bool operator ==(DateTime& d)
    {
        if (Year != d.Year)return false;
        if (Month != d.Month)return false;
        if(Day != d.Day)return false;
        return true;
    }
    bool operator !=(DateTime& d)
    {
        return !(* this == d);
    }
};



}
}
}


#endif

