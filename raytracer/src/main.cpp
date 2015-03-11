#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <Windows.h>
#include "st.h"
#include "Scene.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

int win_width = 512;
int win_height = 512;

Scene *scene = NULL;

void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	win_width = w;
	win_height = h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(0., 1., 0., 1.);
	glViewport(0, 0, w, h);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glutPostRedisplay();
}

static void usage()
{
	printf("Usage:\n");
	printf("./raytracer <sceneFileName>\n");
	printf("Scene file format supports the following commands:\n");
	printf("Camera ex ey ez ux uy uz lx ly lz fovy aspect\n");
	printf("Output width height <filename>\n");
	printf("BounceDepth depth\n");
	printf("ShadowBias bias\n");
	printf("PushMatrix\n");
	printf("PopMatrix\n");
	printf("Rotate rx ry rz\n");
	printf("Translate tx ty tz\n");
	printf("Scale sx sy sz\n");
	printf("Sphere cx cy cz r\n");
	printf("Triangle x1 y1 z1 x2 y2 z2 x3 y3 z3\n");
	printf("AmbientLight r g b\n");
	printf("PointLight px py pz\n");
	printf("DirectionalLight dx dy dz r g b\n");
	printf("Material ra ga ba rd gd bd rs gs bs rr gr br shine\n");
	exit(-1);
}

int main(int argc, char *argv[])
{
	if (argc != 2) usage();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(win_width, win_height);

	glutCreateWindow("Ray Tracer: CS148 Assignment 6");
	init();

	scene = new Scene(argv[1]);
	scene->Render();
	
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glutMainLoop();
}