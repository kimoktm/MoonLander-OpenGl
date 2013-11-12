#ifndef __MoonLand__Terrain__
#define __MoonLand__Terrain__

class Terrain {
public:
	Terrain(float terrainHeight);
	void render(void);
	void generateHights(void);
	float getHight(int xPosition);
	int terrainHeight;
private:
	float RandomFloat(float start, float end);
	static const int HIGHTS_NUMBER = 60;
	float heights[HIGHTS_NUMBER + 1];
	float xSpan;
	int flatSize;
};

#endif
