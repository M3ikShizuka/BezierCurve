#pragma once

#include "head.hpp"

namespace draw
{
	class CDraw
	{
	public:
		void Point(const POINTFLOAT& point);
		void Line(const POINTFLOAT& Start, const POINTFLOAT& End);
	};
	extern CDraw *g_pDraw;
}