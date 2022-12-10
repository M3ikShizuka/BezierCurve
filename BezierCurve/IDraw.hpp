#pragma once
#include "head.hpp"

interface IDraw
{
	virtual ~IDraw() = default;
	virtual void Point(const POINTFLOAT& point) = 0;
	virtual void Line(const POINTFLOAT& Start, const POINTFLOAT& End) = 0;
};