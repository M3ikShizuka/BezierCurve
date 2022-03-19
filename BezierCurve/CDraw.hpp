#pragma once
#include "head.hpp"
#include <glut.h>

#pragma comment (lib, "Opengl32.lib")
#pragma comment (lib, "glut32.lib")
#pragma comment (lib, "GLU32.lib")

class CDraw;

extern CDraw* g_pDraw;

class CDraw
{
public:
	void Point(const POINTFLOAT& point);
	void Line(const POINTFLOAT& Start, const POINTFLOAT& End);
};