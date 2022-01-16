// Copyright (C) 2022 Yomei Otani <yomei.otani@gmail.com>
// Copyright(C) 2010, 2013, 2014 panacoran <panacoran@users.sourceforge.jp>
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
// $Id: PriceData.cs 550 2021-01-10 05:21:56Z darai $

#ifndef DF_PRICEDATA_H_
#define DF_PRICEDATA_H_

#include <string>
#include "DateTime.h"
#include "BinaryReader.h"
#include "BrandData.h"
#include "Global.h"

namespace Protra {
namespace Lib{
namespace Data {

class Price
{
public:
    int RecordSize;
    std::string Code;
    std::string Market;
    DateTime Date;
    int Open;
    int High;
    int Low;
    int Close;
    double Volume;

    Price()
    {
        RecordSize = 4;
        Open=0;
        High=0;
        Low=0;
        Close=0;
        Volume=0;
    }
    void Split(double ratio)
    {
        Open = (int)(Open / ratio);
        High = (int)(High / ratio);
        Low = (int)(Low / ratio);
        Close = (int)(Close / ratio);
        Volume *= ratio;
    }
    void Read(BinaryReader& b)
    {
        Date = DateTime(b.ReadInt32());
        Open = b.ReadInt32();
        High = b.ReadInt32();
        Low = b.ReadInt32();
        Close = b.ReadInt32();
        Volume = b.ReadDouble();
    }
};

enum TimeFrame
{
    Daily,
    Weekly
};

class PriceList
{
public:
    std::shared_ptr<std::vector<std::shared_ptr<Price> > >_priceList;
    int TimeFrame;
    std::shared_ptr<Price> First()
    {
        std::shared_ptr<class Price> ret;
        if (_priceList->size() == 0)return ret;
        ret = _priceList->at(0);
        return ret;
    }

    std::shared_ptr<Price>Last()
    {
        int c;
        std::shared_ptr<class Price> ret;
        c = (int)_priceList->size();
        if (c == 0)return ret;
        ret = _priceList->at(c - 1);
        return ret;
    }
    int Count()
    {
        return (int)_priceList->size();
    }
    PriceList(std::shared_ptr<std::vector<std::shared_ptr<class Price> > >prices,int timeFrame)
    {
        _priceList = prices;
        TimeFrame = timeFrame;
    }

    std::shared_ptr<Price> Price(int index)
    {
        std::shared_ptr<class Price> ret;
        if (index < 0 || index >= _priceList->size())return ret;
        ret=_priceList->at(index);
        return ret;
    }
    int SearchByDate(DateTime& date)
    {
        int c;
        c = (int)_priceList->size();
        for (int i = 0; i < c; i++) {
            if (_priceList->at(i)->Date == date) {
                return i;
            }
        }
        return -1;
    }
};

class PriceData
{
public:
    static DateTime MaxDate()
    {
        static int cashe_maxdate=0;
        if (cashe_maxdate) {
            return DateTime(cashe_maxdate);
        }
        BinaryReader b = BinaryReader("MaxDate");
        if (b.isExist() == false) {
            return DateTime(0);
        }
        cashe_maxdate = b.ReadInt32();
        return DateTime(cashe_maxdate);
    }

