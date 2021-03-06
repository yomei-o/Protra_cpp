// Copyright (C) 2022 Yomei Otani <yomei.otani@gmail.com>
// Copyright (C) 2008, 2013 panacoran <panacoran@users.sourceforge.jp>
// Copyright (C) 2011 Daisuke Arai <darai@users.sourceforge.jp>
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

#ifndef DF_SYSTEMEXECUTOR_H_
#define DF_SYSTEMEXECUTOR_H_

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
#include "DataReader.h"
#include "WhileStatementNode.h"
namespace PtSim
{


	class SystemExcutor {
	public:
		std::string _name;
		std::shared_ptr<Protra::Lib::Lang::Interpreter> _interpreter;
		std::shared_ptr < Protra::Lib::Config::BrandList> _brandList;
		std::shared_ptr< Protra::Lib::Data::LogData> logData;
		int _timeFrame;
		int initialized;
		int excuted;

		SystemExcutor(std::string name, std::shared_ptr<Protra::Lib::Config::BrandList> bl, int timeFrame)
		{
			initialized = 0;
			excuted = 0;
			_name = name;
			_brandList = bl;
			_timeFrame = timeFrame;

			std::shared_ptr<Protra::Lib::Data::BrandData>& bd = Protra::Lib::GlobalEnv::BrandData();
			bd = std::shared_ptr<Protra::Lib::Data::BrandData>(new Protra::Lib::Data::BrandData());
			bd->Load();
			logData = std::shared_ptr< Protra::Lib::Data::LogData>(new Protra::Lib::Data::LogData(_name, _timeFrame));
			initialized = 1;
		}
		void LoopBrandAndDate(std::shared_ptr<std::map<std::string, std::string> > option)
		{
			if (option->count("logfile") != 0) {
				excuted = 1;
				return;
			}

			_interpreter = std::shared_ptr<Protra::Lib::Lang::Interpreter>(new Protra::Lib::Lang::Interpreter(_name));
			if (_interpreter->initialized == 0)return;
			if (_brandList->List->size() == 0)return;

			int bl_sz = (int)_brandList->List->size();
			for (int i = 0; i < bl_sz; i++) {
				std::shared_ptr< Protra::Lib::Lang::Builtins::Builtins> btin;
				Protra::Lib::Lang::Builtins::BasicBuiltins* bb;
				std::shared_ptr< Protra::Lib::Lang::Builtins::Builtins> stin;
				Protra::Lib::Lang::Builtins::SimulateBuiltins* sb;

				std::shared_ptr<Protra::Lib::Data::PriceList> prices;
				prices = Protra::Lib::Data::PriceData::GetPrices(_brandList->List->at(i), Protra::Lib::Data::TimeFrame::Daily);
				if (prices == nullptr) {
					prices = Protra::Lib::Data::PriceData::GetPricesCSV(_brandList->List->at(i), Protra::Lib::Data::TimeFrame::Daily);
				}
				if (prices == nullptr)continue;

				btin = Protra::Lib::Lang::Builtins::BasicBuiltins::Init(_interpreter->_resource->Builtins);
				bb = (Protra::Lib::Lang::Builtins::BasicBuiltins*)(btin.get());

				bb->Index = 0;
				bb->RightIndex = prices->Count() - 1;
				bb->Prices(prices);

				stin = Protra::Lib::Lang::Builtins::SimulateBuiltins::Init(_interpreter->_resource->Builtins);
				sb = (Protra::Lib::Lang::Builtins::SimulateBuiltins*)(stin.get());

				sb->Index = 0;
				sb->BrandList = _brandList;
				sb->System = _name;
				sb->LogData = logData;
				sb->Prices(prices);

				_interpreter->GlobalVariableTable().clear();

				if (prices == nullptr)continue;

				for (int j = 0; j < prices->Count(); j++)
				{
					bb->Index = j;
					sb->Index = j;
					_interpreter->Execute();
					if (_interpreter->executed == 0)break;
				}
				if (_interpreter->executed == 0)break;
			}
			if (_interpreter->executed == 0)return;
			try {
				if (option->count("savetrading") != 0) {
					Protra::Lib::Data::DataWriter::WriteLog(option->at("savetrading"), _brandList, logData);
				}
				if (option->count("savetradingcsv") != 0) {
					Protra::Lib::Data::DataWriter::WriteCSVLog(option->at("savetradingcsv"), _brandList, logData);
				}
				if (option->count("appendlog") != 0) {
					Protra::Lib::Data::DataWriter::WriteCSVLog(option->at("appendlog"), _brandList, logData,1);
				}
				excuted = 1;
			}
			catch (...) {
				printf("loop brand data runtime error  \n");
			}
		}
		void Performance(std::shared_ptr<std::map<std::string, std::string> > option)
		{
			try {
				if (option->count("appendlog") != 0)return;
				if (option->count("logfile") != 0) {
					Protra::Lib::Data::DataReader::ReadCSVLog(option->at("logfile"), logData,_brandList);
				}
				PtSim::Performance a(_name, _brandList, _timeFrame);
				a.Calculate(logData, option);
			}
			catch (...) {
				printf("performance runtime error  \n");
			}
		}
		static void ClearInterpretor() {
			Protra::Lib::Lang::WhileStatementNode::clear_timeout();
		}
		static void StopInterpretor() {
			Protra::Lib::Lang::WhileStatementNode::set_timeout();
		}

	};

}

#endif


