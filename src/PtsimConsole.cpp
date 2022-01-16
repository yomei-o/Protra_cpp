#include "SystemExcutor.h"
#include "BrandListConfig.h"

int main(int argc,char* argv[])
{
	if (argc < 3) {
		printf("PtSimConsoke file.pt Code1 [Code2 ...] \n");
		return 0;
	}
	std::shared_ptr<Protra::Lib::Config::BrandList> bl;
	bl = std::shared_ptr<Protra::Lib::Config::BrandList>(new (Protra::Lib::Config::BrandList));
	bl->Name = "test";
	bl->List = std::shared_ptr <std::vector<std::string>>(new std::vector<std::string>);
	//bl->List->push_back("1378");
	for (int i = 2; i < argc; i++) {
		bl->List->push_back(argv[i]);
	}
	std::shared_ptr<SystemExcutor> mf;
	mf = std::shared_ptr<SystemExcutor>(new SystemExcutor(argv[1],bl));
	mf->LoopBrandAndDate();

	return 0;
}

