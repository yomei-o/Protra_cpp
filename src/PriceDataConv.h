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

#include <string>
#include <stdio.h>

#include "PriceData.h"
#include "StreamWriter.h"
#include "splitreplace.h"

namespace Protra{
namespace Lib{
namespace Data{

class PriceDataConv
{
public:
    static bool ConvertToCSV(std::string code, std::string fn)
    {
        try {
            std::shared_ptr<Protra::Lib::Data::BrandData>& bd = Protra::Lib::GlobalEnv::BrandData();
            bd = std::shared_ptr<Protra::Lib::Data::BrandData>(new Protra::Lib::Data::BrandData());
            bd->Load();

            std::shared_ptr<PriceList>prices = PriceData::GetPrices(code, TimeFrame::Daily);
            if (prices == nullptr || prices->Count() == 0)return false;


            StreamWriter f = StreamWriter(fn);
            for (int i = 0; i < prices->Count(); i++) {
                char buf[64];
                Price p = *prices->Price(i).get();
                std::string msg;
                msg = "";
                msg += p.Date.toStringCSV();
                msg += ",";
                msg += std::to_string(p.Open);
                msg += ",";
                msg += std::to_string(p.High);
                msg += ",";
                msg += std::to_string(p.Low);
                msg += ",";
                msg += std::to_string(p.Close);
                msg += ",";
                sprintf(buf, "%.0f", p.Volume);
                msg += buf;
                f.WriteLine(msg);
            }
            f.Close();
            return true;
        }
        catch (...)
        {
            return false;
        }
    }
    static bool ConvertFromCSV(std::string fn, std::string code)
    {
        try {
            std::vector<Price> prices;
            StreamReader f = StreamReader(fn);
            std::string line;
            while ((line = f.ReadLine()) != "")
            {
                Price p;
                std::vector<std::string> token;
                int yy, mm, dd;
                token = split(line, ",");
                if (token.size() < 6)continue;
                p.Code = code;
                yy = 0; mm = 0; dd = 0;
                sscanf(token[0].c_str(), "%d/%d/%d", &yy, &mm, &dd);
                p.Date = DateTime(yy, mm, dd);
                p.Open = std::stoi(token[1]);
                p.High = std::stoi(token[2]);
                p.Low = std::stoi(token[3]);
                p.Close = std::stoi(token[4]);
                p.Volume = std::stod(token[5]);
                prices.push_back(p);
            }
            BinaryWriter b = BinaryWriter(code);
            for (int i = 0; i < prices.size(); i++) {
                prices[i].Write(b);
            }
            b.Close();
            f.Close();
            return true;
        }
        catch (...) {
            return false;
        }
    }
};


}
}
}