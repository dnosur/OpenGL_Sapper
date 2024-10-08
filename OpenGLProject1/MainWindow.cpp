#include "MainWindow.h"
#include "Figures.h"
#include "GameField.h"
#include "WindowPointerController.h"

MainWindow::MainWindow(): Window()
{
}

MainWindow::MainWindow(Size size, const char* title, Color backgroundColor, GLFWmonitor* monitor, GLFWwindow* share):
    Window(size, title, backgroundColor, monitor, share) {}

void MainWindow::Update()
{
    GameField gameField(*this, 20, 20, 15);
    
    glfwSetWindowUserPointer(window, &mouse);

    //WindowPointerController::SetPointer(window, WindowPointer<int>("Sample 1", 12));
    //WindowPointerController::SetPointer(window, WindowPointer<int>("Sample 2", 32));
    //WindowPointer<int> sample2 = WindowPointerController::GetValue<int>(window, "Sample 2");

    //std::cout << sample2.GetValue();
    //sample2.SetValue(44);
    //std::cout << sample2.GetValue();

    //WindowPointerController::SetPointer(window, WindowPointer<int>("Sample 1", 48));

    while (!glfwWindowShouldClose(GetWindow()) && !IsClosed())
    {
        FillBackground();
        glClear(GL_COLOR_BUFFER_BIT);

        gameField.Draw();
        mouse.Update();

        //Debug();

        glfwSwapBuffers(GetWindow());
        glfwPollEvents();
    }

    CloseWindow();
}
