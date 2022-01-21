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

#ifndef DF_PRICEDATA_H_
#define DF_PRICEDATA_H_

#include <string>
#include "DateTime.h"
#include "BinaryReader.h"
#include "BinaryWriter.h"
#include "BrandData.h"
#include "Global.h"

namespace Protra {
namespace Lib{
namespace Data {

class Price
{
public:
    int RecordSize;
    std::string Code;
    std::string Market;
    DateTime Date;
    int Open;
    int High;
    int Low;
    int Close;
    double Volume;

    Price()
    {
        RecordSize = 4;
        Open=0;
        High=0;
        Low=0;
        Close=0;
        Volume=0;
    }
    void Split(double ratio)
    {
        Open = (int)(Open / ratio);
        High = (int)(High / ratio);
        Low = (int)(Low / ratio);
        Close = (int)(Close / ratio);
        Volume *= ratio;
    }
    void Read(BinaryReader& b)
    {
        Date = DateTime(b.ReadInt32());
        Open = b.ReadInt32();
        High = b.ReadInt32();
        Low = b.ReadInt32();
        Close = b.ReadInt32();
        Volume = b.ReadDouble();
    }
    void Write(BinaryWriter& b)
    {
        b.WriteInt32(Date.Value);
        b.WriteInt32(Open);
        b.WriteInt32(High);
        b.WriteInt32(Low);
        b.WriteInt32(Close);
        b.WriteDouble(Volume);
    }
};

enum TimeFrame
{
    Daily,
    Weekly
};

class PriceList
{
public:
    std::shared_ptr<std::vector<std::shared_ptr<Price> > >_priceList;
    int TimeFrame;
    std::shared_ptr<Price> First()
    {
        std::shared_ptr<class Price> ret;
        if (_priceList->size() == 0)return ret;
        ret = _priceList->at(0);
        return ret;
    }

    std::shared_ptr<Price>Last()
    {
        int c;
        std::shared_ptr<class Price> ret;
        c = (int)_priceList->size();
        if (c == 0)return ret;
        ret = _priceList->at(c - 1);
        return ret;
    }
    int Count()
    {
        return (int)_priceList->size();
    }
    PriceList(std::shared_ptr<std::vector<std::shared_ptr<class Price> > >prices,int timeFrame)
    {
        _priceList = prices;
        TimeFrame = timeFrame;
    }

    std::shared_ptr<Price> Price(int index)
    {
        std::shared_ptr<class Price> ret;
        if (index < 0 || index >= _priceList->size())return ret;
        ret=_priceList->at(index);
        return ret;
    }
    int SearchByDate(DateTime& date)
    {
        int c;
        c = (int)_priceList->size();
        for (int i = 0; i < c; i++) {
            if (_priceList->at(i)->Date == date) {
                return i;
            }
        }
        return -1;
    }
};

class PriceData
{
public:
    static DateTime MaxDate()
    {
        static int cashe_maxdate=0;
        if (cashe_maxdate) {
            return DateTime(cashe_maxdate);
        }
        BinaryReader b = BinaryReader("MaxDate");
        if (b.isExist() == false) {
            return DateTime(0);
        }
        cashe_maxdate = b.ReadInt32();
        return DateTime(cashe_maxdate);
    }

    static std::shared_ptr<PriceList> GetPrices(std::string code,int timeFrame, bool needLastWeek = false)
    {
        std::shared_ptr<PriceList> ret;

        std::shared_ptr<std::vector<std::shared_ptr<Price> > > prices;
        prices = std::shared_ptr<std::vector<std::shared_ptr<Price> > >(new(std::vector<std::shared_ptr<Price> >));
        {
            BinaryReader b(code);
            if (b.isExist() == false)return ret;

            while (b.Position() < b.Length())
            {
                std::shared_ptr<Price> p;
                p = std::shared_ptr <class Price>(new class Price());
                p->Code=code;
                p->Read(b);
                prices->push_back(p);
            }
        }
        std::shared_ptr <Brand> brand;
        std::shared_ptr<BrandData> branddata=GlobalEnv::BrandData();
        if (branddata != nullptr) {
            brand = branddata->Brand(code);
        }
        if (brand == nullptr) {
            brand = std::shared_ptr<Brand>(new Brand());
        }

        int sz = (int)brand->Split.size();
        for (int i = 0; i < sz; i++) {
            Split split = brand->Split[i];
            if (split.Date.Value > prices->at(prices->size() - 1)->Date.Value) {
                continue;
            }
            std::shared_ptr<Price> price;
            int sszz = (int)prices->size();
            for (int ii = 0; ii < sszz; ii++) {
                price = prices->at(ii);
                if (price->Date.Value < split.Date.Value) {
                    price->Split(split.Ratio);
                }
                else {
                    break;
                }
            }
        }
        if (timeFrame == TimeFrame::Daily) {
            ret = std::shared_ptr<PriceList>(new PriceList(prices, needLastWeek));
            return ret;
        }
        ret= GenerateWeeklyPrices(prices, needLastWeek);
        return ret;
    }
    static std::shared_ptr<PriceList> GenerateWeeklyPrices(std::shared_ptr<std::vector<std::shared_ptr<Price> > >& daily, bool needLastWeek)
    {
        //TODO
        std::shared_ptr<PriceList> ret;
        return ret;
    }

};


}
}
}



#endif
