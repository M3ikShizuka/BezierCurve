#include "main.hpp"
#include "draw.hpp"
#include "curve.hpp"

const int g_iScreenX= 600,
			g_iScreenY = 450;

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(g_iScreenX, g_iScreenY);
	glutCreateWindow("ShizukaSystems::BezierCurve");
	// »нициализа€ци€ кривых безье
	InitBezier();
	glutReshapeFunc(Reshape);
	glutDisplayFunc(RenderScene);
	glutMainLoop();

	return 0;
}

void Reshape(int w, int h)
{
	glViewport(0, 0, g_iScreenX, g_iScreenY);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, g_iScreenX, g_iScreenY, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void RenderScene(void)
{
	static int iKeyCurrent = 0;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPointSize(6);
	glLineWidth(3);
	g_pBezier->Draw(iKeyCurrent);
	glutSwapBuffers();
	glutPostRedisplay();
	// ”величиваем keyTime анимации
	if (iKeyCurrent == 100)
		iKeyCurrent = 0;
	else
		iKeyCurrent++;
}