#include "imports.h"
#include "BasicShapes.h"
#include "SpaceShip.h"

BasicShapes basicShapes;

SpaceShip::SpaceShip(float startX, float startY) {
    GameOver = false;
	this->startX = startX;
	this->startY = startY;
	fuel = 101.0f;
    time = 101.0f;
	fuelUsage = 0.6f;
	shipWidth = 76.0f;
	shipHeight = 97.0f;
	gravitySpeed = 1.622f;
	speedX = speedY = x = y = rotateDeg = 0;
}

void SpaceShip::draw() {
	Point abc[4];

	// Right & Left Carriers
	glLineWidth(2);
	glColor3f(0.799, 0.1098, 0.0588);

	glBegin(GL_TRIANGLE_STRIP);
	glVertex2i(startX + 10, (startY + 0));
	glVertex2i(startX + 20, (startY + 10));
	glVertex2i(startX + 7, (startY + 23));
	glVertex2i(startX + 17, (startY + 30));
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	glVertex2i(startX + 68, (startY + 0));
	glVertex2i(startX + 58, (startY + 10));
	glVertex2i(startX + 72, (startY + 23));
	glVertex2i(startX + 62, (startY + 30));
	glEnd();

	// Main Body
	glLineWidth(4);
	glColor3f(0.925, 0.925, 0.925);

	abc[0].setxy(startX + 22, (startY + 9));
	abc[1].setxy(startX + 14, (startY + 28));
	abc[2].setxy(startX + 16, (startY + 86));
	abc[3].setxy(startX + 39, (startY + 97));
	basicShapes.drawCurve(abc[0], abc[1], abc[2], abc[3]);

	abc[0].setxy(startX + 56, (startY + 9));
	abc[1].setxy(startX + 66, (startY + 28));
	abc[2].setxy(startX + 62, (startY + 86));
	abc[3].setxy(startX + 39, (startY + 97));
	basicShapes.drawCurve(abc[0], abc[1], abc[2], abc[3]);

	abc[0].setxy(startX + 22, (startY + 9));
	abc[1].setxy(startX + 34, (startY + 16));
	abc[2].setxy(startX + 44, (startY + 16));
	abc[3].setxy(startX + 56, (startY + 9));
	basicShapes.drawCurve(abc[0], abc[1], abc[2], abc[3]);

	basicShapes.solidCircle(startX + 39, (startY + 82), 13);
	basicShapes.solidCircle(startX + 39, (startY + 65), 20);
	basicShapes.solidCircle(startX + 39, (startY + 53), 22);
	basicShapes.solidCircle(startX + 39, (startY + 35), 23);
	basicShapes.solidCircle(startX + 27, (startY + 20), 9);
	basicShapes.solidCircle(startX + 52, (startY + 20), 9);

	// Glass Window
	glColor3f(0.827, 0.96, 1);
	basicShapes.solidCircle(startX + 39, (startY + 60), 10);

	// Middle Carrier
	glLineWidth(2.8);
	glColor3f(0.799, 0.1098, 0.0588);

	glBegin(GL_LINES);
	glVertex2i(startX + 39, (startY + 0));
	glVertex2i(startX + 39, (startY + 30));
	glEnd();

	// Glass Frame
	glLineWidth(2);
	basicShapes.hallowCircle(startX + 39, (startY + 60), 10);

}

void SpaceShip::drawFuel() {
	glColor3f(0.847, 0.902, 0.925);
	basicShapes.circleSpan(30, WINHEIGHT - 30, fuel, 20);
	glColor3f(0.807, 0.862, 0.885);
	basicShapes.hallowCircle(30, WINHEIGHT - 30, 20);
	glColor3f(1, 1, 1);
	basicShapes.renderBitmapString(17, WINHEIGHT - 64, GLUT_BITMAP_HELVETICA_12,
                                   "Fuel");
}

void SpaceShip::drawTimer() {
	glColor3f(0.847, 0.902, 0.925);
	basicShapes.circleSpan(WINWIDTH - 30, WINHEIGHT - 30, time, 20);
	glColor3f(0.807, 0.862, 0.885);
	basicShapes.hallowCircle(WINWIDTH - 30, WINHEIGHT - 30, 20);
	glColor3f(1, 1, 1);
	basicShapes.renderBitmapString(WINWIDTH - 42, WINHEIGHT - 64, GLUT_BITMAP_HELVETICA_12,
                                   "Time");
}

