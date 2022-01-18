// Copyright (C) 2022 Yomei Otani <yomei.otani@gmail.com>
// Copyright (C) 2003 Daisuke Arai <darai@users.sourceforge.jp>
// Copyright (C) 2005, 2010 panacoran <panacoran@users.sourceforge.jp>
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

#ifndef DF_BRAND_H_
#define DF_BRAND_H_

#define UTC_OFFSET 719162

#include<stdio.h>
#include<time.h>
#include<string>
#include<vector>
#include<memory>
#include<map>

#include"DateTime.h"
#include"StreamReader.h"
#include"splitreplace.h"


namespace Protra{
namespace Lib {
namespace Data {


enum Flag
{
    INIT = 0,
    OBS = 1,
    N255 = 2,
    A500 = 4
};

class Split
{
public:
    DateTime Date;
    double Ratio;
};


class Market
{
public:
    static std::string Name(std::string code)
    {
        if (code == "T1") {
            return "東証1部";
        }
        if (code == "T2") {
            return "東証2部";
        }
        if (code == "M") {
            return "マザーズ";
        }
        if (code == "J") {
            return "JASDAQ";
        }
        if (code == "O1") {
            return "大証1部";
        }
        if (code == "O2") {
            return "大証2部";
        }
        if (code == "H") {
            return "ヘラクレス";
        }
        return "不明";
    }

    static std::shared_ptr<std::vector<std::string> >Codes()
    {
        static std::shared_ptr<std::vector<std::string> >ret;
        if (ret == nullptr){
            ret = std::shared_ptr<std::vector<std::string> >
                (new std::vector<std::string>{ {"T1", "T2", "M", "J"} });
        }
        return ret;
    }
    static std::shared_ptr<std::vector<std::string> > AllCodes()
    {
        static std::shared_ptr<std::vector<std::string> >ret;
        if (ret == nullptr) {
            ret = std::shared_ptr<std::vector<std::string> >
                (new std::vector<std::string>{ { "T1", "T2", "M", "J", "O1", "O2", "H" } });
        }
        return ret;;
    }

    static std::shared_ptr<std::vector<std::string> >Names()
    {
        static std::shared_ptr<std::vector<std::string> >names;
        if (names == nullptr) {
            names = std::shared_ptr<std::vector<std::string> >(new std::vector<std::string>);
            std::shared_ptr<std::vector<std::string> >codes = Codes();
            if (names->size() == 0) {
                for (int i = 0; i < codes->size(); i++) {
                    names->push_back(Name(codes->at(i)));
                }
            }
        }
        return names;
    }

    static std::shared_ptr<std::vector<std::string> > AllNames()
    {
        static std::shared_ptr<std::vector<std::string> >names;
        if (names == nullptr) {
            names = std::shared_ptr<std::vector<std::string> >(new std::vector<std::string>);
            std::shared_ptr<std::vector<std::string> > allcodes = AllCodes();
            if (names->size() == 0) {
                for (int i = 0; i < allcodes->size(); i++) {
                    names->push_back(Name(allcodes->at(i)));
                }
            }
        }
        return names;
    }
};


class Brand {
public:
    std::string Code;
    std::string Name;
    std::string Market;
    int Unit;
    int Flags;
    std::vector<Split> Split;

    Brand()
    {
        Unit = 0;
        Flags = Flag::INIT;
    }
    Brand(std::string c, std::string m,std::string n, int u)
    {
        Code = c;
        Name = n;
        Market = m;
        Unit = u;
        Flags = Flag::INIT;
    }

    std::string MarketName()
    {
        return Market::Name(Market);
    }
    int CompareTo(Brand& other)
    {
        return Code==other.Code;
    }
    std::string ToString()
    {
        return Code + " " + MarketName() + " " + Name;
    }

};

class BrandData
{
public:
    std::map<std::string,std::shared_ptr<class Brand> > _data;
    std::string _dataFile = "index.txt";

