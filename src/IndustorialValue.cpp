#include <iostream>
#include "IndustorialValue.h"
#include "BrandData.h"

// debug 
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

using namespace Protra::Lib::Data;


int main()
{
#if defined(_WIN32) && !defined(__GNUC__)
	//	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_WNDW);
	//	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_WNDW);
	//	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_WNDW);
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	IndustorialValueData ivd;
	std::vector<std::shared_ptr<IndustorialValue> >ivs;
	ivd.Load();
	ivs = ivd.IndustorialValue33(25);
	if (ivs.size() == 0) {
		printf("Error: Data file cannot open.\n");
		return 1;
	}
	ivd.SetValue(ivs, "9201", 2405);
	ivd.SetValue(ivs, "9202", 2668.5);
	ivd.SetValue(ivs, "9232", 1309);
	for (int i = 0; i < ivs.size(); i++) {
		ivs[i]->Print();
	}
	double d;
	d = ivd.GetCapital(ivs);
	printf("Capital=%g\n",d);
	d = ivd.GetRefCapital(ivs);
	printf("RefCapital=%g\n", d);
	d = ivd.GetIndex(ivs);
	printf("Index=%g\n", d);
	return 0;
}



