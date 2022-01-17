// Copyright (C) 2022 Yomei Otani <yomei.otani@gmail.com>
// Copyright(C) 2010, 2013 panacoran <panacoran@users.sourceforge.jp>
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

#ifndef DF_LOGDATA_H_
#define DF_LOGDATA_H_

#include "DateTime.h"
namespace Protra {
namespace Lib {
namespace Data {

enum Order
{
    Buy,
    Sell
};

class Log
{
public:
    std::string Code;
    DateTime Date;
    int Price;
    int Quantity;
    int Order;
    int CompareTo(Log& other)
    {
        if (Date.Value != other.Date.Value)return 1;
        return Code == other.Code;
    }

};


class LogData
{
public:
    bool _updated;
    LogData(std::string system, int timeFrame)
    {
    }
    bool Add(std::shared_ptr<Log> log)
    {
        return true;
    }
};


}
}
}




#endif


#if 0
namespace Protra.Lib.Data
{
    /// <summary>
    /// 注文の種類を表す列挙型。
    /// </summary>
    public enum Order
    {
        /// <summary>
        /// 買い。
        /// </summary>
        Buy,

        /// <summary>
        /// 売り。
        /// </summary>
        Sell
    }

    /// <summary>
    /// システムの実行履歴を表すクラス。
    /// </summary>
    public class Log : IComparable<Log>
    {
        /// <summary>
        /// コードを取得または設定する。
        /// </summary>
        public string Code { get; set; }

        /// <summary>
        /// 日付を取得または設定する。
        /// </summary>
        public DateTime Date { get; set; }

        /// <summary>
        /// 価格を取得または設定する。
        /// </summary>
        public int Price { get; set; }

        /// <summary>
        /// 数量を取得または設定する。
        /// </summary>
        public int Quantity { get; set; }

        /// <summary>
        /// 注文の種類を取得または設定する。
        /// </summary>
        public Order Order { get; set; }

        /// <summary>
        /// 指定されたオブジェクトと自分を比較する。
        /// </summary>
        /// <param name="other">比較対象のオブジェクト</param>
        /// <returns>比較結果</returns>
        public int CompareTo(Log other)
        {
            var result = other.Date.CompareTo(Date);
            return result != 0 ? result : String.Compare(other.Code, Code, StringComparison.Ordinal);
        }

        /// <summary>
        /// ファイルから読み込む。
        /// </summary>
        /// <param name="b">ファイルのBinaryReader</param>
        /// <returns></returns>
        public Log Read(BinaryReader b)
        {
            Code = b.ReadString();
            Date = new DateTime((long)b.ReadInt32() * 86400 * 10000000);
            Price = b.ReadInt32();
            Quantity = b.ReadInt32();
            Order = (Order)b.ReadByte();
            return this;
        }

        /// <summary>
        /// ファイルに書き込む。
        /// </summary>
        /// <param name="b">ファイルのBinaryWriter</param>
        public void Write(BinaryWriter b)
        {
            b.Write(Code);
            b.Write((int)(Date.Ticks / 86400 / 10000000));
            b.Write(Price);
            b.Write(Quantity);
            b.Write((byte)Order);
        }
    }

    /// <summary>
    /// システムの実行履歴を操作するクラス。
    /// </summary>
    public class LogData : IDisposable
    {
        private readonly FileStream _file;
        private bool _updated;

        private readonly SortedList<string, SortedList<DateTime, Log>> _data =
            new SortedList<string, SortedList<DateTime, Log>>();

        private bool _disposed;

        /// <summary>
        /// コンストラクタ
        /// </summary>
        /// <param name="system">システムの名前</param>
        /// <param name="timeFrame">タイムフレーム</param>
        public LogData(string system, TimeFrame timeFrame)
        {
            var name = LogPath(system, timeFrame);
            _file = new FileStream(name, FileMode.OpenOrCreate);
            var reader = new BinaryReader(_file);
            try
            {
                while (true)
                {
                    var log = new Log().Read(reader);
                    if (_data.ContainsKey(log.Code))
                        _data[log.Code][log.Date] = log;
                    else
                        (_data[log.Code] = new SortedList<DateTime, Log>())[log.Date] = log;
                }
            }
            catch (EndOfStreamException)
            {
            }
        }

        private static string LogPath(string system, TimeFrame timeFrame)
        {
            if (!Directory.Exists(Global.DirLog))
                Directory.CreateDirectory(Global.DirLog);
            return Path.Combine(Global.DirLog, PathEncoder.Encode(system.Substring(0, system.Length - 3)) + "&" + (int)timeFrame);
        }

        /// <summary>
        /// 指定された実行履歴を取得する。
        /// </summary>
        /// <param name="code">証券コード</param>
        /// <returns>日付順にソートされた実行履歴</returns>
        public List<Log> GetLog(string code)
        {
            return _data.ContainsKey(code) ? new List<Log>(_data[code].Values) : new List<Log>();
        }

        /// <summary>
        /// 指定された実行履歴を取得する。
        /// </summary>
        /// <param name="min">日付の最小値</param>
        /// <param name="max">日付の最大値</param>
        /// <returns>日付の降順にソートされたログ</returns>
        public List<Log> GetLog(DateTime min, DateTime max)
        {
            var logs = new List<Log>();
            foreach (var pair in _data)
            {
                foreach (var log in pair.Value.Values)
                    if (log.Date >= min && log.Date <= max)
                        logs.Add(log);
            }
            logs.Sort();
            return logs;
        }

        /// <summary>
        /// 実行履歴を追加する。
        /// </summary>
        /// <param name="log">追加する実行履歴</param>
        /// <returns>同日の売買があったらfalseを返す。</returns>
        public bool Add(Log log)
        {
            if (!_data.ContainsKey(log.Code))
                _data[log.Code] = new SortedList<DateTime, Log>();
            if (_data[log.Code].ContainsKey(log.Date))
                return false;
            _data[log.Code][log.Date] = log;
            _updated = true;
            return true;
        }

        /// <summary>
        /// 指定された銘柄の実行履歴を削除する。
        /// </summary>
        /// <param name="code">証券コード</param>
        public void Remove(string code)
        {
            _data.Remove(code);
            _updated = true;
        }

        /// <summary>
        /// 実行履歴を空にする。
        /// </summary>
        public void Clear()
        {
            _data.Clear();
            _updated = true;
        }

        /// <summary>
        /// データを保存してファイルを閉じる。
        /// </summary>
        public void Close()
        {
            if (!_updated)
            {
                _file.Close();
                return;
            }
            _file.SetLength(0);
            using (var writer = new BinaryWriter(_file))
            {
                foreach (var list in _data.Values)
                    foreach (var log in list.Values)
                        log.Write(writer);
            }
        }

        /// <summary>
        /// リソースを開放する。
        /// </summary>
        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        /// <summary>
        /// リソースを開放する。
        /// </summary>
        /// <param name="disposing">マネージとアンマネージの両方のリソースを開放するならtrue。アンマネージだけならfalse。</param>
        protected virtual void Dispose(bool disposing)
        {
            if (_disposed)
                return;
            if (disposing)
                Close();
            _disposed = true;
        }

        /// <summary>
        /// 指定された実行履歴を削除する。
        /// </summary>
        /// <param name="system">システムのファイル名</param>
        /// <param name="timeFrame">タイムフレーム</param>
        public static void Delete(string system, TimeFrame timeFrame)
        {
            try
            {
                File.Delete(LogPath(system, timeFrame));
            }
            catch (DirectoryNotFoundException)
            {
            }
        }

        /// <summary>
        /// 実行履歴をすべて削除する。
        /// </summary>
        public static void DeleteAll()
        {
            try
            {
                Directory.Delete(Global.DirLog, true);
            }
            catch (DirectoryNotFoundException)
            {
            }
        }
    }
}
#endif
