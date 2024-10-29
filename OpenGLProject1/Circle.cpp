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
    if (!vertexes.empty()) {
        vertexes.clear();
    }

    float centerX = window->PixelToGLX(pos.X);
    float centerY = window->PixelToGLY(pos.Y);

    vertexes.push_back(centerX);
    vertexes.push_back(centerY);
    vertexes.push_back(0.0f);
    vertexes.push_back(color.r);
    vertexes.push_back(color.g);
    vertexes.push_back(color.b);
    vertexes.push_back(color.a);

    for (int i = 0; i <= numSegments; ++i) {
        float theta = 2.0f * M_PI * float(i) / float(numSegments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);

        vertexes.push_back(x + centerX);
        vertexes.push_back(y + centerY);
        vertexes.push_back(0.0f);
        vertexes.push_back(color.r);
        vertexes.push_back(color.g);
        vertexes.push_back(color.b);
        vertexes.push_back(color.a);
    }
}

Circle::Circle()
{
    title = (char*)"Undefined";
    window = NULL;

    r = numSegments = -1;

    OnMouseHover = OnMouseOver = nullptr;
    OnMouseClick = nullptr;

    shader = nullptr;
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

    shader = new Shader(title, "shaders/Figures/vertex.vs", "shaders/Figures/fragment.frag");
}

void Circle::Draw()
{
    glUseProgram(0);
    glPushAttrib(GL_ALL_ATTRIB_BITS);

    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertexes.size() * sizeof(float), vertexes.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0); // Позиции
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float))); // Цвета
    glEnableVertexAttribArray(1);

    shader->Use();
    shader->SetVec4("targetColor", 0, 0, 0, 0);

    glDrawArrays(GL_TRIANGLE_FAN, 0, numSegments + 2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);

    glPopAttrib();
    glUseProgram(0);
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

Circle& Circle::operator=(const Circle& other)
{
    if (this == &other) {
        return *this;
    }

    baseColor = other.baseColor;
    color = other.color;
    numSegments = other.numSegments;

    OnMouseClick = other.OnMouseClick;
    OnMouseHover = other.OnMouseHover;
    OnMouseOver = other.OnMouseOver;

    vertexes = other.vertexes;

    r = other.r;

    pos = other.pos;
    size = other.size;

    copyStr(other.title, title);

    shader = other.shader;

    return *this;
}
