#pragma once
#include "IFigure.h"
class Rect :
    public IFigure
{
    Window* window;

    MouseHoverHandler OnMouseHover;
    MouseHoverHandler OnMouseOver;

    MouseClickHandler OnMouseClick;

    Coord vertex1;
    Coord vertex2;

    Coord pos;

    Size size;

    Color color;
    Color baseColor;

    char* title;

    bool MouseInRect(Mouse& mouse);
public:
    Rect();
    Rect(const char* title, Window& window, Coord pos, Size size, Color color = Color(0, 0, 0));
    Rect(const char* title, Window& window, Coord vertex1, Coord vertex2, Color color = Color(0, 0, 0));

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

    void HookMouseHover(MouseHoverHandler handler);
    void HookMouseOver(MouseHoverHandler handler);

    void HookMouseClick(MouseClickHandler handler);

    Rect& operator=(const Rect& other);
};

