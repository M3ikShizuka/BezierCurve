#include "render.hpp"
#include "CDraw.hpp"
#include "CCurve.hpp"

const int g_iScreenX = 600,
	g_iScreenY = 450;

void Reshape(int w, int h);
void RenderScene();
void DrawCurve(CCurve* pCurve, const int iKeyCurrent);
void DrawCurveLines(
	CCurve* pCurve,
	const std::vector<const SLine*>& vLines,
	std::vector<POINTFLOAT*>& vPoints,
	const int iKeyCurrent,
	const float(fLinesLayerColorsArray)[][4],
	const int iLinesLayer
);

void InitRender(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(g_iScreenX, g_iScreenY);
	glutCreateWindow("ShizukaSystems::CurveCurve");
	glutReshapeFunc(Reshape);
	glutDisplayFunc(RenderScene);
	glutMainLoop();
}

void Reshape(int w, int h)
{
	glViewport(0, 0, g_iScreenX, g_iScreenY);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, g_iScreenX, g_iScreenY, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void RenderScene(void)
{
#ifdef MEMORY_LEAKS_TEST
	static _CrtMemState memState1,
		memState2,
		memState3;
#endif

	static int iKeyCurrent = 0;
	static const int iKeyCount = g_pCurve->GetKeyCount();

	static ULONGLONG ullTickStart = GetTickCount64();
	ULONGLONG ullTickCurrent = GetTickCount64();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPointSize(6);
	glLineWidth(3);

	// Draw.
	DrawCurve(g_pCurve, iKeyCurrent);

#ifdef MEMORY_LEAKS_TEST_ENABLE_LEAK
	// Memory leak test.
	int* pI = new int(31);
#endif

	glutSwapBuffers();
	glutPostRedisplay();

	if (20 < (ullTickCurrent - ullTickStart)) // 20 milliseconds IDLE
	{
		// Increase the keyTime of the animation.
		if (iKeyCurrent == iKeyCount)
		{
			iKeyCurrent = 0;

#ifdef MEMORY_LEAKS_TEST
			g_pCurve->ClearPoints();

			static bool bOnce = true;
			if (bOnce)
			{
				bOnce = false;
				_CrtMemCheckpoint(&memState1);
			}
			else
			{
				_CrtMemCheckpoint(&memState2);

				if (_CrtMemDifference(&memState3, &memState1, &memState2))
				{
					_CrtMemDumpStatistics(&memState3);
				}

				_CrtMemCheckpoint(&memState1);
			}
#endif
		}
		else
			iKeyCurrent++;

		ullTickStart = ullTickCurrent;
	}
}

void DrawCurve(CCurve* pCurve, const int iKeyCurrent)
{
	const std::vector<const SLine*> vLines = pCurve->GetLines();
	std::vector<POINTFLOAT*>& vPoints = pCurve->GetPoints();
	const int iLinesLayer = 0;
	const static float fLinesLayerColorsArray[][4] = {
		{0.0f, 1.0f, 0.0f, 1.0f},
		{1.0f, 1.0f, 0.0f, 1.0f},
		{1.0f, 0.5f, 0.0f, 1.0f}
	};

	// Release old data.
	if (0 == iKeyCurrent)
	{
		pCurve->ClearPoints();
	}

	DrawCurveLines(pCurve, vLines, vPoints, iKeyCurrent, fLinesLayerColorsArray, iLinesLayer);
}

void DrawCurveLines(
	CCurve* pCurve,
	const std::vector<const SLine*>& vLines,
	std::vector<POINTFLOAT*>& vPoints, 
	const int iKeyCurrent, 
	const float(fLinesLayerColorsArray)[][4],
	const int iLinesLayer
)
{
	std::vector<const SLine*> vLinesNew;
	const float* fLinesCollorCurrentLayerArray = fLinesLayerColorsArray[iLinesLayer];

	const size_t szLinesCount = vLines.size();
	if (1 < szLinesCount)
	{
		// Draw lines on next layer.
		for (size_t szIndex = 0; szIndex < szLinesCount; szIndex++)
		{
			const SLine* pLine = vLines[szIndex];

			glColor4f(fLinesCollorCurrentLayerArray[0], fLinesCollorCurrentLayerArray[1], fLinesCollorCurrentLayerArray[2], fLinesCollorCurrentLayerArray[3]);
			g_pDraw->Line(pLine->start, pLine->end);

			// Calc next lines.
			if (0 < szIndex)
			{
				SLine* pLineNew = new SLine;
				pCurve->CalcLinePos(vLines[szIndex - 1], pLine, pLineNew, iKeyCurrent);
				vLinesNew.push_back(pLineNew);
			}
		}

		// Draw lines on next layer.
		DrawCurveLines(pCurve, vLinesNew, vPoints, iKeyCurrent, fLinesLayerColorsArray, iLinesLayer + 1);
	}
	else if (1 == szLinesCount) // Last line layer.
	{
		const size_t szCurvePoints = vPoints.size();
		const SLine* pLine = vLines[0];

		glColor4f(fLinesCollorCurrentLayerArray[0], fLinesCollorCurrentLayerArray[1], fLinesCollorCurrentLayerArray[2], fLinesCollorCurrentLayerArray[3]);
		g_pDraw->Line(pLine->start, pLine->end);

		// Draw a curve on the points.
		for (size_t szIndex = 0; szIndex < szCurvePoints; szIndex++)
		{
			glPointSize(2);
			glColor4f(0.5f, 0, 1.0f, 1.0f);
			g_pDraw->Point(*vPoints[szIndex]);
		}

		// Draw the main point of the brush on the last line.
		POINTFLOAT* pPoint = new POINTFLOAT;
		pCurve->CalcPointPos(pLine, pPoint, iKeyCurrent);
		glPointSize(6);
		glColor4f(1.0f, 0, 0, 1.0f);
		g_pDraw->Point(*pPoint);
		vPoints.push_back(pPoint);
	}
	else
	{
		exit(1);
	}

	// Release the layer lines.
	const size_t szLinesNewCount = vLinesNew.size();
	for (size_t szIndex = 0; szIndex < szLinesNewCount; szIndex++)
	{
		delete vLinesNew[szIndex];
	}

	vLinesNew.clear();
}