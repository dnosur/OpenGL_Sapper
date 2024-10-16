#pragma once
#include <GL/glut.h>
#include <gl/glut.h>

#include <windows.h>
#include <string>
#include <conio.h>

#include <map>

#include "Coord.h"
#include "Color.h"
#include "Size.h"

void clear();
void pause();

void gotoxy(int X, int Y);
void gotoxy(COORD coord);

void DrawSymbol(Coord coord, char symbol, Size windowSize, const Color color = Color(1, 0, 0));
void DrawSymbols(Coord coord, char* symbols, Size windowSize, const Color color = Color(1, 0, 0));

void copyStr(char* origin, char*& destination);
void copyStr(const char* origin, char*& destination);

COORD getxy();
void getxy(int& x, int& y);