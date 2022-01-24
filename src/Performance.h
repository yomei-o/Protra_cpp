// Copyright (C) 2022 Yomei Otani <yomei.otani@gmail.com>
// Copyright (C) 2003, 2004 Daisuke Arai <darai@users.sourceforge.jp>
// Copyright (C) 2005, 2007, 2008, 2010, 2013 panacoran <panacoran@users.sourceforge.jp>
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
// $Id$

#ifndef DF_PERFORMANCE_H_
#define DF_PERFORMANCE_H_

#include <stdexcept>
#include "BrandListConfig.h"
#include "LogData.h"
#include "PricePairList.h"
#include "PriceData.h"
#include "formatNumber.h"
#include "hookprintf.h"
#include "zengoopen.h"
#include "DataWriter.h"

namespace PtSim
{

class Performance
{
public:
    std::string _name;
    std::shared_ptr<Protra::Lib::Config::BrandList> _brandList;
    int  _timeFrame;
    int _allTrades; // 全トレード数
    int _winTrades; // 勝ちトレード数
    float _allProfitRatio; // 全トレード平均損益率
    float _winProfitRatio; // 勝ちトレード平均利率
    float _winMaxProfitRatio; // 勝ちトレード最大利率
    float _loseMaxLossRatio; // 負けトレード最大損率
    float _allTerm; // 全トレード平均期間
    float _winTerm; // 勝ちトレード平均期間
    float _budget; // 必要資金
    float _bookMaxPosition; // 時価の最大ポジション
    float _marketMaxPosition; // 簿価の最大ポジション
    float _totalProfit; // 総利益
    float _winTotalProfit; // 勝ちトレード総利益
    float _winMaxProfit; // 勝ちトレード最大利益
    float _loseMaxLoss; // 負けトレード最大損失
    int _runningTrades; // 進行中のトレード数
    float _marketMaxDrowDown; // 時価の最大ドローダウン
    float _bookMaxDrowDown; // 簿価の最大ドローダウン
    Protra::Lib::Data::DateTime _firstTrade; // 最初のトレードの日付
    Protra::Lib::Data::DateTime _lastTrade; // 最後のトレードの日付

    Performance(std::string name,std::shared_ptr<Protra::Lib::Config::BrandList> brandList,int timeFrame)
    {
         _name = name;
         _brandList = brandList;
         _timeFrame = timeFrame;

         _allTrades=0;
         _winTrades = 0;
         _allProfitRatio = 0;
         _winProfitRatio = 0;
         _winMaxProfitRatio = 0;
         _loseMaxLossRatio = 0;
         _allTerm = 0;
         _winTerm=0;
         _budget=0;
         _bookMaxPosition = 0;
         _marketMaxPosition = 0;
         _totalProfit=0;
         _winTotalProfit = 0;
         _winMaxProfit = 0;
         _loseMaxLoss = 0;
         _runningTrades = 0;
         _marketMaxDrowDown = 0;
         _bookMaxDrowDown=0;
    }
	void EvaluateTrade(bool isLong, int term, float totalBuy, float totalSell)
	{
		_allTrades++;
		float ratio = isLong ? totalSell / totalBuy - 1 : 1 - totalBuy / totalSell; // 空売りは売りポジションが分母
		_allProfitRatio += ratio;
		_allTerm += term;
		float profit = totalSell - totalBuy;
		_totalProfit += profit;
		if (totalSell > totalBuy) // 勝ち
		{
			_winTrades++;
			_winProfitRatio += ratio;
			_winMaxProfitRatio = std::max(_winMaxProfitRatio, ratio);
			_winMaxProfit = std::max(_winMaxProfit, profit);
			_winTotalProfit += profit;
			_winTerm += term;
		}
		else // 負け
		{
			_loseMaxLossRatio = std::min(_loseMaxLossRatio, ratio);
			_loseMaxLoss = std::min(_loseMaxLoss, profit);
		}
	}
	void CalcMaxPosition(std::shared_ptr<PricePairList> positionValues)
	{
		PricePair max;
		for (int i = 0; i < positionValues->Count(); i++) {
			PricePair value=*positionValues->_sortedList[i].get();
				max = PricePair::Max(max, value);
		}
		_marketMaxPosition = max.Market;
		_bookMaxPosition = max.Book;
	}

	void CalcBudget(std::shared_ptr<PricePairList> profits, std::shared_ptr<PricePairList> positionValues)
	{
		//foreach(var date in profits.Dates)
		for (int i = 0; i < profits->Count(); i++) {
			Protra::Lib::Data::DateTime date = profits->_sortedList[i]->Date;
			_budget = std::max(_budget, positionValues->get(date)->Book - profits->get(date)->Book);
		}
	}
	void CalcDrowdown(std::shared_ptr<PricePairList> profits)
	{
		PricePair maxProfit;
		PricePair maxDrowdown;
		for (int i = 0; i < profits->Count(); i++) {
			PricePair profit = *profits->_sortedList[i].get();
			maxProfit = PricePair::Max(maxProfit, profit);
			maxDrowdown = PricePair::Min(maxDrowdown, profit - maxProfit);
		}
		_marketMaxDrowDown = maxDrowdown.Market;
		_bookMaxDrowDown = maxDrowdown.Book;
	}

