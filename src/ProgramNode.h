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

#ifndef DH_PROGRAMNODE_H_
#define DH_PROGRAMNODE_H_

#include "StatementNode.h"
#include "FunctionDefinitionNode.h"
#include "ExecutableNode.h"

namespace Protra{
namespace Lib {
namespace Lang {

	class ProgramNode :public ExecutableNode
	{
	public:
		std::vector<std::shared_ptr<ExecutableNode> > _nodeList;

		virtual std::shared_ptr<ExecutableNode>  Parse(std::shared_ptr<ExecutableNode>& that,Scanner& scanner) override
		{
			while (scanner.Scan())
			{
				std::shared_ptr<ExecutableNode> tmp;

				if (scanner._Token.Value == "def") {
					std::shared_ptr<ExecutableNode> p(new FunctionDefinitionNode());
					tmp=p->Parse(p,scanner);
				}
				else {
					std::shared_ptr<ExecutableNode> p(new StatementNode());
					tmp=p->Parse(p,scanner);
				}
                //yomei add
                if (tmp == nullptr)continue;

				_nodeList.push_back(tmp);
			}
			return that;
		}
		virtual Result Execute(std::shared_ptr<ExecutableNode>& that,Resource& resource, int at, std::string& ats)
		{
			std::shared_ptr<std::map<std::string, std::shared_ptr<Value> > > m;
            m = std::shared_ptr<std::map<std::string, std::shared_ptr<Value> > >(new std::map<std::string, std::shared_ptr<Value> >());
			resource.Stack.push_back(m);
			int i, sz = (int)_nodeList.size();
			for (i = 0; i < sz; i++) {
			    std::shared_ptr<ExecutableNode> node;
				node = _nodeList[i];
                //yomei 未実装のノードがあるため
                if (node == nullptr)continue;

				switch (node->Execute(node,resource, at, ats))
				{
				case Result::Normal:
					break;
				case Result::Return:
					goto Finish;
				case Result::Break:
					//throw new RuntimeException("unexpected break", resource.Token);
					throw std::runtime_error(ParseException("unexpected break.",resource.Token));
				case Result::Confinue:
					//throw new RuntimeException("unexpected continue", resource.Token);
					throw std::runtime_error(ParseException("unexpected continue.",resource.Token));
				}
			}
		Finish:
			resource.Stack.pop_back();
			return Result::Normal;
		}
	};
}
}
}

#endif


