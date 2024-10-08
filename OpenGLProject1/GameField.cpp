#include "GameField.h"

void GameField::GenerateField()
{
	field = new std::pair<Rect, Cell<char>>*[row];


	for (int i = 0; i < row; i++) {
		field[i] = new std::pair<Rect, Cell<char>>[col];
		for (int j = 0; j < col; j++) {
			std::string title = "Rect" + std::to_string(i) + std::to_string(j);
			field[i][j] = {
				Rect(title.c_str(), *window, Coord(35 * (j + 1), 35 * (i + 1)), Size(30, 30)),
				Cell<char>(Coord(j, i), '.')
			};

			field[i][j].first.HookMouseHover([](IFigure* figure) {
				figure->SetColor(Color(0, 1, 0, 0));
				//std::cout << figure->GetTitle() << " Mouse Hover!\n";
			});

			field[i][j].first.HookMouseOver([](IFigure* figure) {
				figure->SetColor(figure->GetBaseColor());
				//std::cout << figure->GetTitle() << " Mouse Over!\n";
			});

			field[i][j].first.HookMouseClick([](IFigure* figure, GLFWwindow* window) {
				std::pair<Rect, Cell<char>>** field = static_cast<std::pair<Rect, Cell<char>>**>(glfwGetWindowUserPointer(window));
				auto first = field[0][0];
				std::cout << figure->GetTitle() << " Click!\n";
			});
		}
	}

	glfwSetWindowUserPointer(window->GetWindow(), &field);
	std::pair<Rect, Cell<char>>** field = static_cast<std::pair<Rect, Cell<char>>**>(glfwGetWindowUserPointer(window->GetWindow()));

	std::cout << std::endl;

	int placedMines = 0;
	while (placedMines < mines)
	{
		std::pair<Rect, Cell<char>>& element = GetPairByCoord(rand() % col, rand() % row);

		if (element.second.value != '*')
		{
			element.second.value = '*';
			placedMines++;
		}
	}

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			std::pair<Rect, Cell<char>>& element = GetPairByCoord(j, i);
			if (element.second.value == '*') {
				continue;
			}

			int mineCount = 0;
			for (int x = -1; x <= 1; x++)
			{
				for (int y = -1; y <= 1; y++)
				{
					int newRow = i + x;
					int newCol = j + y;
					if (newRow >= 0 && newRow < row &&
						newCol >= 0 && newCol < col &&
						GetPairByCoord(newCol, newRow).second.value == '*'
					){
						mineCount++;
					}
				}
			}

			if (!mineCount) {
				GetPairByCoord(j, i).second.value = '.';
				continue;
			}

			char value = mineCount + '0';
			GetPairByCoord(j, i).second.value = value;
		}
	}
}

std::pair<Rect, Cell<char>>& GameField::GetPairByCoord(int x, int y)
{
	return field[y][x];
}

GameField::GameField()
{
	this->row = ROWS_DEFAULT;
	this->col = COLS_DEFAULT;
	this->mines = MINES_DEFAULT;

	window = NULL;
}

GameField::GameField(Window& window, int row, int col, int mines)
{
	this->row = row;
	this->col = col;
	this->mines = mines;

	this->window = &window;

	GenerateField();
}

void GameField::Draw()
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			std::pair<Rect, Cell<char>>& element = GetPairByCoord(j, i);
			element.first.MouseHover(window->GetMouse());
			element.first.MouseClick(window->GetMouse());
			element.first.Draw();
		}
	}
}
