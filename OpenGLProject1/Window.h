#pragma once
#include <GLFW/glfw3.h>
#include <iostream>

#include "Size.h"
#include "Mouse.h"
#include "Color.h"

class Window
{
protected:
	GLFWwindow* window;
	GLFWmonitor* monitor;
	GLFWwindow* share;

	Mouse mouse;
	Size size;

	Color backgroundColor;

	char* title;
	bool closed;

	void MakeWindow();

	void FillBackground();
public:

	Window();
	Window(Size size, const char* title, Color backgroundColor = Color(1, 1, 1), GLFWmonitor* monitor = NULL, GLFWwindow* share = NULL);

	GLFWwindow* GetWindow();
	GLFWmonitor* GetMonitor();
	GLFWwindow* GetShare();

	Size GetSize();
	char* GetTitle();

	virtual void Update();

	void MakeContext();

	void CloseWindow();
	const bool IsClosed();

	float PixelToGLX(float pixelX);
	float PixelToGLY(float pixelY);

	float GLXToPixel(float glx);
	float GLYToPixel(float gly);

	void SetBackgroundColor(Color color);
	Color GetBackgroundColor();

	Mouse& GetMouse();

	void Debug(bool norm = false);
};