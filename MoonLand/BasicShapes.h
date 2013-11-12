#ifndef __MoonLand__BezierCurve__
#define __MoonLand__BezierCurve__

class BasicShapes {
public:
	BasicShapes();
	void drawDot(int x, int y);
	void drawLine(Point p1, Point p2);
	void drawCurve(Point p1, Point p2, Point p3, Point p4);
	void circleSpan(float x, float y, float percent, float radius);
	void hallowCircle(float x, float y, float radius);
	void solidCircle(float x, float y, float radius);
	void drawBar(float startX, float startY, float health);
	void renderBitmapString(float x, float y, void *font, const char *string);
	void renderScore(char* score);
private:
	Point nextBezierPoint(Point p1, Point p2, Point p3, Point p4, double t);
	float bezierAccuarcy;
};

#endif
