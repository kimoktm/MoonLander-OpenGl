#include "imports.h"
#include "Terrain.h"
#include "SpaceShip.h"
#define KEY_ESCAPE 27

Terrain terrain(100);
SpaceShip spaceShip(300, 300);

void myInit(void) {
	glClearColor(0.189, 0.305, 0.407, 0.0);
	glColor3f(1.0f, 1.0f, 1.0f);
	glPointSize(4.0);
	glMatrixMode(GL_PROJECTION);
	glLineWidth(2.0f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glLoadIdentity();
	gluOrtho2D(0.0, WINWIDTH, 0.0, WINHEIGHT);
}

void myDisplay(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3f(0.203, 0.322, 0.427);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex2i(0, 0);
	glVertex2i(0, WINHEIGHT);
	glVertex2i(WINWIDTH / 2, 0);
	glVertex2i(WINWIDTH / 4, WINHEIGHT);
	glEnd();

	terrain.render();
	spaceShip.render();
    spaceShip.checkCollision(terrain);
    spaceShip.checkFuel();
	glutSwapBuffers();
}

void timer(int iUnused) {
	if (!spaceShip.isGameOver()) {
		spaceShip.move();
		spaceShip.frameCollision();
		spaceShip.useFuel(0.01f);
		glutPostRedisplay();
	}
	glutTimerFunc(RENDERRATE, timer, 0);

}

void keyboard(unsigned char key, int mousePositionX, int mousePositionY) {
	switch (key) {
	case 'r':
		spaceShip.reset();
		break;
	case KEY_ESCAPE:
		exit(0);
		break;
	default:
		break;
	}
}

void processSpecialKeys(int key, int x, int y) {

	switch (key) {
	case GLUT_KEY_UP:
		spaceShip.setAcceleration(0.0f, 60.0f);
		break;
	case GLUT_KEY_DOWN:
		spaceShip.setAcceleration(0.0f, -60.0f);
		break;
	case GLUT_KEY_LEFT:
		spaceShip.setAcceleration(-50.0f, 0.0f);
		spaceShip.rotate(1.0f);
		break;
	case GLUT_KEY_RIGHT:
		spaceShip.setAcceleration(50.0f, 0.0f);
		spaceShip.rotate(-1.0f);
		break;
	default:
		break;
	}
}

int main(int argc, char **argv) {
	const char* title = "MoonLand";

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(WINWIDTH, WINHEIGHT);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - WINWIDTH) / 2,
			(glutGet(GLUT_SCREEN_HEIGHT) - WINHEIGHT) / 2);
	glutCreateWindow((char*) title);
	glutDisplayFunc(myDisplay);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(processSpecialKeys);
	myInit();
	timer(0);
	glutMainLoop();
	return 0;
}
