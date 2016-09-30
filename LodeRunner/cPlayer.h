// Copyright 2015 Kelvin Chandra, Software Laboratory Center, Binus University. All Rights Reserved.
#pragma once
#include"Globals.h"
#include "cSprite.h"
#include "cAnimation.h"
#include "cAnimControl.h"
#include "Bullet.h"
#define MAX_HEIGHT 480
#define MAX_WIDTH 400

class cPlayer
{
private:
	cAnimControl *animControl;
	std::vector<cSprite*> *playerSheet;
	float x, y;
	int width, height;
	bool keys[255];
	

public:
	cPlayer(std::vector<cSprite*> *playerSheet, float x, float y, int width, int height)
		:playerSheet(playerSheet), x(x), y(y), width(width), height(height) {}
	cPlayer();
	~cPlayer();
	std::vector<Bullet> bullets;
	int life;
	int exp;
	int level;
	float speed;
	float bulletSpeed;
	float cooldownAwal;
	float playerPower;
	float cooldown;
	virtual void Render();
	virtual void Init();
	virtual void Update(float tpf = 0.0333);
	virtual void ReadKeyboard(unsigned char key, int x, int y, bool press);
	virtual void ReadSpecialKeyboard(unsigned char key, int x, int y, bool press);
	virtual void ReadMouse(int button, int state, int x, int y);
	int getX();
	int getY();
	void fire();
	void die();
	void hit();
	int Height() const { return height; }
	void Height(int val) { height = val; }
	int Width() const { return width; }
	void Width(int val) { width = val; }
	float X() const { return x; }
	void X(float val) { x = val; }
	float Y() const { return y; }
	void Y(float val) { y = val; }
};

