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

#ifndef DF_FUNCTIONDEFINITIONNODE_H_
#define DF_FUNCTIONDEFINITIONNODE_H_

#include "FunctionType.h"
#include "StatementNode.h"
#include "ExecutableNode.h"

namespace Protra{
namespace Lib{
namespace Lang{

class FunctionDefinitionNode : public ExecutableNode
{
public:
	std::string _name;
	std::vector<std::string> Arguments;

	std::vector<std::shared_ptr<ExecutableNode> > Nodes;

    std::shared_ptr<ExecutableNode> Parse(std::shared_ptr<ExecutableNode>&that,Scanner& scanner) override
	{
		Token= scanner._Token;

		// 関数名のチェック
		scanner.Scan();
		if (scanner._Token.Type != TokenType::FunctionName) {
			//throw new ParseException("function name expected", scanner.Token);
			throw std::runtime_error(ParseException("function name expected",scanner._Token));
		}
		_name = scanner._Token.Value;

		// 引数のチェック
		Arguments.clear();
		scanner.Scan();
		if (scanner._Token.Value != "(")
		{
			if (scanner._Token.Value != ";") {
				throw std::runtime_error(ParseException("';' expected",scanner._Token));
				//throw new ParseException("';' expected", scanner.Token);
			}
		}
		else
		{
			scanner.Scan();
			if (scanner._Token.Value == ")")
			{
				scanner.Scan();
				if (scanner._Token.Value != ";") {
					throw std::runtime_error(ParseException("';' expected",scanner._Token));
					//throw new ParseException("';' expected", scanner.Token);
				}
			}
			else
			{
				do
				{
					if (scanner._Token.Type != TokenType::LocalVariable) {
						//throw new ParseException("function argument expected", scanner.Token);
						throw std::runtime_error(ParseException("function argument expected",scanner._Token));
					}
					Arguments.push_back(scanner._Token.Value);
					scanner.Scan();
					if (scanner._Token.Value == ")")
					{
						scanner.Scan();
						if (scanner._Token.Value != ";") {
							//throw new ParseException("';' expected", scanner.Token);
							throw std::runtime_error(ParseException("';' expected",scanner._Token));
						}
						break;
					}
					if (scanner._Token.Value != ",") {
						//throw new ParseException("',' or ')' expected", scanner.Token);
						throw std::runtime_error(ParseException("',' or ')' expected",scanner._Token));
					}
				} while (scanner.Scan());
			}
		}

		// 本体のチェック
		Nodes.clear();
		while (scanner.Scan())
		{
			if (scanner._Token.Value == "end")
			{
				scanner.Scan();
				if (scanner._Token.Value != ";") {
					//throw new ParseException("';' expected", scanner.Token);
					throw std::runtime_error(ParseException("';' expected",scanner._Token));
				}
				return that;
			}
			std::shared_ptr<ExecutableNode> tmp(new StatementNode());
			tmp=tmp->Parse(tmp,scanner);
			Nodes.push_back(tmp);
		}

		//throw new ParseException("unexpected EOF", Token);
		throw std::runtime_error(ParseException("unexpected EOF",scanner._Token));
        return that;
	}

	/// <summary>
	/// プログラムを実行する。
	/// </summary>
	/// <exception cref="Protra.Lib.Lang.RuntimeException">
	/// プログラム実行中にエラーが発生した場合にthrowされる。
	/// </exception>
	/// <param name="resource">リソース</param>
	/// <param name="at">int型@作用素の値</param>
	/// <param name="ats">string型@作用素の値</param>
	/// <returns>実行結果</returns>
	Result Execute(std::shared_ptr<ExecutableNode>&that,Resource& resource, int at,std::string& ats)
	{
		// 関数テーブルに登録
		std::shared_ptr<FunctionType> ft= std::shared_ptr<FunctionType>(new FunctionType(_name, (int)Arguments.size()));
		if (resource.FunctionTable[_name] != nullptr) {
			//throw new RuntimeException("function is already defined --- " + ft, Token);
			throw std::runtime_error(ParseException("function is already defined --- ",Token));
		}
		resource.FunctionTypeTable[_name] = ft;
		resource.FunctionTable[_name] = that;

		return Result::Normal;
	}



};

}
}
}

#endif


