// Copyright 2015 Kelvin Chandra, Software Laboratory Center, Binus University. All Rights Reserved.
#include "cMenuScene.h"
#include "cLevel1Scene.h"
#include "cGame.h"
#include <iostream>

cMenuScene::cMenuScene()
{/*
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
		this->highscore = std::stoi(highscoreC);
		in.close();
	}*/
	this->highscore = cLevel1Scene::getInstance().getHighscore();
}

//cMenuScene::cMenuScene(int Highscore)
//{
//	this->highscore = cLevel1Scene::getInstance().;
//}

cMenuScene::~cMenuScene()

{

}

void cMenuScene::Init()
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
	MusicState = true;
	highscore = cLevel1Scene::getInstance().getHighscore();
}

void cMenuScene::Update(float tpf /*= 0.0333*/)
{
}

void cMenuScene::Render()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, cAssetManager::getInstance().GetID(BACKGROUND_MENU));
	glBegin(GL_QUADS);

	glTexCoord2f(0, 1);	glVertex3i(0, 0, 100);
	glTexCoord2f(1, 1);	glVertex3i(0 + 400, 0, 100);
	glTexCoord2f(1, 0);	glVertex3i(0 + 400, 480, 100);
	glTexCoord2f(0, 0);	glVertex3i(0, 480, 100);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	renderBitmapString(150, 430, 9, GLUT_BITMAP_HELVETICA_18, "DDemonstar’ ", 255, 255, 255);

	renderBitmapString(90, 200, 9, GLUT_BITMAP_HELVETICA_18, "Press Any Key To Continue", 255, 255, 255);
	renderBitmapString(75, 100, 9, GLUT_BITMAP_HELVETICA_10, "How to Play: Press [W/A/S/D] Key to Move,\n [ESC] to", 255, 255, 255);
	renderBitmapString(150, 80, 9, GLUT_BITMAP_HELVETICA_10, "Back to Main Menu", 255, 255, 255);

	char highscoreC[10] = { 0 };
	_itoa_s(highscore, highscoreC, 10);
	renderBitmapString(10, 5, 9, GLUT_BITMAP_HELVETICA_10, "Highcore : ", 255, 255, 255);
	renderBitmapString(60, 5, 9, GLUT_BITMAP_HELVETICA_10, highscoreC, 255, 255, 255);
	if (MusicState) {
		char musicStateC[10] = { "ON" };
		renderBitmapString(370, 10, 9, GLUT_BITMAP_HELVETICA_10, musicStateC, 255, 255, 255);
	}
	else {
		char musicStateC[10] = { "OFF" };
		renderBitmapString(370, 10, 9, GLUT_BITMAP_HELVETICA_10, musicStateC, 255, 255, 255);
	}

	renderBitmapString(320, 10, 9, GLUT_BITMAP_HELVETICA_10, "Sound(M) : ", 255, 255, 255);
	
	

}

void cMenuScene::ReadKeyboard(unsigned char key, int x, int y, bool press)
{
	printf("Normal key: %d\n", key);
	if (press)
	{
		keys[key] = true;
	}
	else
	{
		keys[key] = false;
	}

	if (key == 13) {
		cGame::getInstance().UpdateScene(new cLevel1Scene());
	}
	if ((key == 'm' || key == 'M') && MusicState) {
		std::cout << "masuk";
		MusicState = false;
		cSound::getInstance().StopAll();
	}
	else if((key == 'm' || key == 'M') && !MusicState){
		std::cout << "keluar";
		MusicState = true;
		cSound::getInstance().Play(SOUND_AMBIENT1);
	}
}

void cMenuScene::ReadSpecialKeyboard(unsigned char key, int x, int y, bool press)
{
	printf("Special key: %d", key);
	if (press)
	{
		keys[key] = true;
	}
	else
	{
		keys[key] = false;
	}

	
}

void cMenuScene::ReadMouse(int button, int state, int x, int y)
{
}
