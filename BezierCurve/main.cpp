#ifdef MEMORY_LEAKS_TEST
	#define _CRTDBG_MAP_ALLOC
	#include <stdlib.h>
	#include <crtdbg.h>
#endif
#include "main.hpp"
#include "CCurve.hpp"
#include "render.hpp"

void InitCurve();
void ReleaseCurve();

int main(int argc, char *argv[])
{
#ifdef MEMORY_LEAKS_TEST
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	// Initializing Curve curves.
	InitCurve();
	// Initializing render.
	InitRender(argc, argv);
	//Release
	ReleaseCurve();

	return 0;
}

void InitCurve()
{
	g_pCurve = new CCurve();
	const SLine* pLine = new SLine({ POINTFLOAT{ 100, 100 }, POINTFLOAT{ 150, 200 } });
	g_pCurve->AddLine(pLine);
	pLine = new SLine({ POINTFLOAT{ 150, 200 }, POINTFLOAT{ 450, 300 } });
	g_pCurve->AddLine(pLine);
	pLine = new SLine({ POINTFLOAT{ 450, 300 }, POINTFLOAT{ 460, 100 } });
	g_pCurve->AddLine(pLine);
}

void ReleaseCurve()
{
	delete g_pCurve;
	g_pCurve = nullptr;
}