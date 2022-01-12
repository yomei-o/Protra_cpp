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

#ifndef DF_LITERALNODE_H_
#define DF_LITERALNODE_H_


#include "ExpressionNode.h"
#include "Value.h"

namespace Protra {
namespace Lib {
namespace Lang {

class LiteralNode : public ExpressionNode
{
public:
    std::shared_ptr<Value> _val;

    virtual ~LiteralNode() {

    }
    LiteralNode(){

    }
    LiteralNode(std::shared_ptr<Value> val)
    {
        _val = val;
    }
    std::shared_ptr<ExpressionNode> Parse(std::shared_ptr<ExpressionNode>& that,Scanner& scanner)override
    {
        Token = scanner._Token;
        switch (Token.Type)
        {
        case TokenType::Int:
            _val = std::shared_ptr<Value>(new Value(Token.IntValue()));
            break;
        case TokenType::Float:
            _val = std::shared_ptr<Value>(new Value(Token.FloatValue()));
            break;
        case TokenType::String:
            _val = std::shared_ptr<Value>(new Value(Token.Value));
            break;

        }

        //yomei add
        if (Token.Value == "null") {
            _val = std::shared_ptr<Value>(new Value());
        }

        scanner.Scan();
        return that;
    }

    std::shared_ptr<Value> Evaluate(std::shared_ptr<ExpressionNode>& that,Resource& resource, int at, std::string& ats)override
    {
        return _val;
    }

};

}
}
}


#endif



