// Copyright 2015 Kelvin Chandra, Software Laboratory Center, Binus University. All Rights Reserved.
#pragma warning(disable:4996)
#include "cAssetManager.h"
#include "Globals.h"

cAssetManager::cAssetManager(void) {}
cAssetManager::~cAssetManager(void) {}

int cAssetManager::GetID(int img)
{
	return textures[img].GetID();
}

void cAssetManager::GetSize(int img, int *w, int *h)
{
	textures[img].GetSize(w, h);
}

bool cAssetManager::LoadImage(int img, char *filename, int type)
{
	int res;

	res = textures[img].Load(filename, type);
	if (!res) return false;

	return true;
}
bool cAssetManager::Load()
{
	int res;

	res = LoadImage(SPRITESHEET_PLAYERS, "Textures/Assets/ships.png", GL_RGBA);
	if (!res) return false;
	for (int j = 0; j < 2; j++) {
		for (int i = 0; i < 17; i++) {
			float x0, y0, x1, y1;
			int tex_w, tex_h;
			GetSize(GetID(SPRITESHEET_PLAYERS), &tex_w, &tex_h);
			float sprite_width = 32.0f/ tex_w;
			float sprite_height = 32.0f/ tex_h;
			x0 = sprite_width*i;
			x1 = sprite_width*(i + 1);
			y0 = sprite_height*j;
			y1 = sprite_height*(j + 1);
			player->push_back(new cSprite(GetID(SPRITESHEET_PLAYERS), x0, y0, x1, y1));
		}
	}
	res = LoadImage(SPRITESHEET_BULLET, "Textures/Assets/bullet.png", GL_RGBA);
	if (!res) return false;
	for (int j = 0; j < 1; j++) {
		float x0, y0, x1, y1;
		int tex_w, tex_h;
		GetSize(GetID(SPRITESHEET_BULLET), &tex_w, &tex_h);
		float sprite_width = 100.0f / tex_w;
		float sprite_height = 100.0f / tex_h;
			x0 = sprite_width*j;
			x1 = sprite_width*(j + 1);
			y0 = 0;
			y1 = sprite_height;
			bullet->push_back(new cSprite(GetID(SPRITESHEET_BULLET), x0, y0, x1, y1));
	}
	res = LoadImage(BACKGROUND_MENU, "Textures/Assets/bgMenu.png", GL_RGBA);
	if (!res)printf("gagal");
	res = LoadImage(BACKGROUND_GAME, "Textures/Assets/bg.png", GL_RGBA);
	if (!res)printf("gagal");
	


	return true;
}

