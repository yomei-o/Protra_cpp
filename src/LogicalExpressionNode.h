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

#ifndef DF_LOGICALEXPRESSION_H_
#define DF_LOGICALEXPRESSION_H_

#include "ExpressionNode.h"
#include "LogicalExpressionNode.h"
#include "LogicalTermNode.h"

namespace Protra {
namespace Lib {
namespace Lang {

class LogicalExpressionNode : public ExpressionNode
{
public:
    std::vector<std::shared_ptr<ExpressionNode> > _nodeList;

    std::shared_ptr<ExpressionNode> Parse(std::shared_ptr<ExpressionNode>& that,Scanner& scanner)override
    {
        Token = scanner._Token;
        std::shared_ptr<ExpressionNode>node = std::shared_ptr<ExpressionNode>(new LogicalTermNode());
        node=node->Parse(node,scanner);
        std::string token = scanner._Token.Value;
        if (token != "||") {
            return node;
        }
        _nodeList.clear();
        _nodeList.push_back(node);

        do
        {
            scanner.Scan();
            std::shared_ptr<ExpressionNode> tmp = std::shared_ptr<ExpressionNode>(new LogicalTermNode());
            tmp = tmp->Parse(tmp, scanner);
            _nodeList.push_back(tmp);
            token = scanner._Token.Value;
        } while (token == "||");
#if 0
        scanner._Token.Value = ";";
#endif
        return that;
    }
    std::shared_ptr<Value> Evaluate(std::shared_ptr<ExpressionNode>& that, Resource& resource, int at, std::string& ats)override
    {
        //try
        //{
            int sz = (int)_nodeList.size();
            for (int i = 0; i < sz;i++){
                std::shared_ptr<ExpressionNode> node;
                node = _nodeList[i];
                std::shared_ptr<Value> val = node->Evaluate(node,resource, at, ats);
                if (val != nullptr && val->IsTrue())
                    return std:: shared_ptr<Value>(new Value(true));
            }
            return std::shared_ptr<Value>(new Value(false));
        //}
        //catch (...)
        //{
        //    throw std::runtime_error(ParseException("todo parse error",Token));
        //}
    }

};

}
}
}


#endif


