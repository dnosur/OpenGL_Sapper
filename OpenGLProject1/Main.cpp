#define STB_IMAGE_IMPLEMENTATION

#include <GLFW/glfw3.h>
#include "Figures.h"
#include <iostream>

#include "MainWindow.h"
#include <GL/glut.h>

int main(int argc, char** argv)
{
    srand(time(NULL));
    glutInit(&argc, argv);
    if (!glfwInit())
        return -1;

    glRasterPos2f(1, 1);

    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '!');
    MainWindow main(Size(1280, 720), "Sapper");

    main.MakeContext();
    main.Initialize();
    main.Update();

    return 0;
}
