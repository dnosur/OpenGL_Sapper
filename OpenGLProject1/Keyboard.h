#pragma once
#include <GLFW/glfw3.h>

#include "KeyboardKey.h"

#include "WindowPointerController.h"

class Keyboard
{
	GLFWwindow* window;

	KeyboardKey key;
public: 
	Keyboard();
	Keyboard(GLFWwindow* window);
	Keyboard(GLFWwindow* window, GLFWkeyfun handler);

	void Update();

	void HookOnKeyPress(GLFWkeyfun handler);

	void SetKey(KeyboardKey key);
	KeyboardKey GetKey();
};