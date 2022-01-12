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

#ifndef DF_RETURNSTATEMENTNODE_H_
#define DF_RETURNSTATEMENTNODE_H_

#include "ExpressionNode.h"

namespace Protra {
namespace Lib {
namespace Lang {

class ReturnStatementNode : public ExecutableNode
{
public:
    std::shared_ptr<ExpressionNode> _expNode;

    std::shared_ptr<ExecutableNode> Parse(std::shared_ptr<ExecutableNode>& that,Scanner& scanner)override
    {
        Token = scanner._Token;
        if (!scanner.Scan()) {
            throw std::runtime_error(ParseException("';' expected", scanner._Token));
        }
        if (scanner._Token.Value == ";") {
            return that;
        }
        _expNode = std::shared_ptr<ExpressionNode>(new ExpressionNode());
        _expNode= _expNode->Parse(_expNode,scanner);
        if (scanner._Token.Value != ";") {
            throw std::runtime_error(ParseException("';' expected", scanner._Token));
        }
        return that;
    }

    Result Execute(std::shared_ptr<ExecutableNode>& that, Resource& resource, int at, std::string& ats)override
    {
        resource.ReturnValue = _expNode == nullptr ? nullptr : _expNode->Evaluate(_expNode,resource, at, ats);
        resource.Token = Token;
        return Result::Return;
    }


};

}
}
}

#endif


