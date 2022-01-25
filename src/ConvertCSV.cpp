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

#include <stdio.h>
#include "PriceDataConv.h"

int main(int argc, char* argv[])
{
	std::string from;
	std::string to; 
	int t=0;
	int to_csv = 0;
	if (argc < 3){
		printf("CovertCSV code file.csv  \n");
		printf("CovertCSV file.csv code  \n");
		return 1;
	}
	sscanf(argv[1], "%d", &t);
	if (strlen(argv[1]) == 4 && t >= 1000 && t <= 9999)to_csv = 1;

	from = argv[1];
	to = argv[2];
	if (to_csv) {
		Protra::Lib::Data::PriceDataConv::ConvertToCSV(from, to);
	}
	else {
		Protra::Lib::Data::PriceDataConv::ConvertFromCSV(from, to);
	}
	return 0;
}
