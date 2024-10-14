#include "MainWindow.h"
#include "Figures.h"
#include "GameField.h"
#include "WindowPointerController.h"

MainWindow::MainWindow(): Window()
{
}

MainWindow::MainWindow(Size size, const char* title, Color backgroundColor, GLFWmonitor* monitor, GLFWwindow* share):
    Window(size, title, backgroundColor, monitor, share) {}

void MainWindow::Initialize()
{
    WindowPointerController::SetPointer(window, WindowPointer<Mouse>("Mouse", &mouse));
    WindowPointerController::SetPointer(window, WindowPointer<Keyboard>("Keyboard", &keyboard));

    images.Load("images/redFlag.png", "redFlag");
    images.Load("images/mine.png", "mine");
    images.Load("images/hole.png", "hole");
    images.Load("images/ground.png", "ground");

    for (int i = 0; i < 81; i++) {
        std::string path = "animations/explosion1/" + std::to_string(i) + ".png";

        images.Load(path.c_str(), std::to_string(i).c_str());
    }
}

void MainWindow::Update()
{
    GameField gameField(*this, 20, 20, 35);

    std::vector<Image> animation;
    for (int i = 0; i < 80; i++) {
        animation.push_back(images.GetImageByTitle(std::to_string(i).c_str()));
    }

    while (!glfwWindowShouldClose(GetWindow()) && !IsClosed())
    {
        FillBackground();
        glClear(GL_COLOR_BUFFER_BIT);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        images.DrawImage(
            "ground", 
            Coord(0, 0), 
            GetSize(), 
            GetSize(), 
            Color(0.4f, 0.4f, 0.4f, 0.4f)
        );

        //PlayExplosionAnimation(Coord(100, 100), animation, 10);

        gameField.Draw();
        mouse.Update();
        keyboard.Update();

        //Debug();  // ֲûגמהטל סטלגמכ

        glfwSwapBuffers(GetWindow());
        glfwPollEvents();
    }

    CloseWindow();
}

void MainWindow::PlayExplosionAnimation(Coord coord, std::vector<Image>& frames, int frameRate)
{
    static int currentFrame = 0;
    static float timePassed = 0.0f;

    float deltaTime = timer.GetDeltaTime();

    timePassed += deltaTime;

    if (timePassed >= (1.0f / frameRate)) {
        timePassed = 0;
        currentFrame = (currentFrame + 1) % frames.size();
    }

    images.DrawImage(frames[currentFrame].title, coord, Size(50, 50), GetSize());
}
