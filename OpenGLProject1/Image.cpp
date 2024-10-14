#include "Image.h"

Image::Image()
{
	path = title = nullptr;
	image = -1;
}

Image::Image(const char* title, const char* path, GLint image)
{
	this->title = new char[strlen(title) + 1];
	strcpy_s(this->title, strlen(title) + 1, title);

	this->path = new char[strlen(path) + 1];
	strcpy_s(this->path, strlen(path) + 1, path);

	this->image = image;
}

bool Image::operator==(const Image& other) const
{
	return !strcmp(other.title, this->title) && !strcmp(other.path, this->path) && other.image == image;
}

bool Image::operator!=(const Image& other) const
{
	return !(*this == other);
}

Image& Image::operator=(const Image& other)
{
    if (this == &other) {
        return *this;
    }

    this->title = new char[strlen(other.title) + 1];
    strcpy_s(this->title, strlen(other.title) + 1, other.title);


	this->path = new char[strlen(other.path) + 1];
	strcpy_s(this->path, strlen(other.path) + 1, other.path);

	this->image = other.image;

    return *this;
}
