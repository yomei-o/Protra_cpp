#include <iostream>
#include "IndustorialValue.h"
#include "BrandData.h"
#include "IndustorialPriceData.h"

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

	IndustorialPriceData ipd;
	std::shared_ptr<PriceList> ipl;
	std::shared_ptr<Price> p;
	std::shared_ptr<Price> lp;

#if 1
	ipl = ipd.GetPricesIndustory33(25);
	for (int i = 0; ipl!=nullptr && i < ipl->Count(); i++) {
		p=ipl->Price(i);
		printf("%04d/%02d/%02d  %d\n",
			p->Date.Year, p->Date.Month, p->Date.Day,
			p->Close);
	}
#endif


#if 1
	int sz;
	for (int i = 1; i <= 33;i++) {
		ipl = ipd.GetPricesIndustory33(i);
		if (ipl == nullptr)continue;
		sz = ipl->Count();
		p = ipl->Price(0);
		printf("%d  %04d/%02d/%02d  %d\n",i,
			p->Date.Year, p->Date.Month, p->Date.Day,
			p->Close);
		for (int j = 1; j < sz - 1; j++) {
			lp = p;
			p = ipl->Price(j);
			if (lp->Date.Year == p->Date.Year)continue;
			printf("%d  %04d/%02d/%02d  %d\n", i,
				p->Date.Year, p->Date.Month, p->Date.Day,
				p->Close);
		}

		p = ipl->Price(sz-1);
		printf("%d  %04d/%02d/%02d  %d\n", i,
			p->Date.Year, p->Date.Month, p->Date.Day,
			p->Close);
		printf("\n");
	}
#endif

	return 0;
}



