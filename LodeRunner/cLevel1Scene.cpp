// Copyright 2015 Kelvin Chandra, Software Laboratory Center, Binus University. All Rights Reserved.
#include "cLevel1Scene.h"
#include "cAssetManager.h"
#include "cGame.h"
#include "cMenuScene.h"
#include <iostream>
#pragma warning(disable:4996)

cLevel1Scene::cLevel1Scene()
{
	player = new cPlayer(cAssetManager::getInstance().player, 184, 50, TILE_SIZE, TILE_SIZE);
	std::ifstream in("highscore.txt");
	std::string highscoreC;
	if (!in) {
		printf("file ilang");
		exit(1);
	}
	else {
		if (in.is_open()) {
			std::getline(in, highscoreC);
		}
		highscore = std::stoi(highscoreC);
		in.close();
	}
	/*enemyPosX = rand() % 450;
	Vector2 enemyCoord(enemyPosX, 450);
	enemies.push_back(Enemy(cAssetManager::getInstance().player, enemyCoord, TILE_SIZE, TILE_SIZE));
	*/
	//enemy = new Enemy(cAssetManager::getInstance().player, Vector2(184, 450), TILE_SIZE, TILE_SIZE);
}

cLevel1Scene::~cLevel1Scene()
{
}

void cLevel1Scene::Init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	visible_area.top = GAME_HEIGHT;
	visible_area.bottom = 0;
	visible_area.left = 0;
	visible_area.right = GAME_WIDTH;
	glOrtho(visible_area.left, visible_area.right, visible_area.bottom, visible_area.top, 3, -101);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	player->Init();
	std::ifstream in("highscore.txt");
	std::string highscoreC;
	if (!in) {
		printf("file ilang");
		exit(1);
	}
	else {
		if (in.is_open()) {
			std::getline(in, highscoreC);
		}
		highscore = std::stoi(highscoreC);
		in.close();
	}
	//cSound::getInstance().Play(SOUND_AMBIENT1);
}

int cLevel1Scene::getHighscore()
{
	//std::cout << "score masuk " << highscore << "\n";
	return this->highscore;
}

void cLevel1Scene::Random()
{
	EnemyHealthInit = 5 + (2 * waveLevel) + (rand() % 3);
	EnemyPowerRandom = rand() % waveLevel * 2;
	EnemySpeed = 5 + rand() % (10 + waveLevel * 2);
	EnemyBullSpeed = 2 * EnemySpeed + rand() % (10 + (waveLevel * 2));
}

void cLevel1Scene::Render()
{

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, cAssetManager::getInstance().GetID(BACKGROUND_GAME));
	glBegin(GL_QUADS);

	glTexCoord2f(0, 1);	glVertex3i(0, 0, 100);
	glTexCoord2f(1, 1);	glVertex3i(0 + 400, 0, 100);
	glTexCoord2f(1, 0);	glVertex3i(0 + 400, 480, 100);
	glTexCoord2f(0, 0);	glVertex3i(0, 480, 100);

	glEnd();
	glDisable(GL_TEXTURE_2D);
	player->Render();
	for (auto i = enemies.begin(); i != enemies.end(); ++i)
	{
		i->render();
	}

	char scoreC[10] = { 0 };
	_itoa_s(score, scoreC, 10);
	char lifeC[10] = { 0 };
	if (player->life<0)
		_itoa_s(0, lifeC, 10);
	else
		_itoa_s(player->life, lifeC, 10);
	char playerLevel[10] = { 0 };
	_itoa_s(player->level, playerLevel, 10);
	char waveLevelS[10] = { 0 };
	_itoa_s(waveLevel, waveLevelS, 10);
	char highscoreC[10] = { 0 };
	_itoa_s(highscore, highscoreC, 10);
	renderBitmapString(10, 5, 9, GLUT_BITMAP_HELVETICA_10, "Score : ", 255, 255, 255);
	renderBitmapString(50, 5, 9, GLUT_BITMAP_HELVETICA_10, scoreC, 255, 255, 255);
	renderBitmapString(70, 5, 9, GLUT_BITMAP_HELVETICA_10, " [", 255, 255, 255);
	renderBitmapString(90, 5, 9, GLUT_BITMAP_HELVETICA_10,highscoreC, 255, 255, 255);
	renderBitmapString(110, 5, 9, GLUT_BITMAP_HELVETICA_10, "] ", 255, 255, 255);
	renderBitmapString(255, 5, 9, GLUT_BITMAP_HELVETICA_10, "Wave : ", 255, 255, 255);
	renderBitmapString(290, 5, 9, GLUT_BITMAP_HELVETICA_10, waveLevelS, 255, 255, 255);
	renderBitmapString(305, 5, 9, GLUT_BITMAP_HELVETICA_10, "Lv : ", 255, 255, 255);
	renderBitmapString(325, 5, 9, GLUT_BITMAP_HELVETICA_10, playerLevel, 255, 255, 255);
	renderBitmapString(340, 5, 9, GLUT_BITMAP_HELVETICA_10, "HP :", 255, 255, 255);
	renderBitmapString(365, 5, 9, GLUT_BITMAP_HELVETICA_10, lifeC, 255, 255, 255);
}



