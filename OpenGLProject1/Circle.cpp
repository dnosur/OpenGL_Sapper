#include "Circle.h"

bool Circle::MouseInCircle(Mouse& mouse)
{
    float normMouseX = (mouse.GetMouseCoord().X / window->GetSize().GetWidth()) * 2.0f - 1.0f;
    float normMouseY = 1.0f - (mouse.GetMouseCoord().Y / window->GetSize().GetHeight()) * 2.0f;

    float centerX = window->PixelToGLX(pos.X);
    float centerY = window->PixelToGLY(pos.Y);

    float distX = normMouseX - centerX;
    float distY = normMouseY - centerY;
    float distanceSquared = distX * distX + distY * distY;

    return distanceSquared <= (r * r);
}

void Circle::MathHeights()
{
    float centerX = window->PixelToGLX(pos.X);
    float centerY = window->PixelToGLY(pos.Y);

    for (int i = 0; i <= numSegments; i++) {
        float theta = 2.0f * M_PI * float(i) / float(numSegments); 
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        vertexes.push_back(Coord(x + centerX, y + centerY));
    }
}

Circle::Circle()
{
    title = (char*)"Undefined";
    window = NULL;

    r = numSegments = -1;

    OnMouseHover = OnMouseOver = nullptr;
    OnMouseClick = nullptr;
}

Circle::Circle(const char* title, Window& window, Coord pos, int numSegments, float r, Color color)
{
	copyStr(title, this->title);

	this->window = &window;
	this->pos = pos;
	this->numSegments = numSegments;
	this->color = baseColor = color;

    float scaleX = 2.0f / window.GetSize().width;
    float scaleY = 2.0f / window.GetSize().height;

    float scale = (scaleX < scaleY) ? scaleX : scaleY;

    this->r = r * scale;

    MathHeights();

	OnMouseHover = OnMouseOver = nullptr;
	OnMouseClick = nullptr;
}

void Circle::Draw()
{
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glBegin(GL_TRIANGLE_FAN);
    glColor4f(color.r, color.g, color.b, color.a);

	for (const Coord& vertex : vertexes) {
		glVertex2f(vertex.X, vertex.Y);
	}

    glEnd();
    glPopAttrib();
}

bool Circle::MouseHover(Mouse& mouse)
{
    if (mouse.IsEqual()) {
        return false;
    }

    const bool isHover = MouseInCircle(mouse);

    //std::cout << "X: " << mouse.GetMouseCoord().X << " Y: " << mouse.GetMouseCoord().Y << " " << "isHover: " << isHover << std::endl;

    if (isHover && OnMouseHover) {
        OnMouseHover(this, window->GetWindow());
    }

    if (!isHover && OnMouseOver) {
        OnMouseOver(this, window->GetWindow());
    }

    return isHover;
}

bool Circle::MouseClick(Mouse& mouse)
{
    if (!mouse.isClick() || !MouseInCircle(mouse)) {
        return false;
    }

    OnMouseClick(this, window->GetWindow());
    return true;
}

std::vector<Coord> Circle::GetVertices()
{
    return std::vector<Coord>();
}

void Circle::SetTitle(const char* title)
{
	copyStr(title, this->title);
}

void Circle::SetColor(Color color)
{
	this->color = color;
}

Color Circle::GetColor()
{
    return color;
}

Color Circle::GetBaseColor()
{
    return baseColor;
}

Size Circle::GetSize()
{
    return size;
}

Coord Circle::GetPos()
{
    return pos;
}

const char* Circle::GetTitle()
{
    return title;
}

void Circle::SetShader(Shader* shader)
{
    if (this->shader == nullptr) {
        delete this->shader;
    }

    if (shader == nullptr) {
        return;
    }

	this->shader = shader;
}

Shader* Circle::GetShader()
{
	return shader;
}

Window Circle::GetWindow()
{
    return *window;
}

const bool Circle::IsMouseOverlap()
{
    return MouseInCircle(window->GetMouse());
}

void Circle::HookMouseHover(MouseHoverHandler OnMouseHover)
{
	this->OnMouseHover = OnMouseHover;
}

void Circle::HookMouseOver(MouseHoverHandler OnMouseOver)
{
	this->OnMouseOver = OnMouseOver;
}

void Circle::HookMouseClick(MouseClickHandler OnMouseClick)
{
	this->OnMouseClick = OnMouseClick;
}