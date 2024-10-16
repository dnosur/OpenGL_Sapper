#define STB_IMAGE_IMPLEMENTATION

#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include <iostream>

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
    MainWindow main(Size(1280, 720), "Sapper");

    main.MakeContext();
    main.Initialize();
    main.Update();

    return 0;
}
