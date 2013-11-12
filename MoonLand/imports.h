#ifndef MoonLand_main_h
#define MoonLand_main_h

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

static const int WINWIDTH = 640, WINHEIGHT = 480, RENDERRATE = 20;
const float DEG2RAD = 3.14159 / 180;

class Point {
public:
	float x, y, z;
	void setxy(float x2, float y2) {
		x = x2;
		y = y2;
	}
	const Point & operator=(const Point & rPoint) {
		x = rPoint.x;
		y = rPoint.y;
		z = rPoint.z;

		return *this;
	}
};

#endif
