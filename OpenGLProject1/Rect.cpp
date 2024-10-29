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

    shader = nullptr;
}

Rect::Rect(const char* title, Window& window, Coord pos, Size size, Color color)
{
    copyStr(title, this->title);

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

    shader = new Shader(title, "shaders/Figures/vertex.vs", "shaders/Figures/fragment.frag");
}

Rect::Rect(const char* title, Window& window, Coord vertex1, Coord vertex2, Color color)
{
    copyStr(title, this->title);

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

    shader = new Shader(title, "shaders/Figures/vertex.vs", "shaders/Figures/fragment.frag");
}

void Rect::Draw()
{
    glUseProgram(0);
    glPushAttrib(GL_ALL_ATTRIB_BITS);

    float vertices[] = {
        // positions         // colors
         vertex1.X, vertex1.Y, 0.0f,  color.r, color.g, color.b, color.a,
         vertex2.X, vertex1.Y, 0.0f,  color.r, color.g, color.b, color.a,
         vertex2.X, vertex2.Y, 0.0f,  color.r, color.g, color.b, color.a,
		 vertex1.X, vertex2.Y, 0.0f,  color.r, color.g, color.b, color.a
    };

    unsigned int VBO, VAO;

    glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// color attribute
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

    shader->Use();
    shader->SetInt("targetIndex", -1);

	glDrawArrays(GL_QUADS, 0, 4);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
    glPopAttrib();
    glUseProgram(0);
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
    return { vertex1, vertex2 };
}

void Rect::SetShader(Shader* shader)
{
    if (this->shader == nullptr) {
        delete this->shader;
    }

    if (shader == nullptr) {
        return;
    }

	this->shader = shader;
}

Shader* Rect::GetShader()
{
    return shader;
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
    this->OnMouseClick = other.OnMouseClick;

    this->shader = other.shader;

    copyStr(other.title, this->title);

    return *this;
}
