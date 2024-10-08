#include "Size.h"

Size::Size()
{
	width = height = 0;
}

Size::Size(int width, int height)
{
	this->width = width;
	this->height = height;
}

int Size::GetWidth()
{
	return width;
}

int Size::GetHeight()
{
	return height;
}

void Size::SetWidth(int width)
{
	if (width < 0) {
		return;
	}
	this->width = width;
}

void Size::SetHeight(int height)
{
	if (height < 0) {
		return;
	}
	this->height = height;
}

bool Size::operator==(const Size& other) const
{
	return other.height == height && other.width == width;
}

bool Size::operator!=(const Size& other) const
{
	return !(*this == other);
}

Size& Size::operator=(const Size& other)
{
	if (this != &other)
	{
		width = other.width;
		height = other.height;
	}
	return *this;
}
