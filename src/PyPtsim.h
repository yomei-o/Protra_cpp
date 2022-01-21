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

#ifndef DF_PYPTSIM_H_
#define DF_PYPTSIM_H_

#include <string>
#include <vector>
#include <map>
#include <memory>

namespace PtSim{
	class CppExcutor;
}

class PyPtsim_
{
public:
	PyPtsim_();
	virtual ~PyPtsim_();
	void setName(std::string name);
	void setOption(std::string name,std::string param);
	int Initialize();
	void AddLog(int year, int month, int day, std::string code, std::string name, int pri, int qua, int order);
	int Performance();
private:
	std::string name;
	std::shared_ptr<PtSim::CppExcutor>	cppex;
	std::shared_ptr<std::map<std::string, std::string> > option;
	int initialized;
	int executed;
};

#endif

