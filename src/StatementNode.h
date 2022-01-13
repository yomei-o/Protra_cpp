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

#ifndef DF_STATEMENTNODE_H_
#define DF_STATEMENTNODE_H_

#include "ExecutableNode.h"

namespace Protra {
namespace Lib {
namespace Lang {


class StatementNode : public ExecutableNode
{
public:
    std::shared_ptr<ExecutableNode> Parse(std::shared_ptr<ExecutableNode>&that, Scanner& scanner)override;
    Result Execute(std::shared_ptr<ExecutableNode>& that, Resource& resource, int at, std::string& ats)override
    {
        throw std::runtime_error("NotImplementedException");
        return Result::Break;
    }
};

}
}
}



#include "EmptyStatementNode.h"
#include "ContinueStatementNode.h"
#include "BreakStatementNode.h"
#include "ReturnStatementNode.h"
#include "ExpressionStatementNode.h"
#include "IfStatementNode.h"
#include "WhileStatementNode.h"

namespace Protra {
namespace Lib {
namespace Lang {
            
inline std::shared_ptr<ExecutableNode> StatementNode::Parse(std::shared_ptr<ExecutableNode>& that, Scanner& scanner)
{
    std::shared_ptr<ExecutableNode> ret;
    Token = scanner._Token;
    if (Token.Value == "if"){
        ret = std::shared_ptr<ExecutableNode>(new IfStatementNode());
        ret = ret->Parse(ret, scanner);
        return ret;
    }
    else if (Token.Value == "while") {
        ret = std::shared_ptr<ExecutableNode>(new WhileStatementNode());
        ret = ret->Parse(ret, scanner);
        return ret;
    }
    else if (Token.Value == "return") {
        ret = std::shared_ptr<ExecutableNode>(new ReturnStatementNode());
        ret = ret->Parse(ret, scanner);
        return ret;
    }
    else if (Token.Value == "break") {
        ret = std::shared_ptr<ExecutableNode>(new BreakStatementNode());
        ret = ret->Parse(ret, scanner);
        return ret;
    }
    else if (Token.Value == "continue") {
        ret = std::shared_ptr<ExecutableNode>(new ContinueStatementNode());
        ret = ret->Parse(ret, scanner);
        return ret;
    }
    else if (Token.Value == ";") {
        ret = std::shared_ptr<ExecutableNode>(new EmptyStatementNode());
        ret = ret->Parse(ret, scanner);
        return ret;
    }
    else {
        ret = std::shared_ptr<ExecutableNode>(new ExpressionStatementNode());
        ret = ret->Parse(ret, scanner);
        return ret;
    }
    return ret;
}

}
}
}

#endif

