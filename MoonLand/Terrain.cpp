#include "imports.h"
#include "Terrain.h"
#include <random>

Terrain::Terrain(float terrainHeight) {

	flatSize = HIGHTS_NUMBER / 6;
	xSpan = (float) WINWIDTH / (float) HIGHTS_NUMBER;
	this->terrainHeight = terrainHeight;
	generateHights();
}

void Terrain::render() {
	/*
	 glBegin(GL_TRIANGLE_STRIP);
	 glColor3f(0.123, 0.163, 0.2096);
	 for (int i = 0; i <= HIGHTS_NUMBER; i++) {
	 glVertex2f(i * xSpan, heights[i]);
	 }
	 glEnd();
	 */

	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(0.163, 0.198, 0.2496);
	for (int i = 0; i <= HIGHTS_NUMBER; i++) {
		glVertex2f(i * xSpan, heights[i]);
		glVertex2f(i * xSpan, 0);
	}
	glEnd();
}

float Terrain::getHight(int xPosition) {
	int xIndex = (xPosition * HIGHTS_NUMBER) / WINWIDTH;
	return heights[xIndex];
}

void Terrain::generateHights(void) {
	for (int i = 0; i <= HIGHTS_NUMBER; i++) {
		heights[i] = RandomFloat(40, terrainHeight);
	}

	int f1 = (int) RandomFloat(0, HIGHTS_NUMBER / 2);
	int f2 = (int) RandomFloat(HIGHTS_NUMBER / 2, HIGHTS_NUMBER);

	float h = heights[f1];

	for (int i = f1; i < f1 + flatSize; i++) {
		heights[i] = h;
	}

	h = heights[f2];
	for (int i = f2; i < f2 + flatSize; i++) {
		if (i < HIGHTS_NUMBER)
			heights[i] = h;
	}
}

float Terrain::RandomFloat(float a, float b) {
	float random = ((float) rand()) / (float) RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}
