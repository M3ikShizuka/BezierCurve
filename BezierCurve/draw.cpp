#include "draw.hpp"

namespace draw
{
	CDraw *g_pDraw = nullptr;

	void CDraw::Point(const POINTFLOAT& point)
	{
		glBegin(GL_POINTS);
		glVertex3f(point.x, point.y, 0.0);
		glEnd();
	}

	void CDraw::Line(const POINTFLOAT& Start, const POINTFLOAT& End)
	{
		glBegin(GL_LINES);
		glVertex3f(Start.x, Start.y, 0.0);
		glVertex3f(End.x, End.y, 0.0);
		glEnd();
		
		this->Point(Start);
		this->Point(End);
	}
}