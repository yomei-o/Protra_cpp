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
#include <string.h>
#include <thread>
#include <chrono>

#if defined(_WIN32) && !defined(__GNUC__)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif /* _WIN32 */

#ifdef _MSC_VER
#if _MSC_VER >= 1400
#pragma warning( disable : 4996 )
#pragma warning( disable : 4819 )
#endif
#endif

#include "Ptsim.h"

std::shared_ptr <std::map<std::string, std::string> >option;
static std::shared_ptr<PtSim::SystemExcutor> mf;
static int stoped = 0;
void thread_timeout()
{
	for (int i = 0; i < 300; i++) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		//if (i % 10 == 0)printf("%d\n",i);
		if (stoped)return;
	}
	mf->StopInterpretor();
}
void thread_main()
{
	mf->LoopBrandAndDate(option);
	stoped = 1;
}
int main(int argc,char* argv[])
{
	option = std::shared_ptr <std::map<std::string, std::string> >(new (std::map<std::string, std::string>));

	std::shared_ptr<Protra::Lib::Config::BrandList> bl;
	bl = std::shared_ptr<Protra::Lib::Config::BrandList>(new (Protra::Lib::Config::BrandList));
	bl->List = std::shared_ptr <std::vector<std::string> >(new std::vector<std::string>);

	int flag_help = 0;
	std::string system_name;

	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help")==0) {
			flag_help = 1;
		}
		else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
			(* option.get())["savetrading"]=argv[i + 1];
			i++;
		}
		else if (strcmp(argv[i], "-p") == 0 && i + 1 < argc) {
			(*option.get())["saveprofit"] = argv[i + 1];
			i++;
		}
		else if (strcmp(argv[i], "-s") == 0 && i + 1 < argc) {
			(*option.get())["savetradingcsv"] = argv[i + 1];
			i++;
		}
		else if (strcmp(argv[i], "-g") == 0 && i + 1 < argc) {
			(*option.get())["saveprofitcsv"] = argv[i + 1];
			i++;
		}
		else if (strcmp(argv[i], "-a") == 0 && i + 1 < argc) {
			(*option.get())["appendlog"] = argv[i + 1];
			i++;
		}
		else if (strcmp(argv[i], "-l") == 0 && i + 1 < argc) {
			(*option.get())["logfile"] = argv[i + 1];
			i++;
		}
		else {
			if (system_name == "") {
				system_name = argv[i];
				continue;
			}
			bl->List->push_back(argv[i]);
		}
	}
	if ((flag_help || system_name=="" || bl->List->size()<1) && option->count("logfile")==0) {
		printf("PtSimConsole [option ...] file.pt Code1 [Code2 ...] \n");
		printf("\n");
		printf("-h --help                オプションの表示\n");
		printf("-o [filename]            取引データのファイルへの出力\n");
		printf("-s [filename]            取引データのCSVファイルへの出力\n");
		printf("-p [filename]            利益分析データのファイルへの出力\n");
		printf("-g [filename]            利益曲線データのCSVファイルへの出力\n");
		printf("-a [filename]            ログデータのCSV追加まで実行し\n");
		printf("-l [filename]            CSVログデータから利益分析を行う\n");
		return 0;
	}
	if (bl->Name == "")bl->Name = "noname";
	//std::shared_ptr<PtSim::SystemExcutor> mf;
	mf = std::shared_ptr<PtSim::SystemExcutor>(new PtSim::SystemExcutor(system_name,bl,Protra::Lib::Data::TimeFrame::Daily));
	if (mf->initialized == 0) {
		printf("PtSimConsole initialize error\n");
		return 1;
	}
	std::thread th1;
	std::thread th2;

	th1 = std::thread(thread_main);
	th2 = std::thread(thread_timeout);
	th1.join();
	th2.join();

	if (mf->excuted == 0) {
		printf("PtSimConsole excute error\n");
		return 1;
	}
	mf->Performance(option);
	return 0;
}

