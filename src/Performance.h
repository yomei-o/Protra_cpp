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
    std::shared_ptr<PricePairList> AnalyzeLogs(std::shared_ptr< Protra::Lib::Data::LogData> logData)
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
                continue;
            }
            std::vector<std::shared_ptr<Protra::Lib::Data::Log> >logs = logData->GetLog(code);
            int logIndex = 0;
            int prevClose = 0;
            int prevHigh = 0;
            int position = 0;
            float totalBuy = 0;
            float totalSell = 0;
            int startDate = 0;
            float averagePrice = 0;
#if 0
                foreach(var price in prices)
                {
                    if (worker.CancellationPending)
                        return null;
                    var dailyProfit = profits[price.Date];
                    var dailyValue = positionValues[price.Date];
                    var close = price.Close;
                    if (position != 0 && close > 0 && prevClose > 0)
                        dailyProfit.AddMarket(position, close - prevClose); // 時価の前日比を加算する。
                    if (close > 0)
                        prevClose = close;
                    if (price.High > 0)
                        prevHigh = price.High;
                    dailyValue.AddMarket(Math.Abs(position), prevHigh);
                    Log log;
                    if (logIndex == logs.Count || logs[logIndex].Date != price.Date || // 売買が発生しない。
                        (log = logs[logIndex++]).Quantity == 0) // 0株の売買は無視する。
                        continue;
                    var prevPosition = position;
                    var consideration = (float)log.Quantity * log.Price;
                    if (log.Order == Order.Buy)
                    {
                        position += log.Quantity;
                        totalBuy += consideration;
                        if (close > 0)
                            dailyProfit.AddMarket(log.Quantity, close - log.Price);
                    }
                    else
                    {
                        position -= log.Quantity;
                        totalSell += consideration;
                        if (close > 0)
                            dailyProfit.AddMarket(log.Quantity, log.Price - close);
                    }
                    var abs = Math.Abs(position);
                    var prevAbs = Math.Abs(prevPosition);
                    if ((float)position * prevPosition > 0) // トレード継続
                    {
                        if (abs < prevAbs)
                        {
                            dailyValue.AddBook(log.Quantity, -averagePrice);
                            dailyProfit.AddBook(log.Quantity, Math.Sign(position) * (log.Price - averagePrice));
                        }
                        else
                        {
                            averagePrice = (prevAbs * averagePrice + consideration) / abs;
                            dailyValue.AddBook(consideration);
                        }
                        continue;
                    }
                    dailyValue.AddBook(prevAbs, -averagePrice);
                    dailyProfit.AddBook(prevPosition, log.Price - averagePrice);
                    if (position == 0) // トレード終了
                        averagePrice = 0;
                    else // ドテンかトレード開始
                    {
                        dailyValue.AddBook(abs, log.Price);
                        averagePrice = log.Price;
                        startDate = log.Date;
                        if (prevPosition == 0) // トレード開始
                            continue;
                    }
                    // ドテンの補正
                    var realTotalBuy = totalBuy;
                    var realTotalSell = totalSell;
                    totalBuy = totalSell = 0;
                    if (position > 0)
                        realTotalBuy -= (totalBuy = (float)position * log.Price);
                    else if (position < 0)
                        realTotalSell -= (totalSell = (float)-position * log.Price);
                    EvaluateTrade(log.Order == Order.Sell, (log.Date - startDate).Days, realTotalBuy, realTotalSell);
                }
#endif
        }
        //var realPositionValues = positionValues.BookAccumulatedList;
        //CalcMaxPosition(realPositionValues);
        std::shared_ptr<PricePairList> realProfits = profits->AccumulatedList();
        //CalcBudget(realProfits, realPositionValues);
        //CalcDrowdown(realProfits);
        return realProfits;
    }

