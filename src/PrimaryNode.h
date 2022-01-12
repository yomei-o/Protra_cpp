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

#ifndef DF_PRIMARYNODE_H_
#define DF_PRIMARYNODE_H_

#include "ExpressionNode.h"
#include "VariableNode.h"
#include "LiteralNode.h"
#include "ArrayNode.h"
#include "FunctionNode.h"

namespace Protra {
namespace Lib {
 namespace Lang {

class PrimaryNode : public ExpressionNode
{
public:
    std::shared_ptr<ExpressionNode> Parse(std::shared_ptr<ExpressionNode>& that, Scanner& scanner)override
    {
        Token = scanner._Token;

        if (Token.Type == TokenType::LocalVariable ||
            Token.Type == TokenType::GlobalVariable) {
            std::shared_ptr<ExpressionNode> tmp;
            tmp = std::shared_ptr<ExpressionNode>(new VariableNode());
            tmp=tmp->Parse(tmp,scanner);
            return tmp;
        }
        if (Token.Type == TokenType::Int ||
            Token.Type == TokenType::Float ||
            Token.Type == TokenType::String ||
            Token.Value == "null") {
            std::shared_ptr<ExpressionNode> tmp;
            tmp = std::shared_ptr<ExpressionNode>(new LiteralNode());
            tmp = tmp->Parse(tmp, scanner);
            return tmp;
        }
        if (Token.Type == TokenType::FunctionName) {
            std::shared_ptr<ExpressionNode> tmp;
            tmp = std::shared_ptr<ExpressionNode>(new FunctionNode());
            tmp = tmp->Parse(tmp, scanner);
			return tmp;
		}
        if (Token.Value == "[") {
            std::shared_ptr<ExpressionNode> tmp;
            tmp = std::shared_ptr<ExpressionNode>(new ArrayNode());
            tmp = tmp->Parse(tmp, scanner);
			return tmp;
		}
        if (Token.Value == "(")
        {
            scanner.Scan();
            std::shared_ptr<ExpressionNode> node;
            node = std::shared_ptr<ExpressionNode>(new ExpressionNode());
            node=node->Parse(node,scanner);
            if (scanner._Token.Value != ")") {
                throw std::runtime_error(ParseException("')' expected", Token));
            }
            scanner.Scan();
            return node;
        }
        throw std::runtime_error(ParseException("syntax error", Token));
#if 0
        scanner._Token.Value = ";";
#endif
        return that;
    }
    std::shared_ptr<Value> Evaluate(std::shared_ptr<ExpressionNode>& that, Resource& resource, int at, std::string& ats)override
    {
        return std::shared_ptr<Value>(new Value(false));
    }
};

}
}
}

#endif


