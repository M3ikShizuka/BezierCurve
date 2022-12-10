#pragma once
#include "head.hpp"
#include "ICurve.hpp"

class CCurve final : public ICurve
{
private:
	std::vector<const SLine*> vLines;
	std::vector<POINTFLOAT*> vPoints;
	const int iKeyCount;

public:
	CCurve();
	virtual ~CCurve();

public:
	virtual void Clear();
	virtual void ClearLines();
	virtual void ClearPoints();
	virtual void AddLine(const SLine* pLine);
	virtual const std::vector<const SLine*>& GetLines();
	virtual std::vector<POINTFLOAT*>& GetPoints();
	virtual const int GetKeyCount();
	virtual void CalcLinePos(const SLine* psLine1Pos, const SLine* psLine2Pos, SLine* psPosCurrent, const int iKeyCurrent);
	virtual void CalcPointPos(const SLine* psLine1Pos, POINTFLOAT* psPosCurrent, const int iKeyCurrent);
};