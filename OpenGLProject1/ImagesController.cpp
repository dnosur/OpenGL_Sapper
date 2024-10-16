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

void ImagesController::Load(const char* path, const char* title)
{
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    int width, height, nrChannels;
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

    stbi_image_free(data); 

    ChangeIfExist(Image(title, path, textureID));
}

void ImagesController::LoadAndDrawImage(const char* path, const char* title, Coord position, Size size, Size windowSize)
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
    gluOrtho2D(0, windowSize.GetWidth(), windowSize.GetHeight(), 0);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();


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

    ChangeIfExist(Image(title, path, texture));
}

void ImagesController::DrawImage(const char* title, Coord position, Size size, Size windowSize, Color color)
{
    const int index = GetIndexByTitle((char*)title);
    const GLuint image = images[index].image;

    glColor4f(color.r, color.g, color.b, color.a);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, image);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, windowSize.GetWidth(), windowSize.GetHeight(), 0);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

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
