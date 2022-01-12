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

#ifndef DF_PREFIXEXPRESSIONNODE_H_
#define DF_PREFIXEXPRESSIONNODE_H_

#include "ExpressionNode.h"
#include "SuffixedExpressionNode.h"

namespace Protra {
namespace Lib {
namespace Lang {

class PrefixedExpressionNode : public ExpressionNode
{
public:
    char _op;
    std::shared_ptr<ExpressionNode> _atNode;
    ValueType::ValueType _type;
    std::shared_ptr <ExpressionNode> _expNode;


    std::shared_ptr<ExpressionNode> Parse(std::shared_ptr<ExpressionNode>& that, Scanner& scanner)override
    {
        Token = scanner._Token;
        if (Token.Type != TokenType::Operator) {
            std::shared_ptr<ExpressionNode> tmp = std::shared_ptr<ExpressionNode>(new SuffixedExpressionNode());
            tmp=tmp->Parse(tmp,scanner);
            return tmp;
        }
        std::string token = Token.Value;
        if (token == "{") {
            _op = token[0];
            scanner.Scan();
            _atNode = std::shared_ptr<ExpressionNode>(new ExpressionNode());
            _atNode = _atNode->Parse(_atNode,scanner);
            if (scanner._Token.Value != "}") {
                throw std::runtime_error(ParseException("'}' expected", Token));
            }
            scanner.Scan();
        }
        else if (token == "+" || token == "-" || token == "!") {
            _op = token[0];
            scanner.Scan();
        }
        else if (token == "(") {
            class Token peek = scanner.Peek(); // 先読み
            if (peek.Type != TokenType::Type) {
                std::shared_ptr<ExpressionNode> tmp = std::shared_ptr<ExpressionNode>(new SuffixedExpressionNode());
                tmp = tmp->Parse(tmp, scanner);
                return tmp;
            }
            _op = token[0];
            scanner.Scan();

            if (scanner._Token.Value == "int") {
                _type = ValueType::Int;
            }
            else if (scanner._Token.Value == "float") {
                _type = ValueType::Float;
            }
            else if (scanner._Token.Value == "string") {
                _type = ValueType::String;
            }
            else{
                _type = ValueType::Null;
            }
            if (_type == ValueType::Null) {
                throw std::runtime_error(ParseException("bad cast", scanner._Token));
            }

            scanner.Scan();
            if (scanner._Token.Value != ")") {
                throw std::runtime_error(ParseException("')' expected", scanner._Token));
            }
            scanner.Scan();
        }
        else{
            std::shared_ptr<ExpressionNode> tmp = std::shared_ptr<ExpressionNode>(new SuffixedExpressionNode());
            tmp=tmp->Parse(tmp,scanner);
            return tmp;
        }
        _expNode = std::shared_ptr<ExpressionNode>(new PrefixedExpressionNode());
        _expNode=_expNode->Parse(_expNode,scanner);
#if 0
        scanner._Token.Value = ";";
#endif
        return that;
    }
    std::shared_ptr<Value> Evaluate(std::shared_ptr<ExpressionNode>& that, Resource& resource, int at, std::string& ats)override
    {
        //try
        //{

            std::shared_ptr<Value>tmp;
            std::shared_ptr<Value>val;
            std::string str;
            switch (_op)
            {
            case '{': // @作用素
                val = _atNode->Evaluate(_atNode,resource, at, ats);
                switch (val->ValueType)
                {
                case ValueType::Int:
                    return _expNode->Evaluate(_expNode,resource, at + val->InnerValue().toInt(), ats);
                case ValueType::String:
                    str = val->InnerValue().toString();
                    return _expNode->Evaluate(_expNode,resource, at, str);
                default:
                    throw std::runtime_error(ParseException("non-(int or string) value for at operator", Token));
                }
            case '+':
                //return +_expNode->Evaluate(_expNode, resource, at, ats);
                tmp = _expNode->Evaluate(_expNode, resource, at, ats);
                tmp = std::shared_ptr<Value>(new Value(+*tmp.get()));
                return tmp;
            case '-':
                //return -_expNode.Evaluate(resource, at, ats);
                tmp = _expNode->Evaluate(_expNode, resource, at, ats);
                tmp = std::shared_ptr<Value>(new Value(-*tmp.get()));
                return tmp;
            case '!':
                //return !_expNode.Evaluate(resource, at, ats);
                tmp = _expNode->Evaluate(_expNode, resource, at, ats);
                tmp = std::shared_ptr<Value>(new Value(!*tmp.get()));
                return tmp;
            case '(': // キャスト
                std::shared_ptr<Value>val = _expNode->Evaluate(_expNode,resource, at, ats);
                if (val->IsNull())
                    throw std::runtime_error(ParseException("null casted", Token));
                return std::shared_ptr<Value>(new Value(val->Cast(_type)));
            }
        //}
        //catch (RuntimeException e)
        //{
        //    throw new RuntimeException(e.Message, e.Token ? ? Token, e);
        //}
        return _expNode->Evaluate(_expNode,resource, at, ats);
#if 0
        return std::shared_ptr<Value>(new Value(false));
#endif
    }
};

}
}
}

#endif



