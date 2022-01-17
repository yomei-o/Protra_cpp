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

#ifndef DF_INTERPRETER_H_
#define DF_INTERPRETER_H_

#include <stdio.h>
#include "ProgramNode.h"
#include "Resource.h"

#include "RegisterBuiltins.h"

namespace Protra{
namespace Lib{
namespace Lang {

class Interpreter
{
public:
	std::shared_ptr<ExecutableNode> _program;
	std::shared_ptr<Resource> _resource;
    int initialized;
    int executed;
	Interpreter(std::string file)
	{
        initialized = 0;
        executed = 0;
		try
		{
			Scanner scanner(file);
			_program= std::shared_ptr<ProgramNode>(new ProgramNode());
			_program->Parse(_program,scanner);
			_resource = std::shared_ptr<Resource>(new Resource(scanner.MagicComment));

			//yomei
			_resource->Builtins = std::shared_ptr<Builtins::Builtins>(new Builtins::RegisterBuiltins());
			
            initialized = 1;
        }
		catch (const std::runtime_error& e)
		{
			printf("runtime error msg=%s\n", e.what());
		}
		catch (...)
		{
			printf("Exception!!\n");
		}
    }
	void Execute()
	{
        std::string ats = "";
        Execute(0, ats);
	}
    void Execute(int at,std::string& ats)
    {
		executed = 0;
		if (initialized == 0) {
            printf("Interpreter is not initialized\n");
            return;
        }
        _resource->Stack.clear();
        _resource->FunctionTable.clear();
        try
        {
            std::string param = "";
            _program->Execute(_program, *(_resource.get()), at, ats);
            executed = 1;
        }
        catch (const std::runtime_error& e)
        {
            printf("runtime error msg=%s\n", e.what());
        }
        catch (...)
        {
            printf("runtime error  \n");
        }
    }

	std::map<std::string, std::shared_ptr<Value> >& GlobalVariableTable()
	{
		return _resource->GlobalVariableTable;
	}
	std::shared_ptr<Builtins::Builtins>& Builtins()
	{
		return _resource->Builtins;
	}

};


}
}
}


#endif