#if 0
    PricePairList Calculate(BackgroundWorker worker, AppendTextDelegate appendText)
        {
            var profits = AnalyzeLogs(worker);
            if (profits.Count == 0)
                throw new Exception("取引がありません。");
            if (worker.CancellationPending)
                return null;
            _firstTrade = profits.Dates[0];
            _lastTrade = profits.Dates[profits.Count - 1];
            PrintResult(appendText);
            return profits;
        }

        private PricePairList AnalyzeLogs(BackgroundWorker worker)
        {
            var profits = new PricePairList();
            var positionValues = new PricePairList();
            var count = 0;
            if (PriceData.MaxDate == DateTime.MinValue)
                throw new Exception("株価データがありません。");
            using (var logData = new LogData(_name, _timeFrame))
            {
                foreach (var code in _brandList.List)
                {
                    if (worker.CancellationPending)
                        return null;
                    var prices = PriceData.GetPrices(code, _timeFrame);
                    if (prices == null)
                        continue;
                    var logs = logData.GetLog(code);
                    var logIndex = 0;
                    var prevClose = 0;
                    var prevHigh = 0;
                    var position = 0;
                    var totalBuy = 0f;
                    var totalSell = 0f;
                    var startDate = DateTime.MinValue;
                    var averagePrice = 0f;
                    foreach (var price in prices)
                    {
                        if (worker.CancellationPending)
                            return null;
                        var dailyProfit = profits[price.Date];
                        var dailyValue = positionValues[price.Date];
                        var close = price.Close;
                        if (position != 0 && close > 0 && prevClose > 0)
                            dailyProfit.AddMarket(position, close - prevClose); // 時価の前日比を加算する。
                        if (close > 0)
                            prevClose = close;
                        if (price.High > 0)
                            prevHigh = price.High;
                        dailyValue.AddMarket(Math.Abs(position), prevHigh);
                        Log log;
                        if (logIndex == logs.Count || logs[logIndex].Date != price.Date || // 売買が発生しない。
                            (log = logs[logIndex++]).Quantity == 0) // 0株の売買は無視する。
                            continue;
                        var prevPosition = position;
                        var consideration = (float)log.Quantity * log.Price;
                        if (log.Order == Order.Buy)
                        {
                            position += log.Quantity;
                            totalBuy += consideration;
                            if (close > 0)
                                dailyProfit.AddMarket(log.Quantity, close - log.Price);
                        }
                        else
                        {
                            position -= log.Quantity;
                            totalSell += consideration;
                            if (close > 0)
                                dailyProfit.AddMarket(log.Quantity, log.Price - close);
                        }
                        var abs = Math.Abs(position);
                        var prevAbs = Math.Abs(prevPosition);
                        if ((float)position * prevPosition > 0) // トレード継続
                        {
                            if (abs < prevAbs)
                            {
                                dailyValue.AddBook(log.Quantity, -averagePrice);
                                dailyProfit.AddBook(log.Quantity, Math.Sign(position) * (log.Price - averagePrice));
                            }
                            else
                            {
                                averagePrice = (prevAbs * averagePrice + consideration) / abs;
                                dailyValue.AddBook(consideration);
                            }
                            continue;
                        }
                        dailyValue.AddBook(prevAbs, -averagePrice);
                        dailyProfit.AddBook(prevPosition, log.Price - averagePrice);
                        if (position == 0) // トレード終了
                            averagePrice = 0;
                        else // ドテンかトレード開始
                        {
                            dailyValue.AddBook(abs, log.Price);
                            averagePrice = log.Price;
                            startDate = log.Date;
                            if (prevPosition == 0) // トレード開始
                                continue;
                        }
                        // ドテンの補正
                        var realTotalBuy = totalBuy;
                        var realTotalSell = totalSell;
                        totalBuy = totalSell = 0;
                        if (position > 0)
                            realTotalBuy -= (totalBuy = (float)position * log.Price);
                        else if (position < 0)
                            realTotalSell -= (totalSell = (float)-position * log.Price);
                        EvaluateTrade(log.Order == Order.Sell, (log.Date - startDate).Days, realTotalBuy, realTotalSell);
                    }
                    if (position != 0)
                        _runningTrades++;
                    worker.ReportProgress(100 * ++count / _brandList.List.Count);
                }
            }
            var realPositionValues = positionValues.BookAccumulatedList;
            CalcMaxPosition(realPositionValues);
            var realProfits = profits.AccumulatedList;
            CalcBudget(realProfits, realPositionValues);
            CalcDrowdown(realProfits);
            return realProfits;
        }

        private void EvaluateTrade(bool isLong, int term, float totalBuy, float totalSell)
        {
            _allTrades++;
            var ratio = isLong ? totalSell / totalBuy - 1 : 1 - totalBuy / totalSell; // 空売りは売りポジションが分母
            _allProfitRatio += ratio;
            _allTerm += term;
            var profit = totalSell - totalBuy;
            _totalProfit += profit;
            if (totalSell > totalBuy) // 勝ち
            {
                _winTrades++;
                _winProfitRatio += ratio;
                _winMaxProfitRatio = Math.Max(_winMaxProfitRatio, ratio);
                _winMaxProfit = Math.Max(_winMaxProfit, profit);
                _winTotalProfit += profit;
                _winTerm += term;
            }
            else // 負け
            {
                _loseMaxLossRatio = Math.Min(_loseMaxLossRatio, ratio);
                _loseMaxLoss = Math.Min(_loseMaxLoss, profit);
            }
        }

        private void CalcMaxPosition(PricePairList positionValues)
        {
            var max = new PricePair();
            foreach (var value in positionValues)
                max = PricePair.Max(max, value);
            _marketMaxPosition = max.Market;
            _bookMaxPosition = max.Book;
        }

        private void CalcBudget(PricePairList profits, PricePairList positionValues)
        {
            foreach (var date in profits.Dates)
                _budget = Math.Max(_budget, positionValues[date].Book - profits[date].Book);
        }

