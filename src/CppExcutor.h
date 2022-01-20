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

#ifndef DF_CPPECXUTOR_H_
#define DF_CPPEXCUTOR_H_

#include "BrandListConfig.h"
#include "Global.h"
#include "BrandData.h"
#include "PriceData.h"
#include "Protra.h"
#include "BasicBuiltins.h"
#include "SimulateBuiltins.h"
#include "LogData.h"
#include "Performance.h"
#include "DataWriter.h"

class CppExcutor {
public:
	std::string _name;
	int initialized;
	int excuted;
	std::shared_ptr< Protra::Lib::Data::LogData> logData;
	std::map<std::string, int> codes;

	CppExcutor(std::string name)
	{
		initialized = 0;
		excuted = 0;
		_name = name;
		std::shared_ptr<Protra::Lib::Data::BrandData>& bd = Protra::Lib::GlobalEnv::BrandData();
		bd = std::shared_ptr<Protra::Lib::Data::BrandData>(new Protra::Lib::Data::BrandData());
		bd->Load();
		logData = std::shared_ptr< Protra::Lib::Data::LogData>(new Protra::Lib::Data::LogData(_name,Protra::Lib::Data::TimeFrame::Daily));
		initialized = 1;
	}
	void AddLog(int year, int month, int day, std::string code, std::string name, int pri, int qua, int order)
	{
		Protra::Lib::Data::DateTime date(year,month,day);

		std::shared_ptr < Protra::Lib::Data::Log> log;
		log = std::shared_ptr < Protra::Lib::Data::Log>(new(Protra::Lib::Data::Log));
		log->Code = code;
		log->Name = name;
		log->Price = pri;
		log->Quantity = qua;
		log->Order = order;
		log->Date = date;
		logData->Add(log);
		codes[code] = 1;
	}
	void Performance(std::shared_ptr<std::map<std::string,std::string> > option)
	{
		std::shared_ptr<Protra::Lib::Config::BrandList> _brandList;
		_brandList = std::shared_ptr<Protra::Lib::Config::BrandList>(new(Protra::Lib::Config::BrandList));
		_brandList->List = std::shared_ptr <std::vector<std::string> >(new std::vector<std::string>);
		for (const auto& item : codes) {
			_brandList->List->push_back(item.first);
		}

		try {
			PtSim::Performance a(_name, _brandList, Protra::Lib::Data::TimeFrame::Daily);
			a.Calculate(logData, option);

			if (option->count("-o") != 0) {
				Protra::Lib::Data::DataWriter::WriteLog(option->at("-o"), _brandList, logData);
			}
			if (option->count("-s") != 0) {
				Protra::Lib::Data::DataWriter::WriteCSVLog(option->at("-s"), _brandList, logData);
			}
			excuted = 1;
		}
		catch (...) {

		}

	}

};


#endif


