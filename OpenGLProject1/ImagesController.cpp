#include "ImagesController.h"

int ImagesController::GetIndexByTitle(char* title)
{
    int index = 0;
    for (Image& img : images) {
        if (!strcmp(title, img.title)) {
            return index;
        }
        index++;
    }

    return -1;
}

void ImagesController::ChangeIfExist(Image image)
{
    const int index = GetIndexByTitle(image.title);
    if (index < 0) {
        images.push_back(image);
        return;
    }

    images[index] = image;
}

void ImagesController::Draw(Image& item, Coord& position, Color& color, Size& windowSize, Size& size, bool reverse)
{
    const GLuint image = item.image;

    float normX = (position.X / (float)windowSize.GetWidth()) * 2.0f - 1.0f;
    float normY = !reverse 
        ? (position.Y / (float)windowSize.GetHeight()) * 2.0f - 1.0f 
        : 1.0f - (position.Y / (float)windowSize.GetHeight()) * 2.0f;
    float normW = (size.width / (float)windowSize.GetWidth()) * 2.0f;
    float normH = (size.height / (float)windowSize.GetHeight()) * 2.0f;

    // Вершины и текстурные координаты
    float vertices[] = {
        // Позиции           // Текстурные координаты
        normX, normY, 0.0f,         0.0f, 0.0f,  // Левый нижний угол
        normX + normW, normY, 0.0f, 1.0f, 0.0f,  // Правый нижний угол
        normX + normW, normY + normH, 0.0f, 1.0f, 1.0f,  // Правый верхний угол
        normX, normY + normH, 0.0f, 0.0f, 1.0f   // Левый верхний угол
    };

    unsigned int indices[] = {
        0, 1, 2, // Первый треугольник
        2, 3, 0  // Второй треугольник
    };

    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, image);

    item.shader->Use();
    item.shader->SetInt("ourTexture", 0);
    item.shader->SetVec4("ourColor", color.r, color.g, color.b, color.a);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);

    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    glUseProgram(0);
}

void ImagesController::Load(const char* path, const char* title, Shader* shader)
{
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);

    unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
    if (data) {
        GLenum format;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
            format = GL_RGBA;

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
        return;
    }

    if (shader == nullptr) {
        shader = new Shader(
            title,
            "shaders/Image/imageVertex.vs",
            "shaders/Image/imageFragment.frag"
        );
    }

    stbi_image_free(data); 

    ChangeIfExist(Image(title, path, textureID, shader));
}

void ImagesController::LoadAndDrawImage(const char* path, const char* title, Shader* shader, Coord position, Size size, Size windowSize)
{
    int width, height, nrChannels;
    unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);

    if (!data) {
        std::cerr << "Failed to load image: " << path << std::endl;
        return;
    }

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    GLenum format = GL_RGB;
    if (nrChannels == 1)
        format = GL_RED;
    else if (nrChannels == 3)
        format = GL_RGB;
    else if (nrChannels == 4)
        format = GL_RGBA;

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);


    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glad_glOrtho(0, windowSize.GetWidth(), windowSize.GetHeight(), 0, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    shader->Use();
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(position.X, position.Y); // Левый нижний угол
    glTexCoord2f(1.0f, 0.0f); glVertex2f(position.X + size.width, position.Y); // Правый нижний угол
    glTexCoord2f(1.0f, 1.0f); glVertex2f(position.X + size.width, position.Y + size.height); // Правый верхний угол
    glTexCoord2f(0.0f, 1.0f); glVertex2f(position.X, position.Y + size.height); // Левый верхний угол
    glEnd();


    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glDisable(GL_TEXTURE_2D);

    ChangeIfExist(Image(title, path, texture, shader));
}

void ImagesController::DrawImage(const char* title, Coord position, Size size, Size windowSize, Color color, bool reverse)
{
    const int index = GetIndexByTitle((char*)title);
    Draw(images[index], position, color, windowSize, size, reverse);
}

Image ImagesController::GetImageByTitle(const char* title)
{
    const int index = GetIndexByTitle((char*)title);
    if (index < 0) {
        return Image();
    }
    return images[index];
}

std::vector<Image> ImagesController::GetImages()
{
    return images;
}

void ImagesController::SetImages(std::vector<Image> images)
{
    Clear();
    for (const Image& image : images) {
        this->images.push_back(image);
    }
}

int ImagesController::GetSize()
{
    return images.size();
}

void ImagesController::Clear()
{
    if (!images.size()) {
        return;
    }
    images.clear();
}
