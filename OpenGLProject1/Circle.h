#pragma once

#include <corecrt_math_defines.h>
#include <iostream>
#include "IFigure.h"

class Circle : public IFigure
{
    Window* window;

    MouseHoverHandler OnMouseHover;
    MouseHoverHandler OnMouseOver;

    MouseClickHandler OnMouseClick;

    std::vector<Coord> vertexes;
    int numSegments;
    float r;

    Coord pos;

    Size size;

    Color color;
    Color baseColor;

    Shader* shader;

    char* title;

    bool MouseInCircle(Mouse& mouse);

    void MathHeights();
public:

    Circle();
	Circle(const char* title, Window& window, Coord pos, int numSegments, float r, Color color);

	void Draw();
	bool MouseHover(Mouse& mouse);
	bool MouseClick(Mouse& mouse);

    std::vector<Coord> GetVertices();

	void SetTitle(const char* title);
	void SetColor(Color color);
    Color GetColor();

    Color GetBaseColor();

    Size GetSize();

    Coord GetPos();

    const char* GetTitle();

    void SetShader(Shader* shader);

    Shader* GetShader();

    Window GetWindow();

    const bool IsMouseOverlap();

    void HookMouseHover(MouseHoverHandler OnMouseHover);
    void HookMouseOver(MouseHoverHandler OnMouseOver);
    void HookMouseClick(MouseClickHandler OnMouseClick);
};