#pragma once
#pragma once
#include "Vector2.h"
#include <vector>
#include "Bullet.h"
#include <string>
#include "cSprite.h"
#include "cAnimControl.h"

//#define state_moving 2
//#define state_idle 1
//#define attack_1 1  
//#define attack_0 0
//#define rotationTime 0.8f
class Enemy
{
public:
	int state;
	int power;
	bool enemyDie = false;
	float healthAwal;
	float kecepatan;
	float BulletSpeed;
	//int attack_type;
	int powerRandom;
	int powerAcak;
	float cooldownRandom;
	Vector2 worldCoord;
	Vector2 destination;
	Vector2 velocity;
	std::vector<Bullet> bullets;
	std::vector<cSprite*> *playerSheet;
	float health;
	void update(float tpf);
	void render();
	void Shot();
	void die();
	//cLevel1Scene* level1Scene;
	Enemy(std::vector<cSprite*> *sprites, Vector2 pos, int width, int height, float healthInit,float speed,float BullSpeed, int power);
	cAnimControl* animControl;
	~Enemy();

	float idle;
	int getWidth();
	int getHeight();
private:
	int width;
	int height;
	float cooldown;
};


