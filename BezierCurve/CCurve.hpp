#pragma once
#include "head.hpp"

struct SLine;
class CCurve;

extern CCurve* g_pCurve;

struct SLine
{
	POINTFLOAT start,
		end;
};

class CCurve 
{
private:
	std::vector<const SLine*> vLines;
	std::vector<POINTFLOAT*> vPoints;
	const int iKeyCount;

public:
	CCurve();
	~CCurve();

	void Clear();
	void ClearPoints();
	void AddLine(const SLine* pLine);
	const std::vector<const SLine*>& GetLines();
	std::vector<POINTFLOAT*>& GetPoints();
	const int GetKeyCount();
	void CalcLinePos(const SLine* psLine1Pos, const SLine* psLine2Pos, SLine* psPosCurrent, const int iKeyCurrent);
	void CalcPointPos(const SLine* psLine1Pos, POINTFLOAT* psPosCurrent, const int iKeyCurrent);
};