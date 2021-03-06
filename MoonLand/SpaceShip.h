#ifndef __MoonLand__SpaceShip__
#define __MoonLand__SpaceShip__
#include "Terrain.h"

class SpaceShip {
public:
	SpaceShip(float startX, float startY);
	void move();
	void render();
	void reset();
	void endGame();
	void frameCollision();
	void useFuel(float usage);
    void decreaseTime(float timePassed);
	void rotate(float rotationDeg);
	void setAcceleration(float speedX, float speedY);
    void checkCollision(Terrain terrain);
    void checkFuelandTime();
	float getY();
	bool isGameOver();
	Point *getPositions();
private:
	void draw();
	void drawFuel();
    void drawTimer();
    void loseGame();
    void winGame();
	Point getRotatedPoint(float x, float y);
	float x, y, startX, startY, rotateDeg, speedX, speedY, shipWidth,
			shipHeight, fuel, time, fuelUsage, gravitySpeed;
	bool GameOver;
};

#endif
