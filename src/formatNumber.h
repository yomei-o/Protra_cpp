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

#ifndef DF_FORMATNUMBER_H_
#define DF_FORMATNUMBER_H_

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>
#include <math.h>

inline std::string formatNumber(int num)
{
	std::vector<int>    sepnum;
	int                 number = abs(num);
	int                 sgn = num >= 0 ? 1 : -1;

	while (number / 1000) {
		sepnum.push_back(number % 1000);
		number /= 1000;
	}

	std::stringstream  ss;
	ss << number * sgn;
	for (std::vector<int>::reverse_iterator i = sepnum.rbegin();
		i < sepnum.rend(); i++) {
		ss << "," << std::setfill('0') << std::setw(3) << *i;
	}
	return std::string(ss.str());
}

inline std::string yenFormatNumber(int num)
{
	std::string ret;
	if (num == INT_MAX || num == INT_MIN)return "NaN";
	if (num < 0) {
		ret = "-";
		num = -num;
	}
	ret += "\\";
	ret += formatNumber(num);
	return ret;
}

inline std::string perNanNumber(float num)
{
	char buf[64];
	if (std::isnan(num))return "NaN";
	sprintf(buf,"%.2f%%", num);
	return buf;
}

inline std::string nanNumber(float num)
{
	char buf[64];
	if (std::isnan(num))return "NaN";
	if (std::signbit(num) && std::isinf(num))return "-‡";
	if (std::isinf(num))return "‡";
	sprintf(buf, "%.2f", num);
	return buf;
}

#endif

