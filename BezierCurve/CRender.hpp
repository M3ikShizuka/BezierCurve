#pragma once
#include "IRender.hpp"
#include "IDraw.hpp"
#include "ICurve.hpp"

class CRender final : public IRender
{
private:
	const int iScreenX = 600,
		iScreenY = 450;
	IDraw* pDraw;
	ICurve* pCurve;

public:
	CRender(IDraw* pDraw_, ICurve* pCurve_);
	virtual ~CRender();

public:
	virtual void InitRender(int argc, char* argv[]);
	virtual void RenderScene();

private:
	virtual void InitCurve();
	virtual void ReleaseCurve();
	virtual void DrawCurve(ICurve* pCurve, const int iKeyCurrent);
	virtual void DrawCurveLines(
		ICurve* pCurve,
		const std::vector<const SLine*>& vLines,
		std::vector<POINTFLOAT*>& vPoints,
		const int iKeyCurrent,
		const float(fLinesLayerColorsArray)[][4],
		const int iLinesLayer
	);
};