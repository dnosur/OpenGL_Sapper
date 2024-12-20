#pragma once
#include "Window.h"

#include "Rect.h"
#include "Triangle.h"
#include "Circle.h"

#include "Figures.h"
#include "GameField.h"
#include "WindowPointerController.h"

class MainWindow :
    public Window
{
public:
    MainWindow();
    MainWindow(Size size, const char* title, Color backgroundColor = Color(1, 1, 1), GLFWmonitor* monitor = NULL, GLFWwindow* share = NULL);

    void Initialize() override;
    void Update() override;

    void PlayExplosionAnimation(Coord coord, std::vector<Image>& frames, int frameRate);
};

