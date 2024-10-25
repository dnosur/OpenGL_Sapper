#include "GameField.h"

void GameField::GenerateField()
{
	if (field != nullptr) {
		delete[] field;
	};

	field = new std::pair<Rect, Cell<char>>*[row];

	for (int i = 0; i < row; i++) {
		field[i] = new std::pair<Rect, Cell<char>>[col];
		for (int j = 0; j < col; j++) {
			std::string title = "Rect" + std::to_string(i) + std::to_string(j);
			field[i][j] = {
				Rect(title.c_str(), *window, Coord(35 * (j + 1), 35 * (i + 1)), Size(30, 30)),
				Cell<char>(Coord(j, i), '.')
			};

			WindowPointerController::SetPointer(window->GetWindow(), WindowPointer<Cell<char>>(title.c_str(), &field[i][j].second));

			field[i][j].first.HookMouseHover([](IFigure* figure, GLFWwindow* window) {
				WindowPointer<Cell<char>>* cell = WindowPointerController::GetValue<Cell<char>>(window, figure->GetTitle());
				if (cell->GetValue().revealed && cell->GetValue().value == '*') {
					figure->SetColor(Color(1, 0, 0));
					return;
				}

				figure->SetColor(Color(0, 1, 0));
				//std::cout << figure->GetTitle() << " Mouse Hover!\n";
			});

			field[i][j].first.HookMouseOver([](IFigure* figure, GLFWwindow* window) {
				WindowPointer<Cell<char>>* cell = WindowPointerController::GetValue<Cell<char>>(window, figure->GetTitle());
				if (cell->GetValue().revealed && cell->GetValue().value == '*') {
					figure->SetColor(Color(1, 0, 0));
					return;
				}

				figure->SetColor(figure->GetBaseColor());
				//std::cout << figure->GetTitle() << " Mouse Over!\n";
			});

			field[i][j].first.HookMouseClick([](IFigure* figure, GLFWwindow* window) {
				WindowPointer<Cell<char>>* cell = WindowPointerController::GetValue<Cell<char>>(window, figure->GetTitle());
				if (cell->GetValue().revealed) {
					return;
				}

				WindowPointer<AudioController>* audioController = WindowPointerController::GetValue<AudioController>(window, "audioController");
				std::cout << figure->GetTitle() << " X: " << cell->GetValue().coord.X << " Y: " << cell->GetValue().coord.Y << " Value: " << cell->GetValue().value << "\n";
			

				if (cell->GetValue().value == '*') {
					figure->SetColor(Color(1, 0, 0, 0));
					audioController->GetValue().Play("fail");
					return;
				}

				audioController->GetValue().Play("diggin");

				figure->SetColor(EmptyColor);
			});
		}
	}

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

void GameField::RevealCell(std::pair<Rect, Cell<char>>& cell)
{
	if (cell.second.coord.X < 0 || cell.second.coord.X >= col ||
		cell.second.coord.Y < 0 || cell.second.coord.Y >= row ||
		cell.second.revealed) {
		return;
	}

	cell.second.revealed = true;

	if (cell.second.value != '.' && cell.second.value != '0')
	{
		return;
	}

	for (int dx = -1; dx <= 1; dx++)
	{
		for (int dy = -1; dy <= 1; dy++)
		{
			if (bool(dx != 0 || dy != 0) &&
				cell.second.coord.X + dy < col && cell.second.coord.Y + dy < row && 
				cell.second.coord.X + dy < col >= 0 && cell.second.coord.Y + dy >= 0
			)
			{
				RevealCell(GetPairByCoord(cell.second.coord.X + dx, cell.second.coord.Y + dy));
			}
		}
	}
}

std::pair<Rect, Cell<char>>& GameField::GetPairByCoord(int x, int y)
{
	return field[y][x];
}

void GameField::CheckWin()
{
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (!field[i][j].second.revealed && field[i][j].second.value != '*') {
				win = false;
				return;
			}
		}
	}
	WindowPointer<AudioController>* audioController = WindowPointerController::GetValue<AudioController>(window->GetWindow(), "audioController");
	audioController->GetValue().Play("won");

	win = true;
	gameOver = true;
}

void GameField::End()
{
	char* str = (char*)(win ? "Win! :)" : "Lose :(");
	DrawSymbols(
		Coord(800, 100),
		str,
		window->GetSize(),
		win
		? Color(0, 1, 0)
		: Color(1, 0, 0)
	);

	DrawSymbols(
		Coord(800, 200),
		(char*)"Press R to restart",
		window->GetSize(),
		Color(0.9f, 0.8f, 0.1f)
	);

	if (alpha >= .0f) {
		alpha -= 0.005f;
	}

	window->GetImagesController().DrawImage(
		win ? "won" : "fail", 
		Coord(720, 110), Size(500, 600), 
		window->GetSize(), 
		Color(1.0f, 1.0f, 1.0f, alpha)
	);
}

