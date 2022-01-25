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

#include "PyPtsim.h"
#include "CppExcutor.h"

PyPtsim_::PyPtsim_()
{
	initialized=0;
	executed=0;
	option = std::shared_ptr<std::map<std::string, std::string> >(new (std::map<std::string, std::string>));
}

PyPtsim_::~PyPtsim_()
{
	option = nullptr;
	cppex = nullptr;
	name = "";
}

int PyPtsim_::Initialize()
{
	initialized = 0;
	executed = 0;
	cppex = nullptr;
	try {
		cppex = std::shared_ptr<PtSim::CppExcutor>(new PtSim::CppExcutor(name));
		if (cppex->initialized == 0)return 1;
		initialized = 1;
	}
	catch (...)
	{
	}
	return initialized==0;
}

void PyPtsim_::setName(std::string name_)
{
	name = name_;
}

void PyPtsim_::setOption(std::string name_, std::string param_)
{
	option->insert({ name_, param_ });
}

void PyPtsim_::AddLog(int year, int month, int day, std::string code, std::string name_, int pri, int qua, int order)
{
	if (cppex == nullptr)return;
	if (cppex->initialized == 0)return;
	try {
		cppex->AddLog(year, month, day, code, name_, pri, qua, order);
	}
	catch (...) {
	}
}

int PyPtsim_::Performance()
{
	executed = 0;
	try {
		if (cppex == nullptr)return 1;
		if (cppex->initialized == 0)return 1;
		cppex->Performance(option);
		if (cppex->excuted == 0)return 1;
		executed = 1;
	}
	catch (...) {

	}
	return executed==0;
}

