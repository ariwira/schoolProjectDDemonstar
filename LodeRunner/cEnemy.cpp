#include "cEnemy.h"
#include "cSound.h"
#include <iostream>





Enemy::Enemy(std::vector<cSprite*>* sprites, Vector2 pos, int width, int height, float healthInit, float speed, float BullSpeed, int powerAcak)
	: playerSheet(sprites), worldCoord(pos), width(width), height(height), 
	destination(Vector2(0, 0)), velocity(Vector2(0, 0))
{
	animControl = new cAnimControl();
	healthAwal = healthInit;
	health = healthAwal;
	kecepatan = 2 * speed;
	BulletSpeed = 2 * BullSpeed;
	powerRandom = powerAcak;
	animControl->AddAnim("NoLoop", "idle", 25, 25, 0.2f);
	
	idle = 0.f;
	destination = Vector2(184, 0);
	velocity = destination - worldCoord;
	velocity.normalize();
	velocity = velocity * kecepatan;
}

Enemy::~Enemy()
{
}

int Enemy::getWidth()
{
	return height;
}

int Enemy::getHeight()
{
	return width;
}

void Enemy::update(float tpf)
{
	cooldownRandom = rand() % 2 + 4;

	if (cooldown > 0)
		cooldown -= tpf;

	animControl->UpdateAnim(tpf);
	if (animControl->ActiveName() != "idle") {
		animControl->SetActiveAnim("idle");
	}

	for (auto i = bullets.begin(); i != bullets.end(); ++i)
	{
		i->updateBulletEnemy(tpf);
	}
	if (cooldown <= 0) {
		Shot();
	}
	
	if (abs(destination.x - worldCoord.x) < 10 && abs(destination.y - worldCoord.y) < 10) {
		velocity.x = 0;
		velocity.y = 0;
	}
	else {
		worldCoord.y += velocity.y * tpf;
	}
}

void Enemy::render() {
	if (!enemyDie) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, playerSheet->at(0)->Texture());
		glBegin(GL_QUADS);
		Vector2 x0y0(-width / 2, -height / 2);
		Vector2 x0y1(-width / 2, height / 2);
		Vector2 x1y0(width / 2, -height / 2);
		Vector2 x1y1(width / 2, height / 2);
		x0y0 = x0y0.rotate(3.14f);
		x0y1 = x0y1.rotate(3.14f);
		x1y1 = x1y1.rotate(3.14f);
		x1y0 = x1y0.rotate(3.14f);

		//glTexture ng map coordinate texture ke quad
		glTexCoord2f(playerSheet->at(animControl->Index())->X0(), playerSheet->at(animControl->Index())->Y1());
		glVertex3i(worldCoord.x + x0y0.x, worldCoord.y + x0y0.y, 49);
		glTexCoord2f(playerSheet->at(animControl->Index())->X1(), playerSheet->at(animControl->Index())->Y1());
		glVertex3i(worldCoord.x + x1y0.x, worldCoord.y + x1y0.y, 49);
		glTexCoord2f(playerSheet->at(animControl->Index())->X1(), playerSheet->at(animControl->Index())->Y0());
		glVertex3i(worldCoord.x + x1y1.x, worldCoord.y + x1y1.y, 49);
		glTexCoord2f(playerSheet->at(animControl->Index())->X0(), playerSheet->at(animControl->Index())->Y0());
		glVertex3i(worldCoord.x + x0y1.x, worldCoord.y + x0y1.y, 49);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		for (auto i = bullets.begin(); i != bullets.end(); ++i)
		{
			i->renderKebalik();

		}

		if (health >= 0.f) {
			float healtCoord = worldCoord.x + x1y0.x;
			glColor3f(1.0, 0.0, 0.0);
			glBegin(GL_POLYGON);
			glVertex2f(healtCoord + getWidth()*(health / healthAwal), worldCoord.y + 25.f);
			glVertex2f(healtCoord + getWidth()*(health / healthAwal), worldCoord.y + x1y0.y + 5);
			glVertex2f(healtCoord, worldCoord.y + x0y0.y + 5);
			glVertex2f(healtCoord, worldCoord.y + 25.f);
			glEnd();
			glColor4f(1.0, 1.0, 1.0, 1.0);
		}
		//tes tititk
		//glPointSize(5.f);
		//glBegin(GL_POINTS);
		//glVertex2f(worldCoord.x, worldCoord.y);
		//glVertex2f(worldCoord.x - getWidth()/2, worldCoord.y + getHeight()/2);
		//glVertex2f(worldCoord.x + getWidth()/2, worldCoord.y + getHeight()/2);
		////glVertex2f(bullets->worldCenterCoord.x, (*i).worldCenterCoord.y + 20);
		//glEnd();

	}
}

void Enemy::Shot()
{
	power = 2 + powerRandom;
	cooldown = cooldownRandom;
	Vector2 bulletCoord(worldCoord.x, worldCoord.y);
	Vector2 bulletVel(0, BulletSpeed);
	bullets.push_back(Bullet(bulletCoord, bulletVel, 5.f));
	//cSound::getInstance().Play(SOUND_AMBIENT2);
}

void Enemy::die()
{
	enemyDie = true;
}




