#pragma once
#include "IDraw.hpp"
#include "head.hpp"
#include <glut.h>

#pragma comment (lib, "Opengl32.lib")
#pragma comment (lib, "glut32.lib")
#pragma comment (lib, "GLU32.lib")

class CDraw final : public IDraw
{
public:
	void Point(const POINTFLOAT& point);
	void Line(const POINTFLOAT& Start, const POINTFLOAT& End);
};