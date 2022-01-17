#ifndef DF_SYSTEMEXECUTOR_H_
#define DF_SYSTEMEXECUTOR_H_

#include "BrandListConfig.h"
#include "Global.h"
#include "BrandData.h"
#include "PriceData.h"
#include "Protra.h"
#include "BasicBuiltins.h"

class SystemExcutor {
public:
	std::string _name;
	std::shared_ptr<Protra::Lib::Lang::Interpreter> _interpreter;
	std::shared_ptr < Protra::Lib::Config::BrandList> _brandList;

	SystemExcutor(std::string name, std::shared_ptr<Protra::Lib::Config::BrandList> bl)
	{
		_name = name;
		_brandList = bl;

		std::shared_ptr<Protra::Lib::Data::BrandData>& bd = Protra::Lib::GlobalEnv::BrandData();
		bd=std::shared_ptr<Protra::Lib::Data::BrandData>(new Protra::Lib::Data::BrandData());
		bd->Load();

	}
	void LoopBrandAndDate()
	{
		_interpreter = std::shared_ptr<Protra::Lib::Lang::Interpreter>(new Protra::Lib::Lang::Interpreter(_name));

		int bl_sz = (int)_brandList->List->size();
		for (int i = 0;  i < bl_sz; i++) {
			std::shared_ptr< Protra::Lib::Lang::Builtins::Builtins> btin;
			Protra::Lib::Lang::Builtins::BasicBuiltins* bb;

			std::shared_ptr<Protra::Lib::Data::PriceList> prices;
			prices = Protra::Lib::Data::PriceData::GetPrices(_brandList->List->at(i), Protra::Lib::Data::TimeFrame::Daily);
			if (prices == nullptr)continue;

			btin=Protra::Lib::Lang::Builtins::BasicBuiltins::Init(_interpreter->_resource->Builtins);
			bb = (Protra::Lib::Lang::Builtins::BasicBuiltins*)(btin.get());

			bb->Index = 0;
			bb->RightIndex = prices->Count() - 1;
			bb->Prices(prices);
#if 0 
			//TODO
			var builtins = new SimulateBuiltins
			{
				Index = 0,
				System = _name,
				BrandList = _brandList,
				LogData = logData,
				AppendText = appendText,
				Prices = prices,
				RightIndex = prices.Count - 1,
			};
#endif
			_interpreter->GlobalVariableTable().clear();

			if (prices == nullptr)continue;

			for (int j=0;j < prices->Count(); j++)
			{
				bb->Index=j;
				_interpreter->Execute();
			}
		}
	}

};


#endif


