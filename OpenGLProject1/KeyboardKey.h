#pragma once
#include "WindowPointerController.h"

struct KeyboardKey
{
	int key;
	int action;

	bool pressed;
	bool clamping;

	bool keyProcessed;

	KeyboardKey();
	KeyboardKey(int key, int action, bool pressed = false);

	bool operator==(const KeyboardKey& other) const;
	bool operator!=(const KeyboardKey& other) const;

	KeyboardKey& operator=(const KeyboardKey& other);
};

