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

#ifndef DF_SCANNER_H_
#define DF_SCANNER_H_
#include <list>
#include <stdexcept>
#include "Buffer.h"
#include "Token.h"
#include "ParseException.h"

//#define DEBUG_PRINT_TOKEN 

namespace Protra {
namespace Lib{
namespace Lang{

    class Scanner
    {
    public:
        std::regex LocalVarRegex = std::regex("^[a-z][a-zA-Z_0-9]*");
        std::regex GlobalVarRegex = std::regex("^\\$[a-zA-Z_0-9]+");
        std::regex FunctionNameRegex = std::regex("^[A-Z][a-zA-Z_0-9]*");
        std::regex FloatRegex = std::regex("^(?:[1-9][0-9]*|0)\\.[0-9]+");
        std::regex IntRegex = std::regex("^(?:[1-9][0-9]*|0)");
        Buffer _buffer;
        std::list<Token> _tokens;
        bool _disposed;

        Token _Token;
        std::map<std::string, std::string> MagicComment;

        Scanner(std::string file) :_buffer(file, MagicComment)
        {
            _disposed = false;
        }

        Token NextToken()
        {
            int res;
            std::smatch m;

            _buffer.Next();
            Token token = Token();
            token.Filename = _buffer.Filename();
            token.LineNo = _buffer.LineNo();
            if (_buffer._Line == "")
            {
                token.Value = "";
                token.Type = TokenType::EOF;
                return token;
            }
            res = std::regex_search(_buffer._Line.cbegin() + _buffer._Column,
                _buffer._Line.cend(), m, LocalVarRegex);
            if (res)
            {
                token.Value = m[0].str();
                if (token.Value == "if" || token.Value == "else" ||
                    token.Value == "elsif" || token.Value == "while" ||
                    token.Value == "def" || token.Value == "null")
                {
                    token.Type = TokenType::Reserved;
                }
                else if (
                    token.Value == "int" || token.Value == "float" ||
                    token.Value == "string") {
                    token.Type = TokenType::Type;
                }
                else {
                    token.Type = TokenType::LocalVariable;
                }
                _buffer._Column += (int)m.length();
                return token;
            }
            res = std::regex_search(_buffer._Line.cbegin() + _buffer._Column,
                _buffer._Line.cend(), m, GlobalVarRegex);
            if (res)
            {
                token.Type = TokenType::GlobalVariable;
                token.Value = m[0].str();
                _buffer._Column += (int)m.length();
                return token;
            }
            res = std::regex_search(_buffer._Line.cbegin() + _buffer._Column,
                _buffer._Line.cend(), m, FunctionNameRegex);
            if (res)
            {
                token.Type = TokenType::FunctionName;
                token.Value = m[0].str();
                _buffer._Column += (int)m.length();
                return token;
            }
            res = std::regex_search(_buffer._Line.cbegin() + _buffer._Column,
                _buffer._Line.cend(), m, FloatRegex);
            if (res)
            {
                token.Type = TokenType::Float;
                token.Value = m[0].str();
                _buffer._Column += (int)m.length();
                return token;
            }
            res = std::regex_search(_buffer._Line.cbegin() + _buffer._Column,
                _buffer._Line.cend(), m, IntRegex);
            if (res)
            {
                token.Type = TokenType::Int;
                token.Value = m[0].str();
                _buffer._Column += (int)m.length();
                return token;
            }
            switch (_buffer._Line[_buffer._Column])
            {
            case ',':
            case ';':
            case '(':
            case ')':
            case '{':
            case '}':
            case '[':
            case ']':
            case '+':
            case '-':
            case '*':
            case '/':
            case '%':
                token.Type = TokenType::Operator;
                token.Value = _buffer._Line.substr(_buffer._Column, 1);
                _buffer._Column++;
                return token;
            case '&':
                token.Type = TokenType::Operator;
                token.Value = "&";
                _buffer._Column++;
                if (_buffer._Column < _buffer._Line.size() &&
                    _buffer._Line[_buffer._Column] == '&')
                {
                    token.Value = "&&";
                    _buffer._Column++;
                }
                return token;
            case '|':
                token.Type = TokenType::Operator;
                token.Value = "|";
                _buffer._Column++;
                if (_buffer._Column < _buffer._Line.size() &&
                    _buffer._Line[_buffer._Column] == '|')
                {
                    token.Value = "||";
                    _buffer._Column++;
                }
                return token;
            case '<':
            case '>':
            case '!':
            case '=':
                token.Type = TokenType::Operator;
                token.Value = _buffer._Line.substr(_buffer._Column, 1);
                _buffer._Column++;
                if (_buffer._Line[_buffer._Column] == '=')
                {
                    token.Value += "=";
                    _buffer._Column++;
                }
                return token;
            case '"':
                token.Type = TokenType::String;
                int start = ++_buffer._Column;
                while (_buffer._Column < _buffer._Line.size() &&
                    _buffer._Line[_buffer._Column] != '"')
                    _buffer._Column++;
                if (_buffer._Column >= _buffer._Line.size()) {
					throw std::runtime_error(ParseException("string is not closed.",token));

					token.Type = TokenType::Unknown;
                    token.Value = "";
                    return token;
                }
                token.Value = _buffer._Line.substr(start, _buffer._Column++ - start);
                return token;
            }
            token.Type = TokenType::Unknown;
            token.Value = "";
            return token;
        }
        Token Peek()
        {
            Token token = NextToken();
            _tokens.push_back(token);
            return token;
        }
        static void printToken(Token& tk) {
            printf("Tokken \"%s\" %s:%d  \n",tk.Value.c_str(), tk.Filename.c_str(), tk.LineNo);
        }
        bool Scan()
        {
            if (_tokens.size() > 0)
            {
                _Token = _tokens.front();
#ifdef DEBUG_PRINT_TOKEN 
                printToken(_Token);
#endif
                _tokens.pop_front();
                return true;
            }
            _Token = NextToken();
#ifdef DEBUG_PRINT_TOKEN 
            printToken(_Token);
#endif
            return _Token.Type != TokenType::EOF;
        }
    };

}
}
}

#endif



