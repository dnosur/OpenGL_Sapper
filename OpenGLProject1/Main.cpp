#define STB_IMAGE_IMPLEMENTATION
#define GL_GLEXT_PROTOTYPES

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Figures.h"
#include "MainWindow.h"
#include "SoundSystem.h"

int main(int argc, char** argv)
{
    srand(time(NULL));
    glutInit(&argc, argv);
    if (!glfwInit())
        return -1;

    SoundSystem soundSystem;
    MainWindow main(Size(1280, 720), "Sapper", Color(.4f, .6f, 0));

    main.MakeContext();
    main.Initialize();
    main.Update();

    return 0;
}
