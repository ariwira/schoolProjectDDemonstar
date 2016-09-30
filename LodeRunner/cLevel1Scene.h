// Copyright 2015 Kelvin Chandra, Software Laboratory Center, Binus University. All Rights Reserved.
#pragma once
#include "Globals.h"
#include "cScene.h"
#include "cPlayer.h"
#include "cEnemy.h"
#include "cRect.h"
#define TOTAL_TILE_Y 430
#define TOTAL_TILE_X 400
#define TILE_SIZE 32
#define TEXTURE_TILE_SIZE 32


class cLevel1Scene:public cScene
{
public:
	static cLevel1Scene& getInstance()
	{
		static cLevel1Scene instance;
		return instance;
	}
	cLevel1Scene();
	~cLevel1Scene();
	cPlayer *player;
	std::vector<Enemy> enemies;
	cRect visible_area;
	int score, highscore, enemyPosX;
	bool waveHabis = false;
	int waveLevel = 1;
	int enemyKilled = 0;
	int enemySpawn = 0;
	int waveEnemy = 3;
	bool spawnComplete = false;
	float spawnCooldown = 1.f;
	float EnemyHealthInit;
	float EnemySpeed;
	float EnemyBullSpeed;
	int EnemyPowerRandom;
	//float waveCooldown = 0;
	virtual int getHighscore();
    virtual void Random();
	virtual void Render();

	virtual void Init();

	virtual void Update(float tpf = 0.0333);

	virtual void ReadKeyboard(unsigned char key, int x, int y, bool press);

	virtual void ReadSpecialKeyboard(unsigned char key, int x, int y, bool press);

	virtual void ReadMouse(int button, int state, int x, int y);
	void checkCollision(std::vector<Bullet>* playerBullet, std::vector<Bullet>* enemyBullet);

private:
	bool keys[255];
};