void cLevel1Scene::Update(float tpf /*= 0.0333*/)
{		
		if (spawnCooldown > 0) {
			//std::cout << "cooldown " << spawnCooldown << "\n";
			spawnCooldown -= tpf;
			//waveCooldown -= tpf;
		}/*
		if (waveCooldown > 0 && !waveHabis) {
			std::cout << "countdown cooldown "<<waveCooldown<<"\n";
			waveCooldown -= tpf;
		}else if(waveCooldown <= 0){*/
			if (!waveHabis) {
				while (enemySpawn != waveEnemy && spawnCooldown <= 0 && !spawnComplete)
				{
					Random();
					enemyPosX = rand() % 400;
					Vector2 enemyCoord(enemyPosX, 450);
					enemies.push_back(Enemy(cAssetManager::getInstance().player, enemyCoord, TILE_SIZE, TILE_SIZE, EnemyHealthInit, EnemySpeed, EnemyBullSpeed, EnemyPowerRandom));
					enemySpawn += 1;
					
					if (enemySpawn == waveEnemy) {
						spawnComplete = true;
						//enemySpawn = 0;
					}
					else {
						spawnComplete = false;
					}
					spawnCooldown = 1.f;
				}
			}
			else {
				spawnComplete = false;
			}
			//waveCooldown = 2.f;
			//enemySpawn = 0;
		
				
		player->Update();
		for (auto i = enemies.begin(); i != enemies.end(); ++i)
		{
			i->update(tpf);
			checkCollision(&player->bullets, &i->bullets);
		}
		if (enemyKilled == waveEnemy) {
			waveHabis = true;
		}
		else {
			//std::cout << "wave belom habis\n";
			waveHabis = false;
		}
		if (waveHabis) {
			waveEnemy += 1;
			waveLevel += 1;
			spawnComplete = false;
			enemyKilled = 0;
			waveHabis = false;
		}
		//std::cout << EnemyBullSpeed << "iniBUllmusuh\n";
		//std::cout << EnemySpeed << "inimusuh\n";
		//std::cout << waveLevel;
		/*if (enemies.size() == 0)
			waveHabis = true;*/
}

void cLevel1Scene::ReadKeyboard(unsigned char key, int x, int y, bool press)
{
	player->ReadKeyboard(key, x, y, press);
	if (press)
	{
		keys[key] = true;
	}
	else
	{
		keys[key] = false;
	}
	if (key == 27) {
		cGame::getInstance().UpdateScene(new cMenuScene());
	}
}

void cLevel1Scene::ReadSpecialKeyboard(unsigned char key, int x, int y, bool press)
{
	player->ReadSpecialKeyboard(key, x, y, press);
	if (press)
	{
		keys[key] = true;
	}
	else
	{
		keys[key] = false;
	}
}

