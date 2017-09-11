#include "curve.hpp"
#include "draw.hpp"

const int iKeyCount = 100;

CBezier *g_pBezier = nullptr;

CBezier::CBezier()
{
	v_Lines.clear();
}

CBezier::~CBezier()
{
	uint32_t uLinesCount = this->v_Lines.size();
	for (uint32_t uIndex = 0; uIndex < uLinesCount; uIndex++)
	{
		delete this->v_Lines[uIndex];
	}

	this->v_Lines.clear();
}

void CBezier::AddLine(SLine *pLine)
{
	this->v_Lines.push_back(pLine);
}

void CBezier::Draw(const int &iKeyCurrent)
{
	this->DrawBezierLines(this->v_Lines, iKeyCurrent);
}

void CBezier::DrawBezierLines(std::vector<SLine*> &v_Lines, const int &iKeyCurrent)
{
	if (iKeyCurrent == 0)
	{
		uint32_t uBezierPoints = this->v_BezierPoints.size();
		for (uint32_t uIndex = 0; uIndex < uBezierPoints; uIndex++)
		{
			this->v_BezierPoints[uIndex];
		}
		this->v_BezierPoints.clear();
	}

	std::vector<SLine*> v_LinesNew;
	uint32_t uLinesCount = v_Lines.size();
	if (uLinesCount > 1)
	{
		for (uint32_t uIndex = 0; uIndex < uLinesCount; uIndex++)
		{
			SLine *pLine = v_Lines[uIndex];
			glColor4f(0, 1.0f, 0, 1.0f);
			draw::g_pDraw->Line(pLine->Start, pLine->End);

			if (uIndex > 0)
			{
				SLine *pLineNew = new SLine;
				CalcBezierLinePos(v_Lines[uIndex - 1], pLine, pLineNew, iKeyCurrent);
				glColor4f(0, 0, 1.0f, 1.0f);
				draw::g_pDraw->Line(pLineNew->Start, pLineNew->End);
				v_LinesNew.push_back(pLineNew);
			}
		}

		this->DrawBezierLines(v_LinesNew, iKeyCurrent);
	}
	else if (uLinesCount != 0)
	{
		SLine *pLine = v_Lines[0];
		draw::g_pDraw->Line(pLine->Start, pLine->End);

		uint32_t uBezierPoints = this->v_BezierPoints.size();
		for (uint32_t uIndex = 0; uIndex < uBezierPoints; uIndex++)
		{
			glPointSize(2);
			glColor4f(0.5f, 0, 1.0f, 1.0f);
			draw::g_pDraw->Point(*this->v_BezierPoints[uIndex]);
		}

		POINTFLOAT *pPoint = new POINTFLOAT;
		CalcBezierPointPos(pLine, pPoint, iKeyCurrent);
		glPointSize(6);
		glColor4f(1.0f, 0, 0, 1.0f);
		draw::g_pDraw->Point(*pPoint);
		this->v_BezierPoints.push_back(pPoint);
	}

	uint32_t uLinesNewCount = v_LinesNew.size();
	for (uint32_t uIndex = 0; uIndex < uLinesNewCount; uIndex++)
	{
		delete v_LinesNew[uIndex];
	}
	v_LinesNew.clear();
}

void InitBezier()
{
	g_pBezier = new CBezier;
	SLine *pLine = new SLine({ POINTFLOAT{ 100, 100 }, POINTFLOAT{ 150, 200 } });
	g_pBezier->AddLine(pLine);
	pLine = new SLine({ POINTFLOAT{ 150, 200 }, POINTFLOAT{ 450, 300 } });
	g_pBezier->AddLine(pLine);
	pLine = new SLine({ POINTFLOAT{ 450, 300 }, POINTFLOAT{ 460, 100 } });
	g_pBezier->AddLine(pLine);
}

void CalcBezierLinePos(const SLine* sLine1Pos, const SLine* sLine2Pos, SLine* sPosCurrent, const int& iKeyCurrent)
{
	sPosCurrent->Start.x = sLine1Pos->Start.x + ((sLine1Pos->End.x - sLine1Pos->Start.x) / iKeyCount * iKeyCurrent);
	sPosCurrent->Start.y = sLine1Pos->Start.y + ((sLine1Pos->End.y - sLine1Pos->Start.y) / iKeyCount * iKeyCurrent);

	sPosCurrent->End.x = sLine2Pos->Start.x + (((sLine2Pos->End.x - sLine2Pos->Start.x) / iKeyCount) * iKeyCurrent);
	sPosCurrent->End.y = sLine2Pos->Start.y + (((sLine2Pos->End.y - sLine2Pos->Start.y) / iKeyCount) * iKeyCurrent);
}

void CalcBezierPointPos(const SLine* sLine1Pos, POINTFLOAT * sPosCurrent, const int& iKeyCurrent)
{
	sPosCurrent->x = sLine1Pos->Start.x + ((sLine1Pos->End.x - sLine1Pos->Start.x) / iKeyCount * iKeyCurrent);
	sPosCurrent->y = sLine1Pos->Start.y + ((sLine1Pos->End.y - sLine1Pos->Start.y) / iKeyCount * iKeyCurrent);
}