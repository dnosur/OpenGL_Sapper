#include "Triangle.h"

bool Triangle::MouseInTriangle(Mouse& mouse)
{
    float normMouseX = (mouse.GetMouseCoord().X / window->GetSize().GetWidth()) * 2.0f - 1.0f;
    float normMouseY = 1.0f - (mouse.GetMouseCoord().Y / window->GetSize().GetHeight()) * 2.0f;

    auto Area = [](Coord v1, Coord v2, Coord v3) {
        return std::abs((v1.X * (v2.Y - v3.Y) + v2.X * (v3.Y - v1.Y) + v3.X * (v1.Y - v2.Y)) / 2.0f);
    };

    Coord mousePos(normMouseX, normMouseY);

    float totalArea = Area(vertex1, vertex2, vertex3);

    float area1 = Area(mousePos, vertex2, vertex3);
    float area2 = Area(vertex1, mousePos, vertex3);
    float area3 = Area(vertex1, vertex2, mousePos);

    return std::abs(totalArea - (area1 + area2 + area3)) < 0.001f;
}

Triangle::Triangle()
{
    title = (char*)"Undefined";
    window = NULL;

    OnMouseHover = OnMouseOver = nullptr;
    OnMouseClick = nullptr;
}

Triangle::Triangle(const char* title, Window& window, Coord pos, Size size, Color color)
{
    copyStr(title, this->title);

    this->window = &window;
    this->pos = pos;
    this->size = size;
    this->color = baseColor = color;

    float glCenterX = window.PixelToGLX(pos.X);
    float glCenterY = window.PixelToGLY(pos.Y);

    float glWidth = (float)size.GetWidth() / (float)window.GetSize().GetWidth() * 2.0f;
    float glHeight = (float)size.GetHeight() / (float)window.GetSize().GetHeight() * 2.0f;

    vertex1.X = glCenterX;
    vertex1.Y = glCenterY + (glHeight / 2.0f);

    vertex2.X = glCenterX - (glWidth / 2.0f);
    vertex2.Y = glCenterY - (glHeight / 2.0f);

    vertex3.X = glCenterX + (glWidth / 2.0f);
    vertex3.Y = glCenterY - (glHeight / 2.0f);

    OnMouseHover = OnMouseOver = nullptr;
    OnMouseClick = nullptr;
}

Triangle::Triangle(const char* title, Window& window, Coord vertex1, Coord vertex2, Coord vertex3, Color color)
{
    copyStr(title, this->title);

    this->window = &window;
    this->vertex1 = vertex1;
    this->vertex2 = vertex2;
    this->vertex3 = vertex3;
    this->color = baseColor = color;

    float centerX_GL = (vertex1.X + vertex2.X + vertex3.X) / 3.0f;
    float centerY_GL = (vertex1.Y + vertex2.Y + vertex3.Y) / 3.0f;

    pos = Coord(
        ((centerX_GL + 1.0f) / 2.0f) * (float)window.GetSize().GetWidth(),
        ((1.0f - (centerY_GL + 1.0f) / 2.0f) * (float)window.GetSize().GetHeight())
    );

    OnMouseHover = OnMouseOver = nullptr;
    OnMouseClick = nullptr;
}

void Triangle::Draw()
{
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glBegin(GL_TRIANGLES);
    glColor4f(color.r, color.g, color.b, color.a);
    glVertex2f(vertex1.X, vertex1.Y);
    glVertex2f(vertex2.X, vertex2.Y);
    glVertex2f(vertex3.X, vertex3.Y);
    glEnd();
    glPopAttrib();
}

Coord Triangle::GetPos()
{
    return pos;
}

Size Triangle::GetSize()
{
    return size;
}

bool Triangle::MouseHover(Mouse& mouse)
{
    if (mouse.IsEqual()) {
        return false;
    }

    const bool isHover = MouseInTriangle(mouse);

    //std::cout << "X: " << mouse.GetMouseCoord().X << " Y: " << mouse.GetMouseCoord().Y << " " << "isHover: " << isHover << std::endl;

    if (isHover && OnMouseHover) {
        OnMouseHover(this, window->GetWindow());
    }

    if (!isHover && OnMouseOver) {
        OnMouseOver(this, window->GetWindow());
    }

    return isHover;
}

bool Triangle::MouseClick(Mouse& mouse)
{
    if (!mouse.isClick() || !MouseInTriangle(mouse)) {
        return false;
    }

    OnMouseClick(this, window->GetWindow());
    return true;
}

Window Triangle::GetWindow()
{
    return *window;
}

void Triangle::SetColor(Color color)
{
	this->color = color;
}

Color Triangle::GetColor()
{
    return color;
}

Color Triangle::GetBaseColor()
{
    return baseColor;
}

std::vector<Coord> Triangle::GetVertices()
{
    return { vertex1, vertex2, vertex3 };
}

const char* Triangle::GetTitle()
{
    return title;
}

const bool Triangle::IsMouseOverlap()
{
    return MouseInTriangle(window->GetMouse());
}

void Triangle::HookMouseHover(MouseHoverHandler handler)
{
	OnMouseHover = handler;
}

void Triangle::HookMouseOver(MouseHoverHandler handler)
{
	OnMouseOver = handler;
}

void Triangle::HookMouseClick(MouseClickHandler handler)
{
	OnMouseClick = handler;
}

Triangle& Triangle::operator=(const Triangle& other)
{
	if (this == &other)
		return *this;

	copyStr(other.title, this->title);

	this->window = other.window;
	this->pos = other.pos;
	this->size = other.size;
	this->color = other.color;
	this->baseColor = other.baseColor;

	this->vertex1 = other.vertex1;
	this->vertex2 = other.vertex2;
	this->vertex3 = other.vertex3;

	this->OnMouseHover = other.OnMouseHover;
	this->OnMouseOver = other.OnMouseOver;
	this->OnMouseClick = other.OnMouseClick;

	return *this;
}