    static std::shared_ptr<PriceList> GetPrices(std::string code,int timeFrame, bool needLastWeek = false)
    {
        std::shared_ptr<PriceList> ret;

        std::shared_ptr<std::vector<std::shared_ptr<Price> > > prices;
        prices = std::shared_ptr<std::vector<std::shared_ptr<Price> > >(new(std::vector<std::shared_ptr<Price> >));
        {
            BinaryReader b(code);
            if (b.isExist() == false)return ret;

            while (b.Position() < b.Length())
            {
                std::shared_ptr<Price> p;
                p = std::shared_ptr <class Price>(new class Price());
                p->Code=code;
                p->Read(b);
                prices->push_back(p);
            }
        }
        std::shared_ptr<BrandData> branddata=GlobalEnv::BrandData();
        if (branddata == nullptr)return ret;
        std::shared_ptr <Brand> brand=branddata->Brand(code);
        if (brand == nullptr)return ret;

        int sz = (int)brand->Split.size();
        for (int i = 0; i < sz; i++) {
            Split split = brand->Split[i];
            if (split.Date.Value > prices->at(prices->size() - 1)->Date.Value) {
                continue;
            }
            std::shared_ptr<Price> price;
            int sszz = (int)prices->size();
            for (int ii = 0; ii < sszz; ii++) {
                price = prices->at(ii);
                if (price->Date.Value < split.Date.Value) {
                    price->Split(split.Ratio);
                }
                else {
                    break;
                }
            }
        }
        if (timeFrame == TimeFrame::Daily) {
            ret = std::shared_ptr<PriceList>(new PriceList(prices, needLastWeek));
            return ret;
        }
        ret= GenerateWeeklyPrices(prices, needLastWeek);
        return ret;
    }
    static std::shared_ptr<PriceList> GenerateWeeklyPrices(std::shared_ptr<std::vector<std::shared_ptr<Price> > >& daily, bool needLastWeek)
    {
        //TODO
        std::shared_ptr<PriceList> ret;
        return ret;
    }

};


}
}
}



#endif


#if 0

namespace Protra.Lib.Data
{
    public class PriceData
    {
        public static PriceList GetPrices(string code, TimeFrame timeFrame, bool needLastWeek = false)
        {
            var file = PricePath(code);
            if (!File.Exists(file))
                return null;
            var prices = new List<Price>();
            using (var s = new FileStream(file, FileMode.Open))
                try
                {
                    var buf = new byte[s.Length];
                    s.Read(buf, 0, (int)s.Length);
                    var b = new BinaryReader(new MemoryStream(buf));
                    var baseStream = b.BaseStream;
                    while (baseStream.Position != baseStream.Length)
                    {
                        var p = new Price {Code = code};
                        p.Read(b);
                        prices.Add(p);
                    }
                }
                catch (EndOfStreamException)
                {
                }
            foreach (var split in GlobalEnv.BrandData[code].Split)
            {
                if (split.Date > prices[prices.Count - 1].Date)
                    continue;
                foreach (var price in prices)
                    if (price.Date < split.Date)
                        price.Split(split.Ratio);
                    else
                        break;
            }
            return timeFrame == TimeFrame.Daily
                ? new PriceList(prices, TimeFrame.Daily)
                : GenerateWeeklyPrices(prices, needLastWeek);
        }

        private static PriceList GenerateWeeklyPrices(List<Price> daily, bool needLastWeek)
        {
            if (daily.Count == 0) // 空のデータファイルが存在する場合。
                return new PriceList(daily, TimeFrame.Weekly);
            var weekly = new List<Price>();
            var code = daily[0].Code;
            var date = daily[0].Date;
            var open = 0;
            var high = 0;
            var low = 0;
            var close = 0;
            double volume = 0;
            var prevDow = DayOfWeek.Sunday;
            foreach (var d in daily)
            {
                if (prevDow > d.Date.DayOfWeek)
                {
                    var w = new Price
                    {
                        Code = code,
                        Date = date,
                        Open = open,
                        High = high,
                        Low = low,
                        Close = close,
                        Volume = volume
                    };
                    weekly.Add(w);
                    //次の週のデータを用意する。
                    date = d.Date;
                    open = d.Open;
                    high = d.High;
                    low = d.Low;
                    close = d.Close;
                    volume = d.Volume;
                }
                else
                {
                    if (d.High > high)
                        high = d.High;
                    if (low == 0 || (d.Low > 0 && d.Low < low))
                        low = d.Low;
                    if (open == 0) // 最初に付いた値段が始値
                        open = d.Open;
                    if (d.Close != 0)
                        close = d.Close;
                    volume += d.Volume;
                }
                prevDow = d.Date.DayOfWeek;
            }

            // 週の最終営業日か、終わっていない週足を返す場合は最後の週足を加える。
            if (Calendar.IsLastOpenDateOfWeek(daily[daily.Count - 1].Date) || needLastWeek)
            {
                var w = new Price
                {
                    Code = code,
                    Date = date,
                    Open = open,
                    High = high,
                    Low = low,
                    Close = close,
                    Volume = volume
                };
                weekly.Add(w);
            }
            return new PriceList(weekly, TimeFrame.Weekly);
        }

