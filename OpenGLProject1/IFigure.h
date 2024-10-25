#pragma once
#include "Window.h"

__interface IFigure;

typedef void(__stdcall* MouseHoverHandler)(IFigure* figure, GLFWwindow* window);
typedef void(__stdcall* MouseClickHandler)(IFigure* figure, GLFWwindow* window);

__interface IFigure
{
	void Draw();

	bool MouseHover(Mouse& mouse);
	Window GetWindow();

	Coord GetPos();
	std::vector<Coord> GetVertices();

	void SetColor(Color color);
	Color GetColor();

	Color GetBaseColor();

	Size GetSize();

	void SetShader(Shader* shader);

	Shader* GetShader();

	const char* GetTitle();

	const bool IsMouseOverlap();

	void HookMouseHover(MouseHoverHandler handler);
	void HookMouseOver(MouseHoverHandler handler);

	void HookMouseClick(MouseClickHandler handler);
};