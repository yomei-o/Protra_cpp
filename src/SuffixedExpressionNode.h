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

#ifndef DF_SUFFIXEXPNODE_H_
#define DF_SUFFIXEXPNODE_H_

#include "ExpressionNode.h"
#include "PrimaryNode.h"

namespace Protra {
namespace Lib {
 namespace Lang {

class SuffixedExpressionNode : public ExpressionNode
{
public:

    std::shared_ptr<ExpressionNode> _arrayNode;
    std::vector< std::shared_ptr<ExpressionNode> > _nodeList;

    SuffixedExpressionNode() {
        isSuffixedExpressionNode = true;
    }

    std::shared_ptr<ExpressionNode> Parse(std::shared_ptr<ExpressionNode>& that, Scanner& scanner)override
    {
        Token = scanner._Token;
        std::shared_ptr<ExpressionNode> node = std::shared_ptr<ExpressionNode>(new PrimaryNode());
        node=node->Parse(node,scanner);
        class Token t = scanner._Token;

        if (t.Value != "[")
            return node;
        _arrayNode = node;
        _nodeList.clear();
        do
        {
            scanner.Scan();
            std::shared_ptr<ExpressionNode>tmp = std::shared_ptr<ExpressionNode>(new ExpressionNode());
            tmp = tmp->Parse(tmp, scanner);
            _nodeList.push_back(tmp);
            t = scanner._Token;
            if (t.Value != "]") {
                throw std::runtime_error(ParseException("']' expected.", Token));
            }
            scanner.Scan();
            t = scanner._Token;
        } while (t.Value == "[");
        return that;
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
            if (_arrayNode == nullptr) {
                //未実装の場合はとりあえずfalse
                return std::shared_ptr<Value>(new Value(false));
            }
        
            std::shared_ptr<Value>val = _arrayNode->Evaluate(_arrayNode,resource, at, ats);
            for (int i = 0; i < _nodeList.size(); i++)
            {
                std::shared_ptr<ExpressionNode> t = _nodeList[i];
                std::shared_ptr<Value>index = t->Evaluate(t,resource, at, ats);
                val = (*val.get())[index->toInt()];
            }
            return val;
        //}
        //catch (RuntimeException e)
        //{
        //    throw new RuntimeException(e.Message, e.Token ? ? Token, e);
        //}
        //catch (NullReferenceException e)
        //{
        //    throw new RuntimeException(e.Message, Token);
        //}
#if 0
        return std::shared_ptr<Value>(new Value(false));
#endif
    }
    std::shared_ptr<Value> Assign(std::shared_ptr<ExpressionNode>& that, Resource& resource,
        int at, std::string& ats, std::shared_ptr<Value>& val)override
    {
        //try
        //{
        std::shared_ptr<Value>arr = _arrayNode->Evaluate(_arrayNode, resource, at, ats);
        std::shared_ptr<Value>index = _nodeList[0]->Evaluate(_nodeList[0], resource, at, ats);
        for (int i = 1; i < _nodeList.size(); i++)
        {
            arr = (*arr.get())[index->toInt()];
            index = _nodeList[i]->Evaluate(_nodeList[i], resource, at, ats);
        }
        std::shared_ptr<Value>tmp;
        tmp = (*arr.get())[index->toInt()];
        *(tmp.get()) = *val.get();
        return tmp;
        //}
        //catch (RuntimeException e)
        //{
        //    if (e.Token == null)
        //        e.Token = Token;
        //    throw;
        //}
        //catch (NullReferenceException e)
        //{
        //    throw new RuntimeException(e.Message, Token);
        //}
    }

};

}
}
}


#endif




