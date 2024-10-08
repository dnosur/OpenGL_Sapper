#include "Mouse.h"
#include <iostream>

Mouse::Mouse()
{
	click = false;
	window = NULL;
}

Mouse::Mouse(GLFWwindow* window)
{
	this->window = window;
	double mouseX, mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);

	prev = Coord(mouseX, mouseY);
	curr = Coord(mouseX, mouseY);
	click = false;

	glfwSetWindowUserPointer(this->window, this);
	glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
		Mouse* mouse = static_cast<Mouse*>(glfwGetWindowUserPointer(window));
		if (mouse == nullptr) {
			return;
		}

		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
			mouse->click = true;
		}
	});
}

void Mouse::Update()
{
	double mouseX, mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);

	prev = curr;
	curr = Coord(mouseX, mouseY);

	if (click) {
		std::cout << "Click!\n";
	}
	click = false;
}

Coord Mouse::GetMouseCoord()
{
	return curr;
}

Coord Mouse::GetPrevMouseCoord()
{
	return prev;
}

bool Mouse::isClick()
{
	return click;
}

bool Mouse::IsEqual()
{
	return prev == curr;
}
