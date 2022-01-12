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

#ifndef DF_EXPRESSIONNODE_H_
#define DF_EXPRESSIONNODE_H_

#include "Scanner.h"
#include "Resource.h"

namespace Protra {
namespace Lib {
namespace Lang {

class ExpressionNode {
public:
    Token Token;
    bool isVariableNode;
    bool isSuffixedExpressionNode;
    ExpressionNode()
    {
        isVariableNode = false;
        isSuffixedExpressionNode=false;
    }
    virtual ~ExpressionNode()
    {

    }
    virtual std::shared_ptr<ExpressionNode> Parse(std::shared_ptr<ExpressionNode>& that, Scanner& scanner);
    virtual std::shared_ptr<Value> Evaluate(std::shared_ptr<ExpressionNode>& that, Resource& resource, int at,std::string& ats)
    {
        throw std::runtime_error("NotImplementedException");
    }
    virtual std::shared_ptr<Value> Assign(std::shared_ptr<ExpressionNode>& that, Resource& resource,
        int at, std::string& ats,std::shared_ptr<Value>& val)
    {
        std::shared_ptr<Value> ret;
        return ret;
    }
};

}
}
}

#ifdef PROTRA_LANG_IMPL

#include "AssignmentNode.h"

namespace Protra {
namespace Lib {
namespace Lang {

std::shared_ptr<ExpressionNode> ExpressionNode::Parse(std::shared_ptr<ExpressionNode>& that, Scanner& scanner)
{
    std::shared_ptr<ExpressionNode> ret;

    std::shared_ptr<ExpressionNode> tmp = std::shared_ptr<ExpressionNode>(new AssignmentNode());
    tmp=tmp->Parse(tmp,scanner);
    return tmp;

#if 0    //yomei 未実装の時は行の最後まで実行したことにする。
    scanner._Token.Value = ";";
    return ret;
#endif
}

}
}
}

#endif

#endif


