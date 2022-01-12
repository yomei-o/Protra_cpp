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

#ifndef DF_ARITHMETERMNODE_H_
#define DF_ARITHMETERMNODE_H_

#include "ExpressionNode.h"
#include "PrefixedExpressionNode.h"

namespace Protra {
namespace Lib {
namespace Lang {

class ArithmeticTermNode : public ExpressionNode
{
public:
    std::vector<std::shared_ptr<ExpressionNode> > _nodeList;
    std::vector<char> _opCharList;

    std::shared_ptr<ExpressionNode> Parse(std::shared_ptr<ExpressionNode>& that, Scanner& scanner)override
    {
        Token = scanner._Token;
        std::shared_ptr<ExpressionNode> node = std::shared_ptr<ExpressionNode>(new PrefixedExpressionNode());
        node=node->Parse(node,scanner);

        std::string token = scanner._Token.Value;
        if (!(token == "*" || token == "/" || token == "%"))
            return node;
        _nodeList.clear();
        _opCharList.clear();
        _nodeList.push_back(node);
        do
        {
            _opCharList.push_back(token[0]);
            scanner.Scan();
            std::shared_ptr<ExpressionNode> tmp = std::shared_ptr<ExpressionNode>(new PrefixedExpressionNode());
            tmp = tmp->Parse(tmp, scanner);
            _nodeList.push_back(tmp);
            token = scanner._Token.Value;
        } while (token == "*" || token == "/" || token == "%");
#if 0
        scanner._Token.Value = ";";
#endif
        return that;
    }
    std::shared_ptr<Value> Evaluate(std::shared_ptr<ExpressionNode>& that, Resource& resource, int at, std::string& ats)override
    {
        //try
        //{
        //yomei
        if (_nodeList.size() == 0) {
            //未実装の場合はとりあえずfalse
            return std::shared_ptr<Value>(new Value(false));
        }
        
            std::shared_ptr<ExpressionNode> tmp = _nodeList[0];
            std::shared_ptr<Value> val1=tmp->Evaluate(tmp, resource, at, ats);
            for (int i = 1; i < _nodeList.size(); i++)
            {
                std::shared_ptr<ExpressionNode> tmp2 = _nodeList[i];
                std::shared_ptr<Value>val2 = tmp2->Evaluate(tmp2,resource, at, ats);
                switch (_opCharList[i - 1])
                {
                case '*':
                    val1 = std::shared_ptr<Value>(new Value(*val1.get() * *val2.get()));
                    break;
                case '/':
                    val1 = std::shared_ptr<Value>(new Value(*val1.get() / *val2.get()));
                    break;
                default:
                    val1 = std::shared_ptr<Value>(new Value(*val1.get() % *val2.get()));
                    break;
                }
            }
            return val1;
        //}
        //catch (RuntimeException e)
        //{
        //    throw new RuntimeException(e.Message, e.Token ? ? Token, e);
        //}
#if 0
        return std::shared_ptr<Value>(new Value(false));
#endif
    }
};

}
}
}

#endif

