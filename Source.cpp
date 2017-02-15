#pragma once
#include<iostream>
#include <functional>
#include<cstdlib>
#include <Windows.h>
#include <glut.h>
#include <gl\GL.h>
#include <gl\GLU.h>
using namespace std;

GLsizei Height = 500;
GLsizei Width = 500;
#define WAIT 1000
int b[50][50] = { 0 };
double red = 1;
double green = 1;
double blue = 1;
bool isDecrease = true;

void CalculatePattern()
{
	for (int i = 49; i != 0; i--)
	{
		for (int f = 49; f != -1; f--)
		{
			int center = f;
			int left = f + 1;
			int right = f - 1;
			if (center == 0)
			{
				left = 0;
				right = center + 1;
			}
			if (center == 49)
			{
				left = 1;
				right = 49;
			}

			if (b[center][i] != 0 && b[right][i] != 0 && b[left][i] != 0)
				b[center][i - 1] = 0;

			else if (b[center][i] != 0 && b[right][i] == 0 && b[left][i] != 0)
				b[center][i - 1] = 0;

			else if (b[center][i] == 0 && b[right][i] != 0 && b[left][i] != 0)
				b[center][i - 1] = 0;

			else if (b[center][i] == 0 && b[right][i] == 0 && b[left][i] != 0)
				b[center][i - 1] = 1; // blue

			else if (b[center][i] != 0 && b[right][i] != 0 && b[left][i] == 0)
				b[center][i - 1] = 2; // green

			else if (b[center][i] != 0 && b[right][i] == 0 && b[left][i] == 0)
				b[center][i - 1] = 3; // purple

			else if (b[center][i] == 0 && b[right][i] != 0 && b[left][i] == 0)
				b[center][i - 1] = 4; // red
		}
	}
}

void Display()
{
	glColor3f(0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	for (int i = 49; i != 0; i--)
	{
		for (int j = 49; j != -1; j--)
		{
			if (b[i][j] == 1)
				glColor3f(0, 0, blue); // blue
			else if (b[i][j] == 2)
				glColor3f(0, green, 0); // green
			else if (b[i][j] == 3)
				glColor3f(red, green, 0); // purple
			else if (b[i][j] == 4)
				glColor3f(red, 0, 0); // red

			if (b[i][j] == 1 || b[i][j] == 2 || b[i][j] == 3 || b[i][j] == 4)
			{
				glBegin(GL_POLYGON);
				glVertex2f(i * 10, j * 10);
				glVertex2f((i * 10) + 10, j * 10);
				glVertex2f((i * 10) + 10, (j * 10) + 10);
				glVertex2f(i * 10, (j * 10) + 10);
				glVertex2f(i * 10, j * 10);
				glEnd();

			}
			else if (b[i][j] == 0)
			{
				glColor3f(0, 0, 0);
				glBegin(GL_LINE_STRIP);
				glVertex2f(i * 10, j * 10);
				glVertex2f((i * 10) + 10, j * 10);
				glVertex2f((i * 10) + 10, (j * 10) + 10);
				glVertex2f(i * 10, (j * 10) + 10);
				glVertex2f(i * 10, j * 10);
				glEnd();
			}
		}
	}

	std::less<double> less;
	std::greater<double> greater;
	if (isDecrease)
	{
		red -= 0.1;
		green -= 0.1;
		blue -= 0.1;
		if (less(red, 0.4))
		{
			isDecrease = false;
		}
	}
	else
	{
		red += 0.1;
		green += 0.1;
		blue += 0.1;
		if (greater(red, 1))
		{
			isDecrease = true;
		}
	}

	glFlush();
}
void myReshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
	Height = h;
	Width = w;
}
void myinit(int red, int green, int blue)
{
	glClearColor(red, green, blue, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, Width, 0.0, Height);
}
void waitAndRedraw(int foo)
{
	glutPostRedisplay();
	glutTimerFunc(WAIT, waitAndRedraw, 0);
}
void main(int argc, char **argv)
{
	b[24][49] = 1;
	CalculatePattern();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(Width, Height);
	glutCreateWindow("Cellular automata");
	glutDisplayFunc(Display);
	glutReshapeFunc(myReshape);
	glutTimerFunc(WAIT, waitAndRedraw, 0);
	myinit(1.0, 1.0, 1.0);
	glutMainLoop();
}