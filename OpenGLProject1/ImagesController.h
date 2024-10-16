#pragma once
#include <GLFW/glfw3.h>
#include <gl/GL.h>
#include <GL//glut.h>
#include <vector>

#include "Size.h"
#include "Coord.h"
#include "Image.h"

#include "lib/stb_image.h"
#include "Color.h"

class ImagesController
{
	std::vector<Image> images;

	int GetIndexByTitle(char* title);
	void ChangeIfExist(Image image);
public:

	void Load(const char* path, const char* title);
	void LoadAndDrawImage(const char* path, const char* title, Coord position, Size size, Size windowSize);

	void DrawImage(const char* title, Coord position, Size size, Size windowSize, Color color = Color(1.0f, 1.0f, 1.0f));

	Image GetImageByTitle(const char* title);

	std::vector<Image> GetImages();
	void SetImages(std::vector<Image> images);

	int GetSize();

	void Clear();
};