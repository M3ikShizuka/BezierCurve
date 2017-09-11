#pragma once

#include "head.hpp"

struct SLine;
class CBeizer;

struct SLine
{
	POINTFLOAT Start,
		End;
};

class CBezier 
{
private:
	std::vector<SLine*> v_Lines;
	std::vector<POINTFLOAT*> v_BezierPoints;

public:
	CBezier();
	~CBezier();

	void AddLine(SLine *pLine);
	void Draw(const int &iKeyCurrent);
private:
	void DrawBezierLines(std::vector<SLine*> &v_Lines, const int &iKeyCurrent);
};
extern CBezier *g_pBezier;

void InitBezier();
void CalcBezierLinePos(const SLine* sLine1Pos, const SLine* sLine2Pos, SLine* sPosCurrent, const int& iKeyCurrent); void CalcBezierPointPos(const SLine* sLine1Pos, POINTFLOAT * sPosCurrent, const int& iKeyCurrent);
void CalcBezierPointPos(const SLine* sLine1Pos, POINTFLOAT * sPosCurrent, const int& iKeyCurrent);