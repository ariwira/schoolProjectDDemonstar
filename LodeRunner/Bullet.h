#pragma once
#pragma once
#include "Vector2.h"
#include "Globals.h"
class Bullet
{
public:
	Bullet(Vector2 coord, Vector2 vel, float rad);
	~Bullet();
	void render(GLfloat r, GLfloat g, GLfloat b);
	void render();
	void renderKebalik();
	void update(float tpf);
	void updateBulletEnemy(float tpf);
	Vector2 worldCenterCoord;
	Vector2 velocity;
	float rad;
	int type;
	bool live = true;
	float life = 6.f;
};

