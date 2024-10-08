#pragma once
#include <iostream>
#include <string>

#include "Rect.h"
#include "Cell.h"

#define ROWS_DEFAULT 30;
#define COLS_DEFAULT 30;

#define MINES_DEFAULT 20;

class GameField
{
	Window* window;
	std::pair<Rect, Cell<char>>** field;

	int row, col;
	int mines;

	bool gameOver;
	bool win;

	void GenerateField();

	std::pair<Rect, Cell<char>>& GetPairByCoord(int x, int y);
public:
	GameField();
	GameField(Window& window, int row, int col, int mines);

	void Draw();

	bool IsOver();
	bool IsWin();
};
