#include "Bullet.h"
#include "cAssetManager.h"




Bullet::Bullet(Vector2 coord, Vector2 vel, float rad) : worldCenterCoord(coord), velocity(vel), rad(rad)
{
}

Bullet::~Bullet()
{
}

void Bullet::renderKebalik()
{

	if (live) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, cAssetManager::getInstance().GetID(SPRITESHEET_BULLET));
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBegin(GL_QUADS);
		//glTexture ng map coordinate texture ke quad
		Vector2 x0y0(-15, -15);
		Vector2 x0y1(-15, 15);
		Vector2 x1y0(15, -15);
		Vector2 x1y1(15, 15);
		x0y0 = x0y0.rotate(3.14f);
		x0y1 = x0y1.rotate(3.14f);
		x1y1 = x1y1.rotate(3.14f);
		x1y0 = x1y0.rotate(3.14f);

		glColor4f(1, 1, 1, 1.f);
		glTexCoord2f(0, 1);
		glVertex3i(worldCenterCoord.x + x0y0.x, worldCenterCoord.y + x0y0.y, 47);
		glTexCoord2f(1, 1);
		glVertex3i(worldCenterCoord.x + x1y0.x, worldCenterCoord.y + x1y0.y, 47);
		glTexCoord2f(1, 0);
		glVertex3i(worldCenterCoord.x + x1y1.x, worldCenterCoord.y + x1y1.y, 47);
		glTexCoord2f(0, 0);
		glVertex3i(worldCenterCoord.x + x0y1.x, worldCenterCoord.y + x0y1.y, 47);
		glEnd();
		glColor4f(1, 1, 1, 1);
		glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_TEXTURE_2D);
	}

}

void Bullet::render()
{
	if (live) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, cAssetManager::getInstance().GetID(SPRITESHEET_BULLET));
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBegin(GL_QUADS);
		//glTexture ng map coordinate texture ke quad
		Vector2 x0y0(-15, -15);
		Vector2 x0y1(-15, 15);
		Vector2 x1y0(15, -15);
		Vector2 x1y1(15, 15);
		//x0y0 = x0y0.rotate(3.14f / 2);
		//x0y1 = x0y1.rotate(3.14f / 2);
		//x1y1 = x1y1.rotate(3.14f / 2);
		//x1y0 = x1y0.rotate(3.14f / 2);

		glColor4f(1, 1, 1, 1.f);

		glTexCoord2f(0, 1);
		glVertex3i(worldCenterCoord.x + x0y0.x, worldCenterCoord.y + x0y0.y, 47);
		glTexCoord2f(1, 1);
		glVertex3i(worldCenterCoord.x + x1y0.x, worldCenterCoord.y + x1y0.y, 47);
		glTexCoord2f(1, 0);
		glVertex3i(worldCenterCoord.x + x1y1.x, worldCenterCoord.y + x1y1.y, 47);
		glTexCoord2f(0, 0);
		glVertex3i(worldCenterCoord.x + x0y1.x, worldCenterCoord.y + x0y1.y, 47);
		//glTexCoord2f(worldCenterCoord.x,worldCenterCoord.y);
		//glVertex3i();

		glEnd();
		glColor4f(1, 1, 1, 1);
		glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_TEXTURE_2D);

		//glPointSize(5.f);
		//glBegin(GL_POINTS);
		//glVertex2f(worldCenterCoord.x + x0y0.x, worldCenterCoord.y + x0y0.y);
		//glVertex2f(worldCenterCoord.x + x1y0.x, worldCenterCoord.y + x1y0.y);
		//glVertex2f(worldCenterCoord.x + x1y1.x, worldCenterCoord.y + x1y1.y);
		//glVertex2f(worldCenterCoord.x + x0y1.x, worldCenterCoord.y + x0y1.y);
		//glEnd();
	}

}

void Bullet::update(float tpf)
{
	this->worldCenterCoord.x += velocity.x * tpf;
	this->worldCenterCoord.y += velocity.y * tpf;
	this->life -= tpf;
}

void Bullet::updateBulletEnemy(float tpf)
{
	this->worldCenterCoord.x += velocity.x * tpf;
	this->worldCenterCoord.y -= velocity.y * tpf;
	this->life -= tpf;
}

