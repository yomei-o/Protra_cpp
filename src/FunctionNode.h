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

#ifndef DF_FUNCTIONNODE_H_
#define DF_FUNCTIONNODE_H_

#include "ExpressionNode.h"
#include "FunctionType.h"
#include "FunctionDefinitionNode.h"

namespace Protra {
namespace Lib {
 namespace Lang {

class FunctionNode : public ExpressionNode
{
public:
	std::shared_ptr<FunctionType> _functionType;
	std::vector<std::shared_ptr<ExpressionNode> > _nodeList;

    std::shared_ptr<ExpressionNode> Parse(std::shared_ptr<ExpressionNode>& that, Scanner& scanner)override
    {
		Token = scanner._Token;

		// 関数名の取得
		std::string name = scanner._Token.Value;

		// 引数のチェック
		scanner.Scan();

		if (scanner._Token.Value != "(")
		{
			_functionType = std::shared_ptr<FunctionType>(new FunctionType(name, 0));
			return that;
		}
		scanner.Scan();
		if (scanner._Token.Value == ")")
		{
			_functionType = std::shared_ptr<FunctionType>(new FunctionType(name, 0));
			scanner.Scan();
			return that;
		}
		do
		{
			std::shared_ptr<ExpressionNode> tmp = std::shared_ptr<ExpressionNode>(new ExpressionNode());
			tmp = tmp->Parse(tmp, scanner);
			_nodeList.push_back(tmp);
			if (scanner._Token.Value == ")")
			{
				_functionType = std::shared_ptr<FunctionType>(new FunctionType(name, (int)_nodeList.size()));
				scanner.Scan();
				return that;
			}
			if (scanner._Token.Value != ",") {
				throw std::runtime_error(ParseException("',' or ')' expected", Token));
			}
		} while (scanner.Scan());
		throw std::runtime_error(ParseException("unexpected EOF", Token));
#if 0
        scanner._Token.Value = ";";
#endif
        return that;
    }
    std::shared_ptr<Value> Evaluate(std::shared_ptr<ExpressionNode>& that, Resource& resource, int at, std::string& ats)override
    {
		// 関数が定義されていれば実行する
		if (resource.FunctionTable[_functionType->Name()] != nullptr)
		{
			// 関数定義ノードの取得
			std::shared_ptr<ExecutableNode> fdn = resource.FunctionTable[_functionType->Name()];

			// 記号表を用意
			std::map<std::string, std::shared_ptr<Value> >* variables=new std::map<std::string, std::shared_ptr<Value> >;
            std::shared_ptr<std::map<std::string, std::shared_ptr<Value> > >tmp = std::shared_ptr<std::map<std::string, std::shared_ptr<Value> > >(variables);

			(* variables)["at"] = std::shared_ptr<Value>(new Value(at));
			for (int i = 0; i < _nodeList.size(); i++) {
				std::shared_ptr<ExpressionNode> tmp;
				tmp = _nodeList[i];
				(* variables)[((FunctionDefinitionNode*)fdn.get())->Arguments[i]] = tmp->Evaluate(tmp, resource, at, ats);
			}
			resource.Stack.push_back(tmp);
			// 文の実行
			for(int i=0;i<((FunctionDefinitionNode*)fdn.get())->Nodes.size();i++)
			{
				std::shared_ptr<ExecutableNode> node = ((FunctionDefinitionNode*)fdn.get())->Nodes[i];
				Result  ret = node->Execute(node, resource, at, ats);

				switch (ret)
				{
				case Result::Normal:
					break;
				case Result::Return:
					resource.Stack.pop_back();
					return resource.ReturnValue;
				case Result::Confinue:
					throw std::runtime_error(ParseException("unexpected continue", resource.Token));
				case Result::Break:
					throw std::runtime_error(ParseException("unexpected break", resource.Token));
				}
			}
			resource.Stack.pop_back();
			//return null;
			return std::shared_ptr<Value>(new Value(false));
		}

		// 組み込み関数を実行する。
		//try
		//{
			std::vector<std::shared_ptr<Value> > args;
			for (int i = 0; i < _nodeList.size(); i++)
			{
				std::shared_ptr<ExpressionNode> node;
				node = _nodeList[i];
				args.push_back(node->Evaluate(node,resource, at, ats));
			}
			if (resource.Builtins == nullptr) {
				return std::shared_ptr<Value>(new Value(false));
			}
			std::string tmp=_functionType->Name();
			return resource.Builtins->Invoke(tmp, args, at, ats);
		//}
		//catch (NoSuchBuiltinException e)
		//{
		//	throw new RuntimeException("undefined function --- " + _functionType, Token, e);
		//}
		//catch (InvalidCastException e)
		//{
		//	throw new RuntimeException("wrong type argument for " + _functionType, Token, e);
		//}
		//catch (NullReferenceException e)
		//{
		//	throw new RuntimeException("null argument for " + _functionType, Token, e);
		//}
		//catch (Exception e)
		//{
		//	throw new RuntimeException(e.Message, Token, e);
		//}
#if 1
        return std::shared_ptr<Value>(new Value(false));
#endif
    }
};

}
}
}

#endif


