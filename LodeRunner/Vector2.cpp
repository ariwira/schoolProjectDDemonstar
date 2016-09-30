#include "Vector2.h"
#include <math.h>




Vector2 Vector2::operator+(Vector2 a) const
{
	return Vector2(this->x + a.x, this->y + a.y);
}

Vector2 Vector2::operator-(Vector2 a) const
{
	return Vector2(this->x - a.x, this->y - a.y);
}

Vector2 Vector2::operator*(float scalar) const
{
	return Vector2(this->x * scalar, this->y* scalar);
}

Vector2 Vector2::rotate(float deg)
{
	return Vector2((this->x * cos(deg)) - (this->y * sin(deg)), (this->x * sin(deg) + this->y * cos(deg)));
}

void Vector2::operator+=(Vector2 a)
{
	this->x += a.x;
	this->y += a.y;
}

void Vector2::operator-=(Vector2 a)
{
	this->x -= a.x;
	this->y -= a.y;
}

void Vector2::normalize()
{
	float length = sqrt((x*x) + (y*y));
	this->x = x / length;
	this->y = y / length;
}

Vector2::Vector2(float x, float y) : x(x), y(y)
{

}

float Vector2::getLength()
{
	return sqrt((this->x * this->x) + (this->y * this->y));
}


Vector2::~Vector2()
{
}
