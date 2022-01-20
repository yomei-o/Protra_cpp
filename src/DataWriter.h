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
#ifndef DH_DATAWRITER_H_
#define DH_DATAWRITER_H_

#include <stdio.h>
#include <string.h>
#include <string>
#include "LogData.h"
#include "BrandListConfig.h"
#include "zengoopen.h"

namespace Protra {
namespace Lib {
namespace Data {

class DataWriter {
public:
	static int WriteLog(std::string fname, std::shared_ptr<Protra::Lib::Config::BrandList> li, std::shared_ptr<LogData> logdata)
	{
		FILE* fp = NULL;
		if (li == nullptr || li->List->size()<1 || logdata == nullptr)return 1;
		fp = zengo_open(fname.c_str(), "wt", "data");
		if (fp == NULL)return 2;
		for (int i = 0; i < li->List->size(); i++) {
			std::string code;
			std::vector<std::shared_ptr<Log> > logs;
			code = li->List->at(i);
			if (code == "") {
				continue;
			}
			logs=logdata->GetLog(code);
			if (logs.size() < 1)continue;

			for (int j = 0; j < logs.size(); j++) {
				std::shared_ptr<Log> log = logs[i];
                std::string msg;

                msg = "";
                msg += log->Code;
                msg += " ";
                msg += log ->Name;
                msg += " ";

                char tmp[128];
                Protra::Lib::Data::DateTime d = log->Date;
                sprintf(tmp, "%02d/%02d/%02d", d.Year % 100, d.Month, d.Day);

                msg += tmp;
                msg += " ";

                sprintf(tmp, "%d‰~ %dŠ”", log->Price, log->Quantity);
                msg += tmp;
                msg += " ";

                if (log->Order = Protra::Lib::Data::Order::Buy) {
                    msg += "”ƒ";
                }
                else{
                    msg += "”„";
                }
                fprintf(fp,"%s\n", msg.c_str());
			}
		}
		fclose(fp);
		return 0;
	}
};


}
}
}


#endif