void GameField::Restart()
{
	alpha = 1.0f;
	gameOver = win = false;

	explosion.Restart();
	GenerateField();
}

GameField::GameField()
{
	this->row = ROWS_DEFAULT;
	this->col = COLS_DEFAULT;
	this->mines = MINES_DEFAULT;

	window = NULL;

	field = nullptr;
	gameOver = win = false;
}

GameField::GameField(Window& window, int row, int col, int mines)
{
	this->row = row;
	this->col = col;
	this->mines = mines;

	this->window = &window;

	explosion = SpriteAnimation("explosion", "animations/explosion1", 30, &window, {
		FrameSound(
			1,
			Audio("explosion", "sounds/explosion.wav")
		)
	});

	Restart();
}

void GameField::Draw()
{
	KeyboardKey keyboardKey = window->GetKeyboard().GetKey();

	if (IsOver() && keyboardKey.pressed && keyboardKey.key == GLFW_KEY_R) {
		Restart();
	}

	if (IsOver()) {
		End();
	}

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			std::pair<Rect, Cell<char>>& element = GetPairByCoord(j, i);

			bool revealed = element.second.revealed;
			bool isMouseOverlap = element.first.IsMouseOverlap();

			element.first.MouseHover(window->GetMouse());

			//Установка флага
			if (isMouseOverlap && !revealed && keyboardKey.pressed && keyboardKey.key == GLFW_KEY_F) {
				element.second.marker = !element.second.marker;

				WindowPointer<AudioController>* audioController = WindowPointerController::GetValue<AudioController>(window->GetWindow(), "audioController");

				audioController->GetValue().Play(
					element.second.marker 
					? "set_flag" 
					: "reset_flag"
				);
			}

			//Клик по ячейке
			if (!gameOver && element.first.MouseClick(window->GetMouse())) {
				RevealCell(element);
				CheckWin();
				revealed = true;
			};

			if (revealed) {
				const int newX = element.first.GetPos().X - 18;
				const int newY = element.first.GetPos().Y + 20;

				//Нажали на мину
				if (element.second.value == '*') {
					win = false;
					gameOver = true;
					window->GetImagesController().DrawImage(
						"mine",
						Coord(newX, newY),
						Size(35, 35),
						window->GetSize(),
						Color(1, 0, 0),
						true
					);

					explosion.Play(Coord(newX - 10, newY - 10), Size(50, 50));
					continue;
				}

				if (element.second.value == '.') {
					window->GetImagesController().DrawImage(
						"hole", 
						Coord(newX, newY),
						Size(35, 35),
						window->GetSize(),
						Color(1, 1, 1),
						true
					);
					continue;
				}

				DrawSymbol(
					Coord(
						element.first.GetPos().X - 3,
						element.first.GetPos().Y
					),
					element.second.value,
					window->GetSize(),
					Color(222, 90, 119).ConvertToGl()
				);
				continue;
			}

			//Вывод открытых ячеек
			if (gameOver) {
				const int newX = element.first.GetPos().X - 18;
				const int newY = element.first.GetPos().Y + 20;

				if (element.second.value == '*') {
					window->GetImagesController().DrawImage(
						"mine", 
						Coord(newX, newY), 
						Size(35, 35),
						window->GetSize(),
						Color(1, 1, 1),
						true
					);
					continue;
				}

				if (element.second.value == '.') {
					window->GetImagesController().DrawImage(
						"hole", 
						Coord(newX, newY), 
						Size(35, 35), 
						window->GetSize(),
						Color(0.8f, 0.3f, 0.1f),
						true
					);
					continue;
				}

				DrawSymbol(
					Coord(
						element.first.GetPos().X - 3, 
						element.first.GetPos().Y
					), 
					element.second.value, 
					window->GetSize(),
					Color(217, 219, 65).ConvertToGl()
				);
				continue;
			}

			element.first.Draw();

			if (element.second.marker) {
				const int newX = element.first.GetPos().X - 15;
				const int newY = element.first.GetPos().Y;

				window->GetImagesController().DrawImage(
					"redFlag", 
					Coord(newX, newY), 
					Size(50, 50),
					window->GetSize(),
					Color(1, 1, 1),
					true
				);
				continue;
			}
		}
	}
}

bool GameField::IsOver()
{
	return gameOver;
}

bool GameField::IsWin()
{
	return win;
}
