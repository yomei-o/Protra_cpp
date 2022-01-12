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

#ifndef DF_IFSTATEMENTNODE_H_
#define DF_IFSTATEMENTNODE_H_

#include "ExecutableNode.h"
#include "ExpressionNode.h"
#include "LiteralNode.h"

namespace Protra {
namespace Lib {
namespace Lang {

class IfStatementNode :public ExecutableNode
{
public:
    std::shared_ptr<ExpressionNode> _condNode;
    std::vector<std::shared_ptr<ExecutableNode> > _nodeList;
    std::shared_ptr <ExecutableNode> _nextNode;

    std::shared_ptr<ExecutableNode> Parse(std::shared_ptr<ExecutableNode>& that,Scanner& scanner)override
    {
        Token = scanner._Token;

        if (!scanner.Scan()) {
            throw std::runtime_error(ParseException("expression is expected", Token));
        }
        _condNode = std::shared_ptr<ExpressionNode>(new ExpressionNode());
        _condNode= _condNode->Parse(_condNode,scanner);
        if (scanner._Token.Value != ";") {
            throw std::runtime_error(ParseException("';' expected", Token));
        }
        while (scanner.Scan())
        {
            std::string token = scanner._Token.Value;
            if (token == "end")
            {
                scanner.Scan();
                if (scanner._Token.Value != ";") {
                    throw std::runtime_error(ParseException("';' expected", scanner._Token));
                }
                return that;
            }
            if (token == "elsif")
            {
                _nextNode = std::shared_ptr<ExecutableNode>(new IfStatementNode());
                _nextNode= _nextNode->Parse(_nextNode,scanner);
                return that;
            }
            if (token == "else")
            {
                _nextNode = ParseElse(scanner);
                return that;
            }
            std::shared_ptr< ExecutableNode> tmp = std::shared_ptr< ExecutableNode>(new StatementNode());
            tmp = tmp->Parse(tmp, scanner);
            _nodeList.push_back(tmp);
        }
        throw std::runtime_error(ParseException("unexpected EOF", Token));
    }

    std::shared_ptr<ExecutableNode> ParseElse(Scanner& scanner)
    {
        scanner.Scan();
        if (scanner._Token.Value != ";")
            throw std::runtime_error(ParseException("';' expected", scanner._Token));

        //var node = new IfStatementNode{ _condNode = new LiteralNode(new Value(true)) };

        IfStatementNode* tmp = new IfStatementNode();
        std::shared_ptr<Value> val = std::shared_ptr<Value>(new Value(true));
        std::shared_ptr<ExpressionNode> lite = std::shared_ptr<ExpressionNode>(new LiteralNode(val));
        tmp->_condNode = lite;
        std::shared_ptr<ExecutableNode> node = std::shared_ptr<ExecutableNode>(tmp);

        while (scanner.Scan())
        {
            if (scanner._Token.Value == "end")
            {
                scanner.Scan();
                if (scanner._Token.Value != ";") {
                    throw std::runtime_error(ParseException("';' expected", scanner._Token));
                }
                return node;
            }
            std::shared_ptr< ExecutableNode> tmp = std::shared_ptr< ExecutableNode>(new StatementNode());
            tmp = tmp->Parse(tmp, scanner);
            ((IfStatementNode*)(node.get()))->_nodeList.push_back(tmp);
        }
        throw std::runtime_error(ParseException("unexpected EOF", Token));
    }
    Result Execute(std::shared_ptr<ExecutableNode>& that,Resource& resource, int at,std::string& ats)override
    {
        std::shared_ptr<Value> val = _condNode->Evaluate(_condNode,resource, at, ats);
        if (val != nullptr && val->IsTrue())
        {
            int ct = (int)_nodeList.size();
            for (int i = 0; i < ct; i++)
            {
                std::shared_ptr< ExecutableNode> node;
                node = _nodeList[i];
                Result result = node->Execute(node, resource, at, ats);
                if (result != Result::Normal)
                    return result;
            }
        }
        else if (_nextNode != nullptr) {
            return _nextNode->Execute(_nextNode,resource, at, ats);
        }
        return Result::Normal;
    }

};

}
}
}
#endif


