#pragma once
#include "SLine.hpp"

interface ICurve
{
	virtual ~ICurve() = default;
	virtual void Clear() = 0;
	virtual void ClearLines() = 0;
	virtual void ClearPoints() = 0;
	virtual void AddLine(const SLine* pLine) = 0;
	virtual const std::vector<const SLine*>& GetLines() = 0;
	virtual std::vector<POINTFLOAT*>& GetPoints() = 0;
	virtual const int GetKeyCount() = 0;
	virtual void CalcLinePos(const SLine* psLine1Pos, const SLine* psLine2Pos, SLine* psPosCurrent, const int iKeyCurrent) = 0;
	virtual void CalcPointPos(const SLine* psLine1Pos, POINTFLOAT* psPosCurrent, const int iKeyCurrent) = 0;
};