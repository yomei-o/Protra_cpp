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
