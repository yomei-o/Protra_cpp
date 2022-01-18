// Copyright (C) 2022 Yomei Otani <yomei.otani@gmail.com>
// Copyright (C) 2013 panacoran <panacoran@users.sourceforge.jp>
// Copyright (C) 2003 Daisuke Arai <darai@users.sourceforge.jp>
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
// $Id$
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <memory>
#include "DateTime.h"

namespace PtSim
{

    class PricePair
    {
    public:
        float Market;
        float Book;
        Protra::Lib::Data::DateTime Date;
        PricePair()
        {
            Market = 0;
            Book = 0;
        }
        PricePair(const PricePair& p) {
            Market = p.Market;
            Book = p.Book;
            Date = p.Date;
        }
        PricePair(float market, float book)
        {
            Market = market;
            Book = book;
        }
        PricePair operator=(const PricePair& p) {
            Market = p.Market;
            Book = p.Book;
            Date = p.Date;
            return *this;
        }
        void AddMarket(float value)
        {
            Market += value;
        }
        void AddMarket(float quantity, float price)
        {
            Market += quantity * price;
        }
        void AddBook(float value)
        {
            Book += value;
        }
        void AddBook(float quantity, float price)
        {
            Book += quantity * price;
        }
        PricePair operator +(PricePair v2)
        {
            return PricePair(Market + v2.Market, Book + v2.Book);
        }
        PricePair operator -(PricePair v2)
        {
            return PricePair(Market - v2.Market, Book - v2.Book);
        }
        static PricePair Max(PricePair v1, PricePair v2)
        {
            return PricePair(std::max(v1.Market, v2.Market),
                std::max(v1.Book, v2.Book));
        }
        static PricePair Min(PricePair v1, PricePair v2)
        {
            return PricePair(std::min(v1.Market, v2.Market),
                std::min(v1.Book, v2.Book));
        }
    };


    class PricePairList
    {
    public:
        std::vector<std::shared_ptr<PricePair> >_sortedList;
        std::map<std::string,std::shared_ptr<PricePair> >_sortedList2;
        int Count()
        {
            return (int)_sortedList.size();
        }
        void add(Protra::Lib::Data::DateTime& date,std::shared_ptr<PricePair> value)
        {
            value->Date = date;
            _sortedList.push_back(value);
            _sortedList2[date.toString()]=value;
        }
        std::shared_ptr<PricePair> get(Protra::Lib::Data::DateTime& date)
        {
            std::shared_ptr<PricePair> ret;
            ret = _sortedList2[date.toString()];
            return ret;
        }
        std::shared_ptr<PricePairList> AccumulatedList()
        {
            std::shared_ptr<PricePairList> list;
            list = std::shared_ptr<PricePairList>(new PricePairList);
            class PricePair sum;
            std::sort(_sortedList.begin(), _sortedList.end(),
                [](const std::shared_ptr<PricePair>& x, const std::shared_ptr<PricePair>& y) {
                    return x->Date.Value < y->Date.Value; 
                });
            for(int i=0;i<_sortedList.size();i++)
            {
                sum = sum+*_sortedList[i].get();
                list->add(_sortedList[i]->Date,std::shared_ptr<PricePair>(new PricePair(sum)));
            }
            return list;
        }
        std::shared_ptr<PricePairList> BookAccumulatedList()
        {
            std::shared_ptr<PricePairList> list;
            list = std::shared_ptr<PricePairList>(new PricePairList);
            float sum = 0;
            std::sort(_sortedList.begin(), _sortedList.end(),
                [](const std::shared_ptr<PricePair>& x, const std::shared_ptr<PricePair>& y) {
                    return x->Date.Value < y->Date.Value;
                });
            for (int i = 0; i < _sortedList.size(); i++)
            {
                PricePair pair = *_sortedList[i].get();
                sum += pair.Book;
                list->add(pair.Date, std::shared_ptr<PricePair>(new PricePair(pair.Market,sum)));
            }
            return list;
        }

    };

}