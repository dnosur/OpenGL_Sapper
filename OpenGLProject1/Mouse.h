#pragma once
#include <GLFW/glfw3.h>
#include "Coord.h"

class Mouse
{
	GLFWwindow* window;

	Coord prev;
	Coord curr;

	bool click;
public:
	Mouse();
	Mouse(GLFWwindow* window);

	void Update();

	Coord GetMouseCoord();
	Coord GetPrevMouseCoord();

	bool isClick();

	bool IsEqual();
};