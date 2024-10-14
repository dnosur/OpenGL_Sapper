#include "Keyboard.h"


Keyboard::Keyboard()
{
	window = nullptr;
}

Keyboard::Keyboard(GLFWwindow* window)
{
	this->window = window;
	HookOnKeyPress([](GLFWwindow* window, int key, int scancode, int action, int mods) {
		WindowPointer<Keyboard>* keyboard = WindowPointerController::GetValue<Keyboard>(window, "Keyboard");
		if (keyboard == nullptr) {
			return;
		}

		if (keyboard->GetValue().GetKey().action == 2) {
			keyboard->GetValue().SetKey(KeyboardKey(key, action, action >= GLFW_PRESS));
			return;
		}

		if (!action) {
			return;
		}

		keyboard->GetValue().SetKey(KeyboardKey(key, action, action >= GLFW_PRESS));
	});
}

Keyboard::Keyboard(GLFWwindow* window, GLFWkeyfun handler)
{
	this->window = window;
	HookOnKeyPress(handler);
}

void Keyboard::Update()
{
	if (key.action == 2) {
		return;
	}

	key.pressed = false;
	key.action = 0;
	key.clamping = 0;
}

void Keyboard::HookOnKeyPress(GLFWkeyfun handler)
{
	glfwSetKeyCallback(window, handler);
}

void Keyboard::SetKey(KeyboardKey key)
{
	this->key = key;
}

KeyboardKey Keyboard::GetKey()
{
	return key;
}
