#pragma once
#include <math.h>

class Vec2
{
public:
	float x = 0.0f;
	float y = 0.0f;

	//default constructor
public:
	Vec2() { }

	//overloaded constructor
	Vec2(float x, float y) : x(x), y(y) { }

	Vec2 operator + (const Vec2& rhs)
	{
		return Vec2(x + rhs.x, y + rhs.y);
	}
	//overload + operator
	Vec2& operator += (const Vec2& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}
	Vec2 operator - (const Vec2& rhs)
	{
		return Vec2(x - rhs.x, y - rhs.y);
	}
	//overload - operator
	Vec2& operator -= (const Vec2& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}
	Vec2 operator * (float rhs)
	{
		return Vec2(x * rhs, y * rhs);
	}

	Vec2& operator *= (float rhs)
	{
		x *= rhs;
		y *= rhs;
		return *this;
	}
	Vec2 operator / (float rhs)
	{
		return Vec2(x / rhs, y / rhs);
	}

	Vec2& operator /= (float rhs)
	{
		x /= rhs;
		y /= rhs;
		return *this;
	}

	bool operator == (const Vec2& rhs)
	{
		return x == rhs.x && y == rhs.y;
	}
	bool operator != (const Vec2& rhs)
	{
		return !(x == rhs.x && y == rhs.y);
	}

	float Length()
	{
		return (float)sqrt(x * x + y * y);
	}
	float Magnitude()
	{
		return Length();
	}
	Vec2 Normalise()
	{
		float len = Length();
		return Vec2(x / len, y / len);
	}
	float Dot(const Vec2& rhs)
	{
		return x * rhs.x + y * rhs.y;
	}
};