// ReSharper disable ParameterTypeCanBeEnumerable.Local
        private void CalcDrowdown(PricePairList profits)
// ReSharper restore ParameterTypeCanBeEnumerable.Local
        {
            var maxProfit = new PricePair();
            var maxDrowdown = new PricePair();
            foreach (var profit in profits)
            {
                maxProfit = PricePair.Max(maxProfit, profit);
                maxDrowdown = PricePair.Min(maxDrowdown, profit - maxProfit);
            }
            _marketMaxDrowDown = maxDrowdown.Market;
            _bookMaxDrowDown = maxDrowdown.Book;
        }

        private void PrintResult(AppendTextDelegate appendText)
        {
            var loseTrades = _allTrades - _winTrades;
            var loseProfitRatio = _allProfitRatio - _winProfitRatio;
            var loseTerm = _allTerm - _winTerm;
            var loseTotalLoss = _totalProfit - _winTotalProfit;
            appendText(string.Format(
                "ファイル: {0}\n" +
                "株価データ: {1}\n" +
                "銘柄リスト: {2}\n" +
                "{3:d}～{4:d}における成績です。\n" +
                "----------------------------------------\n" +
                "全トレード数\t\t{5:d}\n" +
                "勝ちトレード数(勝率)\t{6:d}({7:p})\n" +
                "負けトレード数(負率)\t{8:d}({9:p})\n" +
                "\n" +
                "全トレード平均利率\t{10:p}\n" +
                "勝ちトレード平均利率\t{11:p}\n" +
                "負けトレード平均損率\t{12:p}\n" +
                "\n" +
                "勝ちトレード最大利率\t{13:p}\n" +
                "負けトレード最大損率\t{14:p}\n" +
                "\n" +
                "全トレード平均期間\t{15:n}\n" +
                "勝ちトレード平均期間\t{16:n}\n" +
                "負けトレード平均期間\t{17:n}\n" +
                "----------------------------------------\n" +
                "必要資金\t\t{18:c}\n" +
                "最大ポジション(簿価)\t{19:c}\n" +
                "最大ポジション(時価)\t{20:c}\n" +
                "\n" +
                "純利益\t\t\t{21:c}\n" +
                "勝ちトレード総利益\t\t{22:c}\n" +
                "負けトレード総損失\t\t{23:c}\n" +
                "\n" +
                "全トレード平均利益\t{24:c}\n" +
                "勝ちトレード平均利益\t{25:c}\n" +
                "負けトレード平均損失\t{26:c}\n" +
                "\n" +
                "勝ちトレード最大利益\t{27:c}\n" +
                "負けトレード最大損失\t{28:c}\n" +
                "\n" +
                "プロフィットファクター\t\t{29:n}\n" +
                "最大ドローダウン(簿価)\t{30:c}\n" +
                "最大ドローダウン(時価)\t{31:c}\n" +
                "----------------------------------------\n" +
                "現在進行中のトレード数\t{32:d}\n",
                _name,
                _timeFrame == TimeFrame.Daily ? "日足" : "週足",
                _brandList.Name,
                _firstTrade, _lastTrade,
                _allTrades, _winTrades, (float)_winTrades / _allTrades, loseTrades, (float)loseTrades / _allTrades,
                _allProfitRatio / _allTrades, _winProfitRatio / _winTrades, loseProfitRatio / loseTrades,
                _winMaxProfitRatio, _loseMaxLossRatio,
                _allTerm / _allTrades, _winTerm / _winTrades, loseTerm / loseTrades,
                _budget, _bookMaxPosition, _marketMaxPosition,
                _totalProfit, _winTotalProfit, loseTotalLoss,
                _totalProfit / _allTrades, _winTotalProfit / _winTrades, loseTotalLoss / loseTrades,
                _winMaxProfit, _loseMaxLoss,
                _winTotalProfit / -loseTotalLoss,
                _bookMaxDrowDown, _marketMaxDrowDown,
                _runningTrades));
        }
#endif

};

}

#endif