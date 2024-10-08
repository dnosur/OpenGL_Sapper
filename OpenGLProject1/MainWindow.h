#pragma once
#include "Window.h"
#include "Rect.h"

class MainWindow :
    public Window
{
public:
    MainWindow();
    MainWindow(Size size, const char* title, Color backgroundColor = Color(1, 1, 1), GLFWmonitor* monitor = NULL, GLFWwindow* share = NULL);

    void Update() override;
};