void cLevel1Scene::ReadMouse(int button, int state, int x, int y)
{
	player->ReadMouse(button, state, x, y);
}

void cLevel1Scene::checkCollision(std::vector<Bullet>* playerBullet, std::vector<Bullet>* enemyBullet)
{
	for (auto i = playerBullet->begin(); i != playerBullet->end(); i++)
	{
		for (int j = 0; j < enemies.size();)
		{
			Vector2 titikPukul((*i).worldCenterCoord.x, (*i).worldCenterCoord.y + 20);
			Vector2 enemyCenter(enemies[j].worldCoord.x,
				enemies[j].worldCoord.y);
			Vector2 titikSayap1(enemies[j].worldCoord.x - enemies[j].getWidth() / 2, enemies[j].worldCoord.y + enemies[j].getHeight() / 2);
			Vector2 titikSayap2(enemies[j].worldCoord.x + enemies[j].getWidth() / 2, enemies[j].worldCoord.y + enemies[j].getHeight() / 2);
			Vector2 jarak = titikPukul - enemyCenter;
			Vector2 jarak1 = titikPukul - titikSayap1;
			Vector2 jarak2 = titikPukul - titikSayap2;

			if ((jarak.getLength() < 20.f || jarak1.getLength() < 20.f || jarak2.getLength() < 20.f) && i->live) {
				if (enemies[j].health > 0) {
					//delete j;
					enemies[j].health -= player->playerPower;
					if (enemies[j].health <= 0) {
						//delete enemies[j];
						//enemyKilled++;
						cSound::getInstance().Play(SOUND_AMBIENT3);
						if (enemies.size() > 1) {
							enemies[j] = enemies.back();
							enemies.pop_back();
							enemyKilled++;
							enemySpawn--;
							score += 10 * waveLevel;
							player->exp += 1;
						}
						else {
							//enemies.
							//enemies.erase(enemies.begin());
							//delete &enemies[j];
							//enemies.pop_back();
							enemyKilled++;
							enemySpawn--;
							score += 10 * waveLevel;
							player->exp += 1;
							
						}
					}
					else
					{
						j++;
					}
					i->live = false;
					//std::cout << "20\n";
				}
			}
			else {
				j++;
			}
		}
	}
	for (auto i = enemyBullet->begin(); i != enemyBullet->end(); i++) {
		for (auto j = enemies.begin(); j != enemies.end(); ++j) {
			Vector2 tengahnyaPlayer(player->getX() + player->Width() / 2, player->getY() + player->Height() / 2);
			Vector2 bulletnyaEnemy(i->worldCenterCoord.x, i->worldCenterCoord.y);
			//std::cout << "posisi" << j->worldCoord.y << "\n";
			if ((tengahnyaPlayer - bulletnyaEnemy).getLength() < 20.f && i->live) {
				player->life -= j->power;
				if (player->life <= 0) {
					if (score > highscore) {
						std::ofstream out;
						out.open("highscore.txt");
						out << highscore;
						out.close();
					}
					player->die();
				}
				else
				{
					i->live = false;
				}
			}
		}
	}
	for (auto j = enemies.begin(); j != enemies.end(); ++j)
	{	
		Vector2 tengahnyaPlayer(player->getX() + player->Width() / 2, player->getY() + player->Height() / 2);
		Vector2 enemyCenter(j->worldCoord.x, j->worldCoord.y);
		//Vector2 out(0, 0);
		Vector2 jarak = tengahnyaPlayer - enemyCenter;
		//Vector2 jarakOut = enemyCenter - out;
		//std::cout << "x " << jarakOut.x << "\n";
		std::cout << "y " << j->worldCoord.y << "\n";
		//std::cout << "get " << jarakOut.getLength() << "\n";
		if (jarak.getLength() < 32.f || j->worldCoord.y < 16.f) {
			player->die();
		}
		
	}
	//printf("%d\n", player->life);
	//printf("%f\n", j->health);*/
}

