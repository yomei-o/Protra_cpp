#ifndef DF_FORMATNUMBER_H_
#define DF_FORMATNUMBER_H_

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>

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
	if (num < 0) {
		ret = "-";
		num = -num;
	}
	ret += "\\";
	ret += formatNumber(num);
	return ret;
}

#endif

