// Copyright 2015 Kelvin Chandra, Software Laboratory Center, Binus University. All Rights Reserved.
#include "cPlayer.h"
#include "cSound.h"
#include "cGame.h"
#include "cMenuScene.h"


cPlayer::cPlayer()
{
}


cPlayer::~cPlayer()
{
}

void cPlayer::Render()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, playerSheet->at(animControl->Index())->Texture());
	glBegin(GL_QUADS);

	glTexCoord2f(playerSheet->at(animControl->Index())->X0(), playerSheet->at(animControl->Index())->Y1());	glVertex3i(x, y, 49);
	glTexCoord2f(playerSheet->at(animControl->Index())->X1(), playerSheet->at(animControl->Index())->Y1());	glVertex3i(x + Width(), y, 49);
	glTexCoord2f(playerSheet->at(animControl->Index())->X1(), playerSheet->at(animControl->Index())->Y0());	glVertex3i(x + Width(), y + Height(), 49);
	glTexCoord2f(playerSheet->at(animControl->Index())->X0(), playerSheet->at(animControl->Index())->Y0());	glVertex3i(x, y + Height(), 49);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	for (auto i = bullets.rbegin(); i != bullets.rend(); ++i)
	{
		//i->render(0.f, 0.f, 1.f);
		i->render();
	}
}

void cPlayer::Init()
{
	animControl = new cAnimControl();
	life = 15;
	level = 1;
	playerPower = 5;
	cooldown = 0;
	cooldownAwal = 2.f;
	speed = 10*10;
	bulletSpeed = 10*15;
	animControl->AddAnim("StraightLoop", "terbang_kanan", 9, 16, 0.5f);
	animControl->AddAnim("StraightLoop", "terbang_kiri", 0, 7, 0.5f);
	//animControl->AddAnim("NoLoop", "jump", 2, 2, 0.5f);
	animControl->AddAnim("NoLoop", "idle", 8, 8, 0.5f);
	
}

void cPlayer::Update(float tpf /*= 0.0333*/)
{
	if (exp == 10) {
		level += 1;
		life += 5;
		playerPower += 0.2;
		cooldownAwal += 0.05f;
		speed += 1;
		bulletSpeed += 1;
		exp = 0;
	}
	if (cooldown > 0)
		this->cooldown -= tpf;
	animControl->UpdateAnim(tpf);
	
	if (keys['d'])
	{
		if (animControl->ActiveName() != "terbang_kanan")
			animControl->SetActiveAnim("terbang_kanan");
	}
	else if (keys['a'])
	{
		if (animControl->ActiveName() != "terbang_kiri")
			animControl->SetActiveAnim("terbang_kiri");
	}
	else if (keys['w'])
	{
		if (animControl->ActiveName() != "idle")
			animControl->SetActiveAnim("idle");
	}
	else if (keys['s'])
	{
		if (animControl->ActiveName() != "idle")
			animControl->SetActiveAnim("idle");
	}
	else
	{
		if (animControl->ActiveName() != "idle")
			animControl->SetActiveAnim("idle");
	}

	if (keys['a']) {
		if (getX() == 0) {
			x -= 0 * tpf;
		}
		else
		{
			x -= speed * tpf;
		}
		
	}
	else if (keys['d']) {
		if (getX() > 365) {
			x += 0 * tpf;
		}
		else
		{
			x += speed * tpf;
		}
		
	}
	else if (keys['w']) {
		if (getY() > 440) {
			y += 0 * tpf;
		}
		else
		{
			y += speed * tpf;
		}
		
	}
	else if (keys['s']) {
		if (getY() < 30) {
			y -= 0 * tpf;
		}
		else
		{
			y -= speed * tpf;
		}
	}
	if (keys[' '] == true && cooldown <= 0) {
		fire();
	}
	for (auto i = bullets.begin(); i != bullets.end(); i++) {
		i->update(tpf);
	}
}

void cPlayer::ReadKeyboard(unsigned char key, int x, int y, bool press)
{
	if (press)
	{
		keys[key] = true;
	}
	else
	{
		keys[key] = false;
	}
}

void cPlayer::ReadSpecialKeyboard(unsigned char key, int x, int y, bool press)
{
	if (press)
	{
		keys[key] = true;
	}
	else
	{
		keys[key] = false;
	}
}

void cPlayer::ReadMouse(int button, int state, int x, int y)
{

}
void cPlayer::fire()
{
	cooldown = cooldownAwal;
	Vector2 bulletCoord(x + width / 2, y + height / 2);
	Vector2 bulletVel(0, bulletSpeed);
	bullets.push_back(Bullet(bulletCoord, bulletVel, 5.f));
	cSound::getInstance().Play(SOUND_AMBIENT2);
	//printf("fire");
}

void cPlayer::die()
{
	life = 0;
	cGame::getInstance().UpdateScene(new cMenuScene());
}

void cPlayer::hit()
{

}

int cPlayer::getX() {
	return this->x;
}
int cPlayer::getY() {
	return this->y;
}