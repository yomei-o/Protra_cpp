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

class SystemExcutor {
public:
	std::string _name;
	std::shared_ptr<Protra::Lib::Lang::Interpreter> _interpreter;
	std::shared_ptr < Protra::Lib::Config::BrandList> _brandList;
	int _timeFrame;
	int initialized;
	int excuted;

	SystemExcutor(std::string name, std::shared_ptr<Protra::Lib::Config::BrandList> bl,int timeFrame)
	{
		initialized = 0;
		excuted = 0;
		_name = name;
		_brandList = bl;
		_timeFrame = timeFrame;

		std::shared_ptr<Protra::Lib::Data::BrandData>& bd = Protra::Lib::GlobalEnv::BrandData();
		bd=std::shared_ptr<Protra::Lib::Data::BrandData>(new Protra::Lib::Data::BrandData());
		bd->Load();
		initialized = 1;
	}
	void LoopBrandAndDate()
	{
		std::shared_ptr< Protra::Lib::Data::LogData> logData;
		logData = std::shared_ptr< Protra::Lib::Data::LogData>(new Protra::Lib::Data::LogData(_name, _timeFrame));

		_interpreter = std::shared_ptr<Protra::Lib::Lang::Interpreter>(new Protra::Lib::Lang::Interpreter(_name));
		if (_interpreter->initialized == 0)return;
		if (_brandList->List->size() == 0)return;

		int bl_sz = (int)_brandList->List->size();
		for (int i = 0;  i < bl_sz; i++) {
			std::shared_ptr< Protra::Lib::Lang::Builtins::Builtins> btin;
			Protra::Lib::Lang::Builtins::BasicBuiltins* bb;
			std::shared_ptr< Protra::Lib::Lang::Builtins::Builtins> stin;
			Protra::Lib::Lang::Builtins::SimulateBuiltins* sb;

			std::shared_ptr<Protra::Lib::Data::PriceList> prices;
			prices = Protra::Lib::Data::PriceData::GetPrices(_brandList->List->at(i), Protra::Lib::Data::TimeFrame::Daily);
			if (prices == nullptr)continue;

			btin=Protra::Lib::Lang::Builtins::BasicBuiltins::Init(_interpreter->_resource->Builtins);
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

			for (int j=0;j < prices->Count(); j++)
			{
				bb->Index=j;
				sb->Index = j;
				_interpreter->Execute();
				if (_interpreter->executed == 0)break;
			}
			if (_interpreter->executed == 0)break;
		}
		if (_interpreter->executed == 0)return;

		{
			PtSim::Performance a(_name,_brandList,_timeFrame);
			a.Calculate(logData);
		}
		excuted = 1;
	}

};


#endif


