#pragma once
#include "IFigure.h"

class Triangle
    : public IFigure
{
    Window* window;

    MouseHoverHandler OnMouseHover;
    MouseHoverHandler OnMouseOver;

    MouseClickHandler OnMouseClick;

    Coord vertex1;
    Coord vertex2;
    Coord vertex3;

    Coord pos;

    Size size;

    Color color;
    Color baseColor;

    Shader* shader;

    char* title;

    bool MouseInTriangle(Mouse& mouse);
public:
    Triangle();
    Triangle(const char* title, Window& window, Coord pos, Size size, Color color = Color(0, 0, 0));
    Triangle(const char* title, Window& window, Coord vertex1, Coord vertex2, Coord vertex3, Color color = Color(0, 0, 0));

    void Draw();

    Coord GetPos();
    Size GetSize();

    bool MouseHover(Mouse& mouse);
    bool MouseClick(Mouse& mouse);

    Window GetWindow();

    void SetColor(Color color);
    Color GetColor();

    Color GetBaseColor();

    std::vector<Coord> GetVertices();

    const char* GetTitle();

    void SetShader(Shader* shader);

    Shader* GetShader();

    const bool IsMouseOverlap();

    void HookMouseHover(MouseHoverHandler handler);
    void HookMouseOver(MouseHoverHandler handler);

    void HookMouseClick(MouseClickHandler handler);

    Triangle& operator=(const Triangle& other);
};

