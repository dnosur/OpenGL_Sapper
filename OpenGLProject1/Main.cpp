#include <GLFW/glfw3.h>
#include "Figures.h"
#include <iostream>

#include "MainWindow.h"

//void Sample(Window& window) {
//    Window* main = &window;
//    main->MakeContext();
//    main->Update();
//}

int main(void)
{
    srand(time(NULL));
    if (!glfwInit())
        return -1;


    MainWindow main(Size(1280, 720), "Sapper");

    main.MakeContext();
    main.Update();

    return 0;
}
