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

#ifndef DF_WHILESTATEMENTNODE_H_
#define DF_WHILESTATEMENTNODE_H_

#include "ExecutableNode.h"
#include "ExpressionNode.h"

namespace Protra {
namespace Lib {
namespace Lang {

class WhileStatementNode : public ExecutableNode
{
public:
    std::shared_ptr<ExpressionNode> _condNode;
    std::vector< std::shared_ptr<ExecutableNode> > _nodeList;

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
            if (scanner._Token.Value == "end")
            {
                scanner.Scan();
                if (scanner._Token.Value != ";") {
                    throw std::runtime_error(ParseException("';' expected", Token));
                }
                return that;
            }
            std::shared_ptr<ExecutableNode> tmp = std::shared_ptr<ExecutableNode>(new StatementNode());
            tmp=tmp->Parse(tmp,scanner);
            _nodeList.push_back(tmp);
        }
        throw std::runtime_error(ParseException("unexpected EOF", Token));
    }

    Result Execute(std::shared_ptr<ExecutableNode>& that,Resource& resource, int at, std::string& ats)override
    {
        std::shared_ptr<Value> val = _condNode->Evaluate(_condNode,resource, at, ats);
        while (val != nullptr && val->IsTrue())
        {
            int sz = (int)_nodeList.size();

            for(int i=0;i<sz;i++){
                std::shared_ptr<ExecutableNode> node;
                node = _nodeList[i];
                switch (node->Execute(node,resource, at, ats))
                {
                case Result::Return:
                    return Result::Return;
                case Result:: Break:
                    return Result:: Normal;
                case Result::Confinue:
                    goto Continue;
                }
            }
        Continue:
            val = _condNode->Evaluate(_condNode,resource, at, ats);
        }
        return Result::Normal;
    }


};

}
}
}


#endif