    void Load()
    {
        _data.clear();
        std::shared_ptr<class Brand> b;
        b = std::shared_ptr<class Brand>(new class Brand("1001", "T1", "日経平均", 1));
        _data[b->Code] = b;
        b = std::shared_ptr<class Brand>(new class Brand("1002", "T1", "ＴＯＰＩＸ", 1));
        _data[b->Code] = b;
        try {
            StreamReader reader(_dataFile);
            std::string line;
            while ((line = reader.ReadLine()) != "")
            {
                std::vector<std::string>entries = split(line,",");
                if (entries.size() < 4)continue;
                std::shared_ptr<class Brand> brand;

                std::string tmp;
                tmp=replaceOtherStr(entries[1],"ホールディングス", "ＨＤ");

                brand = std::shared_ptr<class Brand>(
                    new class Brand(entries[0],entries[2],tmp,stoi(entries[3])));
                for (int i = 4; i < entries.size(); i++)
                {
                    if (entries[i] == "OBS") {
                        brand->Flags |= Flag::OBS;
                    }
                    else if (entries[i] == "N225") {
                        brand->Flags |= Flag::N255;
                    }
                    else if (entries[i] == "A500") {
                        brand->Flags |= Flag::A500;
                    }
                    else {
                        if (entries[i].find("S:") != 0) {
                            throw new std::runtime_error("index.txtが不正です。");
                        }
                        int y = stoi(entries[i].substr(2, 4),nullptr,10);
                        int m = stoi(entries[i].substr(6, 2), nullptr, 10);
                        int d = stoi(entries[i].substr(8, 2), nullptr, 10);
                        double r = stod(entries[i].substr(11));
                        Split split;
                        split.Date = DateTime(y, m, d);
                        split.Ratio = r;
                        brand->Split.push_back(split);
                    }
                }
                _data[brand->Code]=brand;
            };
        }
        catch (...) {

        }
    }

    bool Contains(std::string code)
    {
        std::shared_ptr<class Brand> p;
        p = _data[code];
        return p != nullptr;
    }

    int Count()
    {
        return (int)_data.size();
    }

    std::shared_ptr<class Brand> Brand(std::string code)
    {
        std::shared_ptr<class Brand> p;
        p = _data[code];
        return p;
    }

    std::shared_ptr<std::vector<std::string> >Nikkei225()
    {
        std::shared_ptr<std::vector<std::string> >brands;
        brands = std::shared_ptr<std::vector<std::string> >(new std::vector<std::string>);

        auto begin = _data.begin(), end = _data.end();
        for (auto iter = begin; iter != end; iter++) {
            std::shared_ptr<class Brand> b = iter->second;
            if ((b->Flags & Flag::N255) != 0) {
                brands->push_back(b->Code);
            }
        }
        return brands;
    }

    /// <summary>
    /// 売買代金上位500位の銘柄を返す。
    /// </summary>
    /// <returns>証券コードのリスト</returns>
    std::shared_ptr<std::vector<std::string> >A500()
    {
        std::shared_ptr<std::vector<std::string> >brands;
        brands = std::shared_ptr<std::vector<std::string> >(new std::vector<std::string>);

        auto begin = _data.begin(), end = _data.end();
        for (auto iter = begin; iter != end; iter++) {
            std::shared_ptr<class Brand> b = iter->second;
            if ((b->Flags & Flag::A500) != 0) {
                brands->push_back(b->Code);
            }
        }
        return brands;
    }

    std::vector<std::shared_ptr<class Brand> > Search(std::string name)
    {
        std::vector<std::shared_ptr<class Brand> > r;
        auto begin = _data.begin(), end = _data.end();
        for (auto iter = begin; iter != end; iter++) {
            std::shared_ptr<class Brand> b = iter->second;
            if (b->Name.find(name)!=-1) {
                r.push_back(b);
            }
        }
        return r;
    }
};




}
}
}


#endif