	std::shared_ptr<PricePairList> Calculate(std::shared_ptr< Protra::Lib::Data::LogData> logData, std::shared_ptr<std::map<std::string, std::string> > option)
	{
		std::shared_ptr<PricePairList> profits = AnalyzeLogs(logData,option);
		if (profits->Count() == 0) {
			throw std::runtime_error("取引がありません。");
		}
		_firstTrade = profits->_sortedList[0]->Date;
		_lastTrade = profits->_sortedList[profits->_sortedList.size() - 1]->Date;
		PrintResult();
		if (option->count("saveprofit")!=0) {
			std::string fn = option->at("saveprofit");
			std::string msg;
			hookprintf::config::start(hookprintf::HOOK);
			PrintResult();
			msg = hookprintf::config::get_buf();
			hookprintf::config::start(hookprintf::NORMAL);
			FILE* fp = zengo_open(fn.c_str(), "wt", "data");
			if (fp) {
				fprintf(fp,"%s", msg.c_str());
				fclose(fp);
			}
		}
		return profits;
	}
	std::shared_ptr<PricePairList> AnalyzeLogs(std::shared_ptr< Protra::Lib::Data::LogData> logData,std::shared_ptr<std::map<std::string, std::string> > option)
    {
        std::shared_ptr<PricePairList> profits= std::shared_ptr<PricePairList>(new PricePairList);
        std::shared_ptr<PricePairList> positionValues= std::shared_ptr<PricePairList>(new PricePairList);
        int count = 0;

        if (Protra::Lib::Data::PriceData::MaxDate().Value == 0) {
            throw std::runtime_error("株価データがありません。");
        }
        for(int i=0;i<_brandList->List->size();i++)
        {
            std::string code = _brandList->List->at(i);
            std::shared_ptr<Protra::Lib::Data::PriceList>prices = Protra::Lib::Data::PriceData::GetPrices(code, _timeFrame);
            if (prices == nullptr) {
	            prices = Protra::Lib::Data::PriceData::GetPricesCSV(code, _timeFrame);
            }
            if (prices == nullptr) {
                continue;
            }
            std::vector<std::shared_ptr<Protra::Lib::Data::Log> >logs = logData->GetLog(code);
            int logIndex = 0;
            int prevClose = 0;
            int prevHigh = 0;
            int position = 0;
            float totalBuy = 0;
            float totalSell = 0;
            Protra::Lib::Data::DateTime startDate;
            float averagePrice = 0;

			for (int i = 0; i < prices->Count(); i++) {
				std::shared_ptr<Protra::Lib::Data::Price> price;
				price=prices->Price(i);
				auto dailyProfit = profits->get(price->Date);
				auto dailyValue = positionValues->get(price->Date);
				int close = price->Close;
				if (position != 0 && close > 0 && prevClose > 0) {
					dailyProfit->AddMarket(position, close - prevClose); // 時価の前日比を加算する。
				}
				if (close > 0) {
					prevClose = close;
				}
				if (price->High > 0) {
					prevHigh = price->High;
				}
				dailyValue->AddMarket(abs(position), prevHigh);
				std::shared_ptr<Protra::Lib::Data::Log> log;
				if (logIndex == logs.size() || logs[logIndex]->Date != price->Date || // 売買が発生しない。
					(log = logs[logIndex++])->Quantity == 0) {
					// 0株の売買は無視する。
					continue;
				}
				int prevPosition = position;
				float consideration = (float)log->Quantity * log->Price;
				if (log->Order == Protra::Lib::Data::Order::Buy)
				{
					position += log->Quantity;
					totalBuy += consideration;
					if (close > 0) {
						dailyProfit->AddMarket(log->Quantity, close - log->Price);
					}
				}
				else
				{
					position -= log->Quantity;
					totalSell += consideration;
					if (close > 0) {
						dailyProfit->AddMarket(log->Quantity, log->Price - close);
					}
				}
				int _abs = abs(position);
				int prevAbs = abs(prevPosition);
				if ((float)position * prevPosition > 0) // トレード継続
				{
					if (_abs < prevAbs)
					{
						dailyValue->AddBook(log->Quantity, -averagePrice);
						dailyProfit->AddBook(log->Quantity, sign(position) * (log->Price - averagePrice));
					}
					else
					{
						averagePrice = (prevAbs * averagePrice + consideration) / _abs;
						dailyValue->AddBook(consideration);
					}
					continue;
				}
				dailyValue->AddBook(prevAbs, -averagePrice);
				dailyProfit->AddBook(prevPosition, log->Price - averagePrice);
				if (position == 0) // トレード終了
					averagePrice = 0;
				else // ドテンかトレード開始
				{
					dailyValue->AddBook(_abs, log->Price);
					averagePrice = log->Price;
					startDate = log->Date;
					if (prevPosition == 0) // トレード開始
						continue;
				}
				// ドテンの補正
				float realTotalBuy = totalBuy;
				float realTotalSell = totalSell;
				totalBuy = totalSell = 0;
				if (position > 0) {
					realTotalBuy -= (totalBuy = (float)position * log->Price);
				}
				else if (position < 0) {
					realTotalSell -= (totalSell = (float)-position * log->Price);
				}
				EvaluateTrade(log->Order == Protra::Lib::Data::Order::Sell, (log->Date.Value - startDate.Value), realTotalBuy, realTotalSell);
			}
			if (position != 0) {
				_runningTrades++;
			}
		}
		std::shared_ptr<PricePairList> realPositionValues = positionValues->BookAccumulatedList();
        CalcMaxPosition(realPositionValues);
        std::shared_ptr<PricePairList> realProfits = profits->AccumulatedList();
		if (option->count("saveprofitcsv") != 0) {
			std::string fn = option->at("saveprofitcsv");
			Protra::Lib::Data::DataWriter::WriteGraphLog(fn.c_str(), realProfits);
		}
		CalcBudget(realProfits, realPositionValues);
        CalcDrowdown(realProfits);
        return realProfits;
    }
	void PrintResult()
	{
		int loseTrades = _allTrades - _winTrades;
		float loseProfitRatio = _allProfitRatio - _winProfitRatio;
		float loseTerm = _allTerm - _winTerm;
		float loseTotalLoss = _totalProfit - _winTotalProfit;
		
		printf("ファイル: %s\n", _name.c_str());
		printf("株価データ: %s\n", _timeFrame == Protra::Lib::Data::TimeFrame::Daily ? "日足" : "週足");
		printf("銘柄リスト: %s\n", _brandList->Name.c_str());
		printf("%04d/%02d/%02d～%04d/%02d/%02dにおける成績です。\n",
			_firstTrade.Year, _firstTrade.Month, _firstTrade.Day,
			_lastTrade.Year, _lastTrade.Month, _lastTrade.Day);
		printf("----------------------------------------\n");
		printf("全トレード数\t\t%d\n", _allTrades);
		printf("勝ちトレード数(勝率)\t%d(%.2f%%)\n", _winTrades, (float)_winTrades / _allTrades*100);
		printf("負けトレード数(負率)\t%d(%.2f%%)\n", loseTrades, (float)loseTrades / _allTrades*100);
		printf("\n");
		printf("全トレード平均利率\t%s\n", perNanNumber(_allProfitRatio / _allTrades * 100).c_str());
		printf("勝ちトレード平均利率\t%s\n", perNanNumber(_winProfitRatio / _winTrades * 100).c_str());
		printf("負けトレード平均損率\t%s\n", perNanNumber(loseProfitRatio / loseTrades*100).c_str());
		printf("\n");
		printf("勝ちトレード最大利率\t%s\n", perNanNumber(_winMaxProfitRatio * 100).c_str());
		printf("負けトレード最大損率\t%s\n", perNanNumber(_loseMaxLossRatio * 100).c_str());
		printf("\n");
		printf("全トレード平均期間\t%s\n", nanNumber(_allTerm / _allTrades).c_str());
		printf("勝ちトレード平均期間\t%s\n", nanNumber(_winTerm / _winTrades).c_str());
		printf("負けトレード平均期間\t%s\n", nanNumber(loseTerm / loseTrades).c_str());
		printf("----------------------------------------\n");
		printf("必要資金\t\t%s\n", yenFormatNumber((int)_budget).c_str());
		printf("最大ポジション(簿価)\t%s\n", yenFormatNumber((int)_bookMaxPosition).c_str());
		printf("最大ポジション(時価)\t%s\n", yenFormatNumber((int)_marketMaxPosition).c_str());
		printf("\n");
		printf("純利益\t\t\t%s\n", yenFormatNumber((int)(_totalProfit)).c_str());
		printf("勝ちトレード総利益\t%s\n", yenFormatNumber((int)(_winTotalProfit)).c_str());
		printf("負けトレード総損失\t%s\n", yenFormatNumber((int)(loseTotalLoss)).c_str());
		printf("\n");
		printf("全トレード平均利益\t%s\n", yenFormatNumber((int)(_totalProfit / _allTrades)).c_str());
		printf("勝ちトレード平均利益\t%s\n", yenFormatNumber((int)(_winTotalProfit / _winTrades)).c_str());
		printf("負けトレード平均損失\t%s\n", yenFormatNumber((int)(loseTotalLoss / loseTrades)).c_str());
		printf("\n");
		printf("勝ちトレード最大利益\t%s\n", yenFormatNumber((int)(_winMaxProfit)).c_str());
		printf("負けトレード最大損失\t%s\n", yenFormatNumber((int)(_loseMaxLoss)).c_str());
		printf("\n");
		printf("プロフィットファクター\t%s\n", nanNumber(_winTotalProfit / -loseTotalLoss).c_str());
		printf("最大ドローダウン(簿価)\t%s\n", yenFormatNumber((int)(_bookMaxDrowDown)).c_str());
		printf("最大ドローダウン(時価)\t%s\n", yenFormatNumber((int)(_marketMaxDrowDown)).c_str());
		printf("----------------------------------------\n");
		printf("現在進行中のトレード数\t%d\n", _runningTrades);
	}

};

}

#endif