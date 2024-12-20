#pragma once

#include <iostream>
#include <string>

#include "Rect.h"
#include "Cell.h"

#include "SpriteAnimation.h"
#include "AudioController.h"
#include "WindowPointerController.h"

#include "functions.h"

#define ROWS_DEFAULT 30;
#define COLS_DEFAULT 30;

#define MINES_DEFAULT 20;

const Color EmptyColor = Color(0.63f, 0.83f, 0.45f, 0);

class GameField
{
	Window* window;
	std::pair<Rect, Cell<char>>** field;

	SpriteAnimation explosion;

	int row, col;
	int mines;

	bool gameOver;
	bool win;

	float alpha;

	void GenerateField();
	void RevealCell(std::pair<Rect, Cell<char>>& cell);

	std::pair<Rect, Cell<char>>& GetPairByCoord(int x, int y);

	void CheckWin();

	void End();

	void Restart();
public:
	GameField();
	GameField(Window& window, int row, int col, int mines);

	void Draw();

	bool IsOver();
	bool IsWin();
};
