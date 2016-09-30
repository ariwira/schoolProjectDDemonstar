#pragma once
class Vector2
{
public:
	float x, y;
	Vector2 operator+(Vector2 a) const;
	Vector2 operator-(Vector2 a) const;
	Vector2 operator*(float scalar) const;
	Vector2 rotate(float deg);
	void operator+= (Vector2 a);
	void operator-= (Vector2 a);
	void normalize();

	Vector2(float x, float y);

	float getLength();
	~Vector2();
};