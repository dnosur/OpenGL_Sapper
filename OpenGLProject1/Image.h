#pragma once
#include <GLFW/glfw3.h>
#include <gl/GL.h>
#include <iostream>

struct Image
{
	char* title;
	char* path;

	GLuint image;

	Image();
	Image(const char* title, const char* path, GLint image);

	bool operator==(const Image& other) const;
	bool operator!=(const Image& other) const;

	Image& operator=(const Image& other);
};