        private static readonly Dictionary<string, FileStream> OpenFiles = new Dictionary<string, FileStream>();

        /// <summary>
        /// 価格データを追加する。
        /// </summary>
        /// <param name="price">Priceオブジェクト</param>
        /// <param name="close">ファイルを閉じるか</param>
        public static void Add(Price price, bool close)
        {
            FileStream s;
            if (!OpenFiles.TryGetValue(price.Code, out s))
            {
                var file = PricePath(price.Code);
                s = new FileStream(file, FileMode.OpenOrCreate);
                OpenFiles.Add(price.Code, s);
            }
            if (s.Length >= Price.RecordSize)
            {
                s.Seek(-1 * Price.RecordSize, SeekOrigin.End);
                var last = new Price();
                last.Read(new BinaryReader(s));
                if (price.Date <= last.Date) // すでに存在する。
                    goto Exit;
            }
            price.Write(new BinaryWriter(s));
            Exit:
            if (!close)
                return;
            s.Close();
            OpenFiles.Remove(price.Code);
        }

        /// <summary>
        /// ファイルをすべて閉じる。
        /// </summary>
        public static void CloseAll()
        {
            foreach (var s in OpenFiles.Values)
                s.Close();
            OpenFiles.Clear();
        }

        /// <summary>
        /// 指定された証券コードの最後に更新された日付を返す。
        /// </summary>
        /// <param name="code">証券コード</param>
        /// <returns>日付</returns>
        public static DateTime MaxDateByCode(string code)
        {
            var file = PricePath(code);
            try
            {
                using (var s = new FileStream(file, FileMode.Open))
                {
                    s.Seek(-1 * Price.RecordSize, SeekOrigin.End);
                    var r = new Price();
                    r.Read(new BinaryReader(s));
                    return r.Date;
                }
            }
            catch (IOException)
            {
                return DateTime.MinValue;
            }
        }

        /// <summary>
        /// 指定された日付以降の価格データを削除する。
        /// </summary>
        /// <param name="since">日付</param>
        public static void Delete(DateTime since)
        {
            foreach (var file in CollectFiles(""))
            {
                var s = File.Open(file, FileMode.Open);
                s.Seek(0, SeekOrigin.End);
                var r = new Price();
                try
                {
                    s.Seek(-1 * Price.RecordSize, SeekOrigin.Current);
                    var b = new BinaryReader(s);
                    while (true)
                    {
                        r.Read(b);
                        if (r.Date < since)
                            break;
                        s.Seek(-2 * Price.RecordSize, SeekOrigin.Current);
                    }
                    s.SetLength(s.Seek(0, SeekOrigin.Current));
                }
                catch (IOException)
                {
                }
                finally
                {
                    s.Close();
                }
            }
            MaxDate = since.AddDays(-1);
        }

