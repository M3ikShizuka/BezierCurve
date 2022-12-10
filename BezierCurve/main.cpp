#ifdef MEMORY_LEAKS_TEST
	#define _CRTDBG_MAP_ALLOC
	#include <stdlib.h>
	#include <crtdbg.h>
#endif
#include "main.hpp"
#include "CDraw.hpp"
#include "CCurve.hpp"
#include "CRender.hpp"

int main(int argc, char *argv[])
{
#ifdef MEMORY_LEAKS_TEST
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	// Initializing render.
	IRender* pRender = new CRender(
		new CDraw(),
		new CCurve()
	);
	pRender->InitRender(argc, argv);

	// Release.
	if (pRender)
	{
		delete pRender;
		pRender = nullptr;
	}

	return 0;
}