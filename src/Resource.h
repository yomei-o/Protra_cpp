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

#ifndef DF_RESOURCE_H_
#define DF_RESOURCE_H_

#include <string>
#include <vector>
#include <list>
#include <map>

#include "Value.h"
#include "Token.h"

#include "FunctionType.h"
#include "Builtins.h"


namespace Protra {
namespace Lib {
namespace Lang {

class ExecutableNode;
	
	class Resource
    {
    public:
		Resource(std::map<std::string, std::string>& mc): MagicComment(mc)
        {
        }
        std::vector<std::shared_ptr<std::map<std::string,std::shared_ptr<Value> > > > Stack;
		std::map<std::string,std::shared_ptr<FunctionType> > FunctionTypeTable;
		std::map<std::string,std::shared_ptr<ExecutableNode> > FunctionTable;
		std::map<std::string, std::shared_ptr<Value> > GlobalVariableTable;
		std::shared_ptr<Builtins::Builtins> Builtins;
        std::shared_ptr<Value> ReturnValue;
        Token Token;
        std::map<std::string, std::string>& MagicComment;
    };

}
}
}

#endif


