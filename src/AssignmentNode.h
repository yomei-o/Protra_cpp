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

#ifndef DF_ASSIGNMENTNODE_H_
#define DF_ASSIGNMENTNODE_H_

#include "ExpressionNode.h"
#include "LogicalExpressionNode.h"

namespace Protra {
namespace Lib {
namespace Lang {

class AssignmentNode : public ExpressionNode
{
public:
    std::shared_ptr<ExpressionNode> _lvalueNode;
    std::shared_ptr<ExpressionNode> _rvalueNode;
    
    std::shared_ptr<ExpressionNode> Parse(std::shared_ptr<ExpressionNode>& that,Scanner& scanner)override
    {
        Token = scanner._Token;
        std::shared_ptr<ExpressionNode> node = std::shared_ptr<ExpressionNode>(new LogicalExpressionNode());
        node= node->Parse(node,scanner);
        if (scanner._Token.Value != "=")
            return node;
        if (!(node->isVariableNode || node->isSuffixedExpressionNode)) {
            throw std::runtime_error(ParseException("invalid assignment.", Token));
        }
        _lvalueNode = node;
        scanner.Scan();
        _rvalueNode = std::shared_ptr<ExpressionNode>(new ExpressionNode());
        _rvalueNode= _rvalueNode->Parse(_rvalueNode,scanner);

        return that;
    }

    std::shared_ptr<Value> Evaluate(std::shared_ptr<ExpressionNode>& that,Resource& resource, int at, std::string& ats)override
    {
        std::shared_ptr<Value> val = _rvalueNode->Evaluate(_rvalueNode,resource, at, ats);
        if (_lvalueNode->isVariableNode) {
            return _lvalueNode->Assign(_lvalueNode,resource,at, ats,val);
        }
        if (_lvalueNode->isSuffixedExpressionNode) {
            return _lvalueNode->Assign(_lvalueNode,resource, at, ats, val);
        }
        throw std::runtime_error(ParseException("invalid assignment.", Token));
    }

};

}
}
}




#endif


