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

#include <stdio.h>
#include "Ptsim.h"

int main(int argc,char* argv[])
{
	std::shared_ptr <std::map<std::string, std::string> >option;
	option = std::shared_ptr <std::map<std::string, std::string> >(new (std::map<std::string, std::string>));


	std::shared_ptr<PtSim::CppExcutor> cex;
	cex = std::shared_ptr<PtSim::CppExcutor>(new PtSim::CppExcutor("sample"));
	if (cex->initialized == 0) {
		printf("initialize error\n");
		return 1;
	}

	cex->AddLog(2001, 1, 12, "1378", "hoge", 1200, 100, 0);
	cex->AddLog(2001, 3, 12, "1378", "hoge", 1300, 100, 1);
	cex->AddLog(2001, 4, 3, "1378", "hoge", 1200, 100, 0);
	cex->AddLog(2001, 4, 10, "1378", "hoge", 1300, 100, 1);

	option->insert({{"saveprofit","profit.txt"}});
	option->insert({{"saveprofitcsv","profit.csv"}});
	option->insert({{"savetrading", "trading.txt"}});
	option->insert({{"savetradingcsv","tading.csv"}});

	cex->Performance(option);
	if (cex->excuted == 0) {
		printf("excute error\n");
		return 1;
	}

	return 0;
}

