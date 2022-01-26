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
#ifndef DH_DATAREADER_H_
#define DH_DATAREADER_H_

#include <stdio.h>
#include <string.h>
#include <string>
#include "LogData.h"
#include "BrandListConfig.h"
#include "PricePairList.h"
#include "zengoopen.h"
#include "splitreplace.h"

namespace Protra {
namespace Lib {
namespace Data {

class DataReader {
public:
	static int makeBrandList(std::shared_ptr<LogData>& logdata, std::shared_ptr < Protra::Lib::Config::BrandList>& bl)
	{
		bl->List=  std::shared_ptr <std::vector<std::string> >(new std::vector<std::string>);
		for (auto iter = logdata->_data.begin(); iter != logdata->_data.end(); ++iter) {
			bl->List->push_back(iter->first);
		}
		return 0;
	}
	static int ReadCSVLog(std::string fname,std::shared_ptr<LogData>& logdata, std::shared_ptr < Protra::Lib::Config::BrandList>& bl)
	{
		FILE* fp = NULL;
		fp = zengo_open(fname.c_str(), "rt", "data");
		if (fp == NULL)return 2;
		char buf[256];
		while (1) {
			buf[0] = 0;
			fgets(buf, sizeof(buf), fp);
			if (buf[0] == 0)break;
			std::string line = buf;
			std::vector<std::string>entries = split(line, ",");
			std::shared_ptr<Log> log;
			log = std::shared_ptr<Log>(new Log);
			int c = 0;
			sscanf(entries[0].c_str(), "\"%d\"", &c);
			log->Code = std::to_string(c);
			log->Name = entries[1];
			int yy = 0, mm = 0, dd = 0;
			sscanf(entries[2].c_str(), "%d/%d/%d", &dd,&mm,&yy);
			DateTime dt(yy, mm, dd);
			log->Date = dt;
			log->Price = std::stoi(entries[3]);
			log->Quantity = std::stoi(entries[4]);
			log->Order = std::stoi(entries[5]);
			logdata->Add(log);
		}
		fclose(fp);
		makeBrandList(logdata, bl);
		return 0;
	}

};


}
}
}


#endif