        /// <summary>
        /// 株価データをCSV形式に変換する。
        /// </summary>
        /// <param name="start">開始する銘柄コードを指定する。</param>
        /// <param name="end">終了する銘柄コードを指定する。</param>
        /// <returns>完了したらtrueを中断したらfalseを返す。</returns>
        public static bool ConvertToCSV(string start, string end)
        {
            var overwriteAll = false;
            foreach (var file in CollectFiles(""))
            {
                var code = Path.GetFileName(file);
                if (String.Compare(code, start, StringComparison.Ordinal) < 0 ||
                    String.Compare(code, end, StringComparison.Ordinal) > 0)
                    continue;
                var prices = GetPrices(code, TimeFrame.Daily);
                if (prices == null)
                    continue;
                if (!overwriteAll && File.Exists(file + ".csv"))
                {
                    using (var dialog = new OverwriteDialog())
                    {
                        dialog.Text = "株価データの保存";
                        dialog.File = file + ".csv";
                        var result = dialog.ShowDialog();
                        if (result == DialogResult.Cancel)
                            return false;
                        if (result == DialogResult.No)
                            continue;
                        if (result == DialogResult.OK)
                            overwriteAll = true;
                    }
                }
                FileStream f;
                Retry:
                try
                {
                    f = new FileStream(file + ".csv", FileMode.Create);
                }
                catch (IOException e)
                {
                    DialogResult result;
                    using (new CenteredDialogHelper())
                        result = MessageBox.Show(e.Message, "株価データの変換", MessageBoxButtons.AbortRetryIgnore);
                    if (result == DialogResult.Abort)
                        return false;
                    if (result == DialogResult.Ignore)
                        continue;
                    goto Retry;
                }
                using (var txt = new StreamWriter(f, Encoding.ASCII))
                {
                    foreach (var p in prices)
                        txt.WriteLine(string.Join(",", new[]
                        {
                            p.Date.ToString("d"), p.Open.ToString(),
                            p.High.ToString(), p.Low.ToString(), p.Close.ToString(), p.Volume.ToString()
                        }));
                }
            }
            return true;
        }

        /// <summary>
        /// CVS形式から株価データに変換する。
        /// </summary>
        /// <param name="start">開始する銘柄コードを指定する。</param>
        /// <param name="end">終了する銘柄コードを指定する。</param>
        /// <returns>完了したらtrueを中断したらfalseを返す。</returns>
        public static bool ConvertFromCSV(string start, string end)
        {
            var overwriteAll = false;
            foreach (var file in CollectFiles(".csv"))
            {
                var code = Path.GetFileNameWithoutExtension(file);
                if (String.Compare(code, start, StringComparison.Ordinal) < 0 ||
                    String.Compare(code, end, StringComparison.Ordinal) > 0)
                    continue;
                var prices = new List<Price>();
                Retry:
                var num = 0;
                try
                {
                    using (var f = new StreamReader(file, Encoding.ASCII))
                    {
                        string line;
                        while ((line = f.ReadLine()) != null)
                        {
                            num++;
                            var token = line.Split(',');
                            var p = new Price
                            {
                                Code = code,
                                Date = DateTime.Parse(token[0]),
                                Open = int.Parse(token[1]),
                                High = int.Parse(token[2]),
                                Low = int.Parse(token[3]),
                                Close = int.Parse(token[4]),
                                Volume = double.Parse(token[5])
                            };
                            prices.Add(p);
                        }
                    }
                }
                catch (FormatException)
                {
                    DialogResult result;
                    using (new CenteredDialogHelper())
                        result = MessageBox.Show(file + "の" + num + "行目に不正な値があります。" +
                                                 "このファイルを無視して処理を継続しますか？", "株価データの変換", MessageBoxButtons.YesNo);
                    if (result == DialogResult.No)
                        return false;
                    continue;
                }
                catch (IOException e)
                {
                    DialogResult result;
                    using (new CenteredDialogHelper())
                        result = MessageBox.Show(e.Message, "株価データの変換", MessageBoxButtons.AbortRetryIgnore);
                    if (result == DialogResult.Abort)
                        return false;
                    if (result == DialogResult.Ignore)
                        continue;
                    goto Retry;
                }
                var dst = file.Substring(0, file.Length - 4);
                if (!overwriteAll && File.Exists(dst))
                {
                    using (var dialog = new OverwriteDialog())
                    {
                        dialog.Text = "株価データの変換";
                        dialog.File = dst;
                        var result = dialog.ShowDialog();
                        if (result == DialogResult.Cancel)
                            return false;
                        if (result == DialogResult.No)
                            continue;
                        if (result == DialogResult.OK)
                            overwriteAll = true;
                    }
                }
                File.Delete(dst);
                foreach (var p in prices)
                    Add(p, false);
                CloseAll();
                var max = MaxDateByCode(code);
                if (max > MaxDate)
                    MaxDate = max;
            }
            return true;
        }

 
    }
}
#endif
