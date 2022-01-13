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

#if defined(_WIN32) && !defined(__GNUC__)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif /* _WIN32 */

#ifdef _MSC_VER
#if _MSC_VER >= 1400
#pragma warning( disable : 4996 )
#pragma warning( disable : 4819 )
#endif
#endif

#include <iostream>

#define ENABLE_TYPEOF 

#include "Protra.h"

#include "TypeOfBuiltins.h"

//#include "srell.hpp"

int main(int argc,char* argv[])
{
#if defined(_WIN32) && !defined(__GNUC__)
	//	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_WNDW);
	//	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_WNDW);
	//	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_WNDW);
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	if (argc < 2) {
		printf("ProtraLang [filename.pt]  \n");
		return 1;
	}
	std::string file = argv[1];
    Protra::Lib::Lang::Interpreter ip(file);
	if (ip.initialized==0) {
		return 2;
	}

#ifdef ENABLE_TYPEOF 
	//ビルトイン関数のサンプル
	std::shared_ptr<Protra::Lib::Lang::Builtins::Builtins> btin=ip.Builtins();
	Protra::Lib::Lang::Builtins::TypeOfBuiltins::Init(btin);
#endif

	ip.Execute();
	if (ip.executed == 0) {
		return 3;
	}
	return 0;
}