void SpaceShip::render() {
	glPushMatrix();
    
	glTranslatef(x + startX + shipWidth / 2, y + startY + shipHeight / 2, 0);
	glRotatef(rotateDeg, 0, 0, 1);
	glTranslatef(-x - startX - shipWidth / 2, -y - startY - shipHeight / 2, 0);
    
	glTranslatef(x, y, 0.0);
	draw();
	glPopMatrix();
    
	drawFuel();
    drawTimer();
}

void SpaceShip::frameCollision() {
	if (x + startX + shipWidth < 0)
		x = x + shipWidth / 2 + WINWIDTH;
	else if (x + startX > WINWIDTH)
		x = x - shipWidth / 2 - WINWIDTH;
}

void SpaceShip::checkCollision(Terrain terrain) {
	if (getY() < terrain.terrainHeight) {
		Point *bottomPoints = getPositions();
        
		if (bottomPoints[3].y <= terrain.getHight(bottomPoints[3].x)) {
			loseGame();
		} else if (abs(bottomPoints[0].y - bottomPoints[1].y) < 3) {
			if (bottomPoints[0].y <= terrain.getHight(bottomPoints[0].x)
                || bottomPoints[2].y
                <= terrain.getHight(bottomPoints[2].x)) {
				if (abs(bottomPoints[1].y - terrain.getHight(bottomPoints[1].x))
                    < 2) {
					winGame();
				} else {
					loseGame();
				}
			}
		} else {
			if (bottomPoints[0].y <= terrain.getHight(bottomPoints[0].x)
                || bottomPoints[1].y <= terrain.getHight(bottomPoints[1].x)
                || bottomPoints[2].y
                <= terrain.getHight(bottomPoints[2].x)) {
				loseGame();
			}
		}
	}
}

void SpaceShip::checkFuelandTime(){
    if(fuel <= 0 || time <= 0)
        loseGame();
}

void SpaceShip::setAcceleration(float speedX, float speedY) {
	if (fuel > 0) {
		this->speedX += speedX;
		this->speedY += speedY;
		useFuel(fuelUsage);
	}
}

void SpaceShip::useFuel(float usage) {
	fuel -= usage;
	if (fuel < 0)
        fuel = 0;
}

void SpaceShip::decreaseTime(float timePassed){
	time -= timePassed;
	if (time < 0)
        time = 0;
}

void SpaceShip::move() {
	speedY -= gravitySpeed;
	x += speedX * ((float) RENDERRATE / 1000.0f)
    * ((float) RENDERRATE / 200.0f);
	y += speedY * ((float) RENDERRATE / 1000.0f)
    * ((float) RENDERRATE / 200.0f);
}


void SpaceShip::rotate(float rotationDeg) {
	if (fuel > 0)
		rotateDeg += rotationDeg;
}

void SpaceShip::reset() {
	speedX = speedY = x = y = rotateDeg = 0;
	GameOver = false;
	fuel = 101.0f;
    time = 101.0f;
}

void SpaceShip::endGame() {
	speedX = 0;
	speedY = 0;
	GameOver = true;
}

void SpaceShip::loseGame(){
    endGame();
    basicShapes.renderScore((char *) "You Lose");
}

void SpaceShip::winGame(){
    endGame();
    basicShapes.renderScore((char *) "You Win");
}

bool SpaceShip::isGameOver() {
	return GameOver;
}

float SpaceShip::getY() {
	return startY + y;
}

Point *SpaceShip::getPositions() {
	Point *bottomPoints = new Point[4];
    
	bottomPoints[0] = getRotatedPoint(x + startX + 10, startY + y);
	bottomPoints[1] = getRotatedPoint(x + startX + 39, startY + y);
	bottomPoints[2] = getRotatedPoint(x + startX + 68, startY + y);
	bottomPoints[3] = getRotatedPoint(x + startX + 39, startY + y + shipHeight);
    
	return bottomPoints;
}

Point SpaceShip::getRotatedPoint(float ix, float iy) {
	Point rotatedP = *new Point();
	rotatedP.x = x + startX + shipWidth / 2
    + (ix - (x + startX + shipWidth / 2)) * cos(rotateDeg * DEG2RAD)
    - (iy - (y + startY + shipHeight / 2)) * sin(rotateDeg * DEG2RAD);
	rotatedP.y = y + startY + shipHeight / 2
    + (ix - (x + startX + shipWidth / 2)) * sin(rotateDeg * DEG2RAD)
    + (iy - (y + startY + shipHeight / 2)) * cos(rotateDeg * DEG2RAD);
    
	return rotatedP;
}
