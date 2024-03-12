#include "Vec2.h"
#include <cmath>

Vec2::Vec2()
{
}

Vec2::Vec2(float xin, float yin)
	: x(xin), y(yin)
{

}

Vec2 Vec2::operator + (const Vec2& rhs) const
{
	// TODO - DONE
	return Vec2(x + rhs.x, y + rhs.y);
}

Vec2 Vec2::operator - (const Vec2& rhs) const
{
	// TODO - DONE
	return Vec2(x - rhs.x, y - rhs.y);
}

Vec2 Vec2::operator / (const float val) const
{
	// TODO - DONE
	return Vec2(x / val, y / val);
}

Vec2 Vec2::operator * (const float val) const
{
	// TODO - DONE
	return Vec2(x * val, y * val);
}

bool Vec2::operator == (const Vec2& rhs) const
{
	// TODO - DONE
	return (x == rhs.x && y == rhs.y);
}

bool Vec2::operator != (const Vec2& rhs) const
{
	// TODO - DONE
	return (x != rhs.x || y != rhs.y);
}

void Vec2::operator += (const Vec2& rhs)
{
	// TODO - DONE
	this->x += rhs.x;
	this->y += rhs.y;
}

void Vec2::operator -= (const Vec2& rhs)
{
	// TODO - DONE
	this->x -= rhs.x;
	this->y -= rhs.y;
}

void Vec2::operator *= (const float val)
{
	// TODO - DONE
	this->x *= val;
	this->y *= val;
}

void Vec2::operator /= (const float val)
{
	// TODO - DONE
	this->x /= val;
	this->y /= val;
}

Vec2 Vec2::difference(const Vec2& rhs) const
{
	// TODO - DONE
	return Vec2(rhs.x - this->x, rhs.y - this->y);
}

float Vec2::length() const
{
	// TODO - DONE

	// Tested by comparing result to a 2D vector distance calculator
	// online.
	return std::sqrt((this->x * this->x) + (this->y * this->y));
}

//normalize vector. This should give a 2D vector a length of 1 but keep the same angle. - UNTESTED
Vec2 Vec2::normalize() const
{
	return Vec2((this->x / this->length()), (this->y / this->length()));
}

// extra credit
//float Vec2::length() const
//{
//	return 0;
//}