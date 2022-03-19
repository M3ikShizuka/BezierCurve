#include "CCurve.hpp"

CCurve* g_pCurve = nullptr;

CCurve::CCurve() : iKeyCount(100)
{

}

CCurve::~CCurve()
{
	// Clear lines vector.
	this->Clear();
}

void CCurve::Clear()
{
	const size_t szLinesCount = this->vLines.size();
	
	// Release memory.
	for (size_t szIndex = 0; szIndex < szLinesCount; szIndex++)
	{
		delete this->vLines[szIndex];
	}
		
	this->vLines.clear();

	this->ClearPoints();
}

void CCurve::ClearPoints()
{
	const size_t szCurvePoints = this->vPoints.size();

	// Release memory.
	for (size_t szIndex = 0; szIndex < szCurvePoints; szIndex++)
	{
		delete this->vPoints[szIndex];
	}

	this->vPoints.clear();
}

void CCurve::AddLine(const SLine *pLine)
{
	this->vLines.push_back(pLine);
}

const std::vector<const SLine*>& CCurve::GetLines()
{
	return this->vLines;
}

std::vector<POINTFLOAT*>& CCurve::GetPoints()
{
	return this->vPoints;
}

const int CCurve::GetKeyCount()
{
	return this->iKeyCount;
}

void CCurve::CalcLinePos(const SLine* psLine1Pos, const SLine* psLine2Pos, SLine* psPosCurrent, const int iKeyCurrent)
{
	psPosCurrent->start.x = psLine1Pos->start.x + ((psLine1Pos->end.x - psLine1Pos->start.x) / this->iKeyCount * iKeyCurrent);
	psPosCurrent->start.y = psLine1Pos->start.y + ((psLine1Pos->end.y - psLine1Pos->start.y) / this->iKeyCount * iKeyCurrent);

	psPosCurrent->end.x = psLine2Pos->start.x + (((psLine2Pos->end.x - psLine2Pos->start.x) / this->iKeyCount) * iKeyCurrent);
	psPosCurrent->end.y = psLine2Pos->start.y + (((psLine2Pos->end.y - psLine2Pos->start.y) / this->iKeyCount) * iKeyCurrent);
}

void CCurve::CalcPointPos(const SLine* psLine1Pos, POINTFLOAT* psPosCurrent, const int iKeyCurrent)
{
	psPosCurrent->x = psLine1Pos->start.x + ((psLine1Pos->end.x - psLine1Pos->start.x) / this->iKeyCount * iKeyCurrent);
	psPosCurrent->y = psLine1Pos->start.y + ((psLine1Pos->end.y - psLine1Pos->start.y) / this->iKeyCount * iKeyCurrent);
}