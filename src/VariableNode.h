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

#ifndef DF_VARIABLENODE_H_
#define DF_VARIABLENODE_H_

#include "ExpressionNode.h"

namespace Protra {
namespace Lib {
 namespace Lang {

class VariableNode : public ExpressionNode
{
public:
    std::vector<std::shared_ptr<ExpressionNode> > _nodeList;
    std::vector<char> _opCharList;

    VariableNode()
    {
        isVariableNode = true;
    }
    std::shared_ptr<ExpressionNode> Parse(std::shared_ptr<ExpressionNode>& that, Scanner& scanner)override
    {
        Token = scanner._Token;
        scanner.Scan();
#if 0
        scanner._Token.Value = ";";
#endif
        return that;
    }
    std::shared_ptr<Value> Evaluate(std::shared_ptr<ExpressionNode>& that, Resource& resource, int at, std::string& ats)override
    {
        std::shared_ptr<Value> value;
        if (Token.Type == TokenType::GlobalVariable) {
            value = resource.GlobalVariableTable[Token.Value];
            if (value == nullptr) {
                value = std::shared_ptr<Value>(new Value());
            }
            return value;
        }

        std::shared_ptr<std::map<std::string, std::shared_ptr<Value> > > m_ = resource.Stack[resource.Stack.size()-1];
        std::map<std::string, std::shared_ptr<Value> >& m = *m_.get();
        value = m[Token.Value];
        if (value != nullptr) {
            return value;
        }
        {
            char buf[256];
            snprintf(buf,1024,"undefined local variable '%s'",Token.Value.c_str());
            throw std::runtime_error(ParseException(buf, Token));
        }
#if 0
        return std::shared_ptr<Value>(new Value(false));
#endif
    }
    std::shared_ptr<Value> Assign(std::shared_ptr<ExpressionNode>& that,Resource& resource, int at, std::string& ats, std::shared_ptr<Value>& val)override
    {
        if (Token.Type == TokenType::GlobalVariable) {
            resource.GlobalVariableTable[Token.Value] = val;
        }
        else {
            std::shared_ptr<std::map<std::string, std::shared_ptr<Value> > > m_ = resource.Stack[resource.Stack.size() - 1];
            std::map<std::string, std::shared_ptr<Value> >& m = *m_.get();
            m[Token.Value] = val;
        }
        return val;
    }
    };

}
}
}


#endif



