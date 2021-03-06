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

#ifndef DF_ARRAYNODE_H_
#define DF_ARRAYNODE_H_

#include "ExpressionNode.h"

namespace Protra {
namespace Lib {
 namespace Lang {

class ArrayNode : public ExpressionNode
{
public:
    std::shared_ptr<ExpressionNode> _node;


    std::shared_ptr<ExpressionNode> Parse(std::shared_ptr<ExpressionNode>& that, Scanner& scanner)override
    {
        Token = scanner._Token;
        scanner.Scan();
        _node = std::shared_ptr<ExpressionNode>(new ExpressionNode());
        _node = _node->Parse(_node,scanner);
        if (scanner._Token.Value != "]") {
            throw std::runtime_error(ParseException("']' expected", scanner._Token));
        }
        scanner.Scan();
#if 0
        scanner._Token.Value = ";";
#endif
        return that;
    }
    std::shared_ptr<Value> Evaluate(std::shared_ptr<ExpressionNode>& that, Resource& resource, int at, std::string& ats)override
    {
        std::shared_ptr<Value>val = _node->Evaluate(_node,resource, at, ats);
        if (val == nullptr || val->ValueType != ValueType::Int) {
            throw new std::runtime_error(ParseException("invalid array size.", Token));
        }
        std::shared_ptr<Value> tmp;
        tmp=std::shared_ptr<Value>(new Value(ValueType::Array, (int)val->toInt()));
        return tmp;
#if 0
        return std::shared_ptr<Value>(new Value(false));
#endif
    }
};

}
}
}

#endif

