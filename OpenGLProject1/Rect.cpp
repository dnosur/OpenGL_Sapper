#include "Rect.h"

bool Rect::MouseInRect(Mouse& mouse)
{
    float normMouseX = (mouse.GetMouseCoord().X / window->GetSize().GetWidth()) * 2.0f - 1.0f;
    float normMouseY = 1.0f - (mouse.GetMouseCoord().Y / window->GetSize().GetHeight()) * 2.0f;

    return (normMouseX >= vertex1.X && normMouseX <= vertex2.X &&
        normMouseY >= vertex1.Y && normMouseY <= vertex2.Y);
}

Rect::Rect()
{
    title = (char*)"Undefined";
    window = NULL;

    OnMouseHover = OnMouseOver = nullptr;
    OnMouseClick = nullptr;
}

Rect::Rect(const char* title, Window& window, Coord pos, Size size, Color color)
{
    this->title = new char[strlen(title) + 1];
    strcpy_s(this->title, strlen(title) + 1, title);

    this->window = &window;
    this->pos = pos;
    this->size = size;
    this->color = baseColor = color;

    float glCenterX = window.PixelToGLX(pos.X);
    float glCenterY = window.PixelToGLY(pos.Y);

    float glWidth = (float)(size.GetWidth()) / (float)window.GetSize().GetWidth() * 2.0f;
    float glHeight = (float)size.GetHeight() / (float)window.GetSize().GetHeight() * 2.0f;

    float halfWidth = glWidth / 2.0f;
    float halfHeight = glHeight / 2.0f;

    vertex1.X = glCenterX - halfWidth;
    vertex1.Y = glCenterY - halfHeight;
    vertex2.X = glCenterX + halfWidth;
    vertex2.Y = glCenterY + halfHeight;

    OnMouseHover = OnMouseOver = nullptr;
    OnMouseClick = nullptr;
}

Rect::Rect(const char* title, Window& window, Coord vertex1, Coord vertex2, Color color)
{
    this->title = new char[strlen(title) + 1];
    strcpy_s(this->title, strlen(title) + 1, title);

    this->window = &window;
	this->vertex1 = vertex1;
	this->vertex2 = vertex2;
    this->color = baseColor = color;

    size = Size(vertex2.X - vertex1.X, vertex2.Y - vertex1.Y);
    
    float centerX_GL = float(vertex1.X + vertex2.X) / 2.0f;
    float centerY_GL = float(vertex1.Y + vertex2.Y) / 2.0f;

    pos = Coord(((centerX_GL + 1.0f) / 2.0f) * (float)window.GetSize().GetWidth(),
        ((1.0f - (centerY_GL + 1.0f) / 2.0f) * (float)window.GetSize().GetHeight()));

    OnMouseHover = OnMouseOver = nullptr;
    OnMouseClick = nullptr;
}

void Rect::Draw()
{
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glBegin(GL_QUADS);
    glColor3f(color.r, color.g, color.b);
    glVertex2f(vertex1.X, vertex1.Y);
    glVertex2f(vertex2.X, vertex1.Y);
    glVertex2f(vertex2.X, vertex2.Y);
    glVertex2f(vertex1.X, vertex2.Y);
    glEnd();
    glPopAttrib();
}

Coord Rect::GetPos()
{
    return pos;
}

Size Rect::GetSize()
{
    return size;
}

bool Rect::MouseHover(Mouse& mouse)
{
    if (mouse.IsEqual()) {
        return false;
    }

    const bool isHover = MouseInRect(mouse);

    if (isHover && OnMouseHover) {
        OnMouseHover(this, window->GetWindow());
    }

    if (!isHover && OnMouseOver) {
        OnMouseOver(this, window->GetWindow());
    }

    return isHover;
}

bool Rect::MouseClick(Mouse& mouse)
{
    if (!mouse.isClick() || !MouseInRect(mouse)) {
        return false;
    }

    OnMouseClick(this, window->GetWindow());
    return true;
}

Window Rect::GetWindow()
{
    return Window();
}

void Rect::SetColor(Color color)
{
    this->color = color;
}

Color Rect::GetColor()
{
    return color;
}

Color Rect::GetBaseColor()
{
    return baseColor;
}

std::vector<Coord> Rect::GetVertices()
{
    return std::vector<Coord>();
}

const char* Rect::GetTitle()
{
    return title;
}

const bool Rect::IsMouseOverlap()
{
    return MouseInRect(window->GetMouse());
}

void Rect::HookMouseHover(MouseHoverHandler handler)
{
    OnMouseHover = handler;
}

void Rect::HookMouseOver(MouseHoverHandler handler)
{
    OnMouseOver = handler;
}

void Rect::HookMouseClick(MouseClickHandler handler)
{
    OnMouseClick = handler;
}

Rect& Rect::operator=(const Rect& other)
{
    if (this == &other) {
        return *this;
    }

    this->window = other.window;
    this->pos = other.pos;

    this->vertex1 = other.vertex1;
    this->vertex2 = other.vertex2;

    this->size = other.size;

    this->color = other.color;
    this->baseColor = other.baseColor;

    this->OnMouseHover = other.OnMouseHover;
    this->OnMouseOver = other.OnMouseOver;

    this->title = new char[strlen(other.title) + 1];
    strcpy_s(this->title, strlen(other.title) + 1, other.title);

    return *this;
}
