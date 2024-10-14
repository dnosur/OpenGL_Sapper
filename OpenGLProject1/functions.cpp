#include "functions.h"

void clear() {
	system("cls");
}

void pause() {
	_getch();
}

void gotoxy(int X, int Y)
{
	COORD coord = { X, Y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void gotoxy(COORD coord)
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void DrawSymbol(Coord coord, char symbol, Size windowSize, const Color color)
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, windowSize.GetWidth(), windowSize.GetHeight(), 0);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glColor3f(color.r, color.g, color.b);

	glRasterPos2f(coord.X, coord.Y);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, symbol);

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void DrawSymbols(Coord coord, char* symbols, Size windowSize, const Color color)
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, windowSize.GetWidth(), windowSize.GetHeight(), 0);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glColor3f(color.r, color.g, color.b);

	glRasterPos2f(coord.X, coord.Y);


	while (*symbols) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *symbols);
		symbols++;
	}

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void getxy(int& x, int& y) {
	CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
	HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!GetConsoleScreenBufferInfo(hStd, &screenBufferInfo))
		printf("GetConsoleScreenBufferInfo (%d)\n", GetLastError());

	x = screenBufferInfo.dwCursorPosition.X;
	y = screenBufferInfo.dwCursorPosition.Y;
}

COORD getxy() {
	CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
	HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!GetConsoleScreenBufferInfo(hStd, &screenBufferInfo))
		printf("GetConsoleScreenBufferInfo (%d)\n", GetLastError());

	return screenBufferInfo.dwCursorPosition;
}