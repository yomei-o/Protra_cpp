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

#ifndef DF_TOKEN_H_
#define DF_TOKEN_H_

#include <string>

#undef EOF

namespace Protra {
namespace Lib {
namespace Lang {
    
/// <summary>
/// 字句の型を表す列挙型。
/// </summary>
    enum TokenType
    {
        Int,
        Float,
        String,
        LocalVariable,
        GlobalVariable,
        FunctionName,
        Reserved,
        Type,
        Operator,
        Unknown,
        EOF,
    };

    class Token
    {
    public:
        Token()
        {
            Type = TokenType::EOF;
            LineNo = 0;
        }
        Token(const Token& obj) {
            Type = obj.Type;
            LineNo = obj.LineNo;
            Filename = obj.Filename;
            Value = obj.Value;
        }
        Token& operator=(const Token& obj) {
            Type = obj.Type;
            LineNo = obj.LineNo;
            Filename = obj.Filename;
            Value = obj.Value;
            return *this;
        }
        int IntValue() {
            int ret = 0;
            sscanf(Value.c_str(),"%d", &ret);
            return ret;
        }
        double FloatValue() {
            double  ret= 0.0;
            sscanf(Value.c_str(),"%lf", &ret);
            return ret;
        }
        TokenType Type;
        int LineNo;
        std::string Filename;
        std::string Value;
        Token& Next()
        {
            static Token st;
            return st;
        }
    };

}
}
}

#endif



