#include "imports.h"
#include "BasicShapes.h"
#include <iostream>
#include <cstring>

BasicShapes::BasicShapes() {
	bezierAccuarcy = 0.04f;
}

void BasicShapes::drawDot(int x, int y) {
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	glFlush();
}

void BasicShapes::drawLine(Point p1, Point p2) {
	glBegin(GL_LINES);
	glVertex3f(p1.x, p1.y, p1.z);
	glVertex3f(p2.x, p2.y, p2.z);
	glEnd();
}

void BasicShapes::drawCurve(Point p1, Point p2, Point p3, Point p4) {
	Point pOld = p1;
	for (double t = 0.0; t <= 1.0; t += bezierAccuarcy) {
		Point nextPoint = nextBezierPoint(p1, p2, p3, p4, t);
		drawLine(pOld, nextPoint);
		pOld = nextPoint;
	}
}

void BasicShapes::circleSpan(float x, float y, float percent, float radius) {
    
	int sections = 20;
	GLfloat twoPi = 2.0f * 3.14159f;
    
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y);
	for (int i = 0; i <= sections - ((200 - percent * 2) / 10); i++) {
		glVertex2f(radius * cos(i * twoPi / sections) + x,
                   radius * sin(i * twoPi / sections) + y);
	}
	glEnd();
}

void BasicShapes::hallowCircle(float x, float y, float radius) {
	glBegin(GL_LINE_LOOP);

	for (int i = 0; i < 360; i++) {
		float degInRad = i * DEG2RAD;
		glVertex2f(cos(degInRad) * radius + x, sin(degInRad) * radius + y);
	}

	glEnd();
}

void BasicShapes::solidCircle(float x, float y, float radius) {
	circleSpan(x, y, 100, radius);
}

void BasicShapes::drawBar(float startX, float startY, float value) {
	float bar = value;
	glBegin(GL_QUADS);

	glColor3f(0.39, 0.778, 0.759);
	glVertex2f(startX, startY);
	glVertex2f(startX, startY + 16);
	glVertex2f(startX + bar, startY + 16);
	glVertex2f(startX + bar, startY);

	glEnd();
}

void BasicShapes::renderBitmapString(float x, float y, void *font,
                                     const char *string) {
	const char *c;
	glRasterPos2f(x, y);
	for (c = string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}

void BasicShapes::renderScore(char* score) {
	glColor3f(0.847, 0.902, 0.925);
	solidCircle(WINWIDTH / 2, WINHEIGHT / 2, 50);
	hallowCircle(WINWIDTH / 2, WINHEIGHT / 2, 50);

	glColor3f(0.204, 0.220, 0.220);
	renderBitmapString(WINWIDTH / 2 - (strlen(score) * 10 / 2),
			WINHEIGHT / 2 - 6, GLUT_BITMAP_HELVETICA_18, score);
}

Point BasicShapes::nextBezierPoint(Point p1, Point p2, Point p3, Point p4,
		double t) {
	Point nextPoint;
	nextPoint.x = pow((1 - t), 3) * p1.x + 3 * t * pow((1 - t), 2) * p2.x
			+ 3 * (1 - t) * pow(t, 2) * p3.x + pow(t, 3) * p4.x;
	nextPoint.y = pow((1 - t), 3) * p1.y + 3 * t * pow((1 - t), 2) * p2.y
			+ 3 * (1 - t) * pow(t, 2) * p3.y + pow(t, 3) * p4.y;
	nextPoint.z = 0;

	return nextPoint;
}
