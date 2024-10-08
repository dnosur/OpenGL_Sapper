#include "Color.h"

Color::Color()
{
	r = g = b = a = .0f;
}

Color::Color(float r, float g, float b, float a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

bool Color::operator==(const Color& other) const
{
	return other.r == r && other.g == g && 
		other.b == b && other.a == a;
}

bool Color::operator!=(const Color& other) const
{
	return !(*this == other);
}

Color& Color::operator=(const Color& other)
{
	if (this != &other) {
		r = other.r;
		g = other.g;
		b = other.b;
		a = other.a;
	}
	return *this;
}