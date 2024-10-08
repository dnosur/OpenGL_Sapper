#include "Mouse.h"
#include <vector>
#include "Window.h"

__interface IFigure;

typedef void(__stdcall* MouseHoverHandler)(IFigure* figure);
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

	const char* GetTitle();

	void HookMouseHover(MouseHoverHandler handler);
	void HookMouseOver(MouseHoverHandler handler);

	void HookMouseClick(MouseClickHandler handler);
};