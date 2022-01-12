// Copyright (C) 2003, 2005 Daisuke Arai <darai@users.sourceforge.jp>
// Copyright (C) 2008, 2013 panacoran <panacoran@users.sourceforge.jp>
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

#ifndef DH_BUFFER_H_
#define DH_BUFFER_H_

#include <map>
#include <regex>
#include <memory>
#include "StreamReader.h"

namespace Protra {
namespace Lib {
namespace Lang {

    class Position
    {
    public:
        Position()
        {
            LineNo = 0;
        }
        Position(const Position& o)
        {
            Reader = o.Reader;
            Filename = o.Filename;
            LineNo = o.LineNo;
        }
        Position& operator=(const Position& o)
        {
            Reader = o.Reader;
            Filename = o.Filename;
            LineNo = o.LineNo;
            return (*this);
        }
        std::shared_ptr<StreamReader> Reader;
        std::string Filename;
        int LineNo;
    };

    class Buffer
    {
    public:
        Buffer(std::string file, std::map<std::string, std::string>& magicComment) : _magicComment(magicComment)
        {
            _pos.Reader = std::shared_ptr<StreamReader>(new StreamReader(file));
            _pos.Filename = file;
            _disposed = false;
            _head = true;
            _Column = 0;
        }
        std::string Filename()
        {
            return _pos.Filename;
        }
        int LineNo()
        {
            return _pos.LineNo;
        }
        void ReadLine()
        {
            while ((_Line = _pos.Reader->ReadLine()) == "")
            {
                _pos.Reader->Close();
                if (_posStack.size() == 0)
                    return;
                _pos = _posStack[_posStack.size() - 1];
                _posStack.pop_back();
            }
            _pos.LineNo++;
            _Column = 0;
        }

        void ParseMagicComment(std::string line)
        {
            std::smatch m;
            for (bool ismatch = std::regex_search(line, m, MagicCommentElementRegex);
                ismatch != false;
                ismatch = std::regex_search(m[0].second, m.suffix().second, m, MagicCommentElementRegex))
            {
                //printf("key=\"%s\"  val=\"%s\"  \n", m[1].str().c_str(), m[2].str().c_str());
                _magicComment[m[1].str()] = m[2].str();
            }
        }
        void OpenIncludeFile(std::string name)
        {
            _posStack.push_back(_pos);
            name = name + ".pt";
            _pos.Reader = std::shared_ptr<StreamReader>(new StreamReader(name));
            _pos.LineNo = 0;
            _pos.Filename = name;
        }

        std::regex MagicCommentElementRegex = std::regex("([-\\w]+):\\s+([^;]+)");
        std::regex SkipRegex = std::regex("^\\s*(?://.*|#.*)?");
        std::regex IncludeRegex = std::regex("^\\s*(?:#include\\s*<(.*)>|require\\s*\"(.*)\")");
        std::regex MagicCommentRegex = std::regex("^(?://|#)\\s+([-\\w]+:\\s+[^;]+(;?|(;\\s+[-\\w]+:\\s+[^;]+)+);?)$");

        Position _pos;
        std::vector<Position> _posStack;
        std::map<std::string, std::string>& _magicComment;
        bool _disposed;
        bool _head;
        std::string _Line;
        int _Column;

        void Next()
        {
            do {
                int res;
                std::smatch m;
                if (_Line == "")
                {
                    ReadLine();
                    if (_Line == "")
                        break;
                    res = std::regex_search(_Line, m, MagicCommentRegex);
                    if (_head && res)
                    {
                        ParseMagicComment(m[1].str());
                        _Line = "";
                        continue;
                    }
                    _head = false;

                    res = std::regex_search(_Line, m, IncludeRegex);
                    if(res)
                    {
                            OpenIncludeFile(m[1].str() != "" ? m[1].str() : m[2].str());
                            _Line = "";
                            continue;
                    }

                }
                res = std::regex_search(_Line.cbegin() + _Column, _Line.cend(), m, SkipRegex);
                _Column += (int)m.length();
                if (m.length() == _Line.size()) // スペースとコメントだけなら読み飛ばす。
                    _Line = "";
                else if (_Column == _Line.size() - 1 && (_Line[_Column] == '\\' || _Line[_Column] == '_')) // \と_による継続行の処理。
                    _Line = "";
                else if (_Column == _Line.size())
                {
                    if (_Line[_Column - 1] == ';')
                        _Line = "";
                    else
                    {
                        // ';'で終わっていない改行には;を挿入する。
                        _Line = ";";
                        _Column = 0;
                    }
                }
            } while (_Line == "");
        }
   };

}
}
}
#endif


