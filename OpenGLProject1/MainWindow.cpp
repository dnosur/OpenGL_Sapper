#include "MainWindow.h"

MainWindow::MainWindow(): Window()
{
}

MainWindow::MainWindow(Size size, const char* title, Color backgroundColor, GLFWmonitor* monitor, GLFWwindow* share):
    Window(size, title, backgroundColor, monitor, share) {}

void MainWindow::Initialize()
{
    if (!gladLoadGL()) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return;
    }

    images.Load("images/redFlag.png", "redFlag");
    images.Load("images/mine.png", "mine");
    images.Load("images/hole.png", "hole");
    images.Load("images/ground.png", "ground");
    images.Load("images/fail.png", "fail");
    images.Load("images/won.png", "won");

    audioController.Load(Audio("diggin", "sounds/diggin.wav"));
    audioController.Load(Audio("set_flag", "sounds/set_flag.wav"));
    audioController.Load(Audio("reset_flag", "sounds/reset_flag.wav"));
    audioController.Load(Audio("fail", "sounds/fail.wav"));
    audioController.Load(Audio("won", "sounds/won.wav"));

    WindowPointerController::SetPointer(window, WindowPointer<Mouse>("Mouse", &mouse));
    WindowPointerController::SetPointer(window, WindowPointer<Keyboard>("Keyboard", &keyboard));

    WindowPointerController::SetPointer(window, WindowPointer<AudioController>("audioController", &audioController));
}

void MainWindow::Update()
{
    GameField gameField(*this, 20, 20, 35);

    Triangle triangle("Sample triangle", *this, Coord(800, 100), Size(100, 100), Color(1.0f, 0.0f, 0.0f));
    triangle.SetShader(new Shader("triangle_sample", "shaders/Triangle/vertex.vs", "shaders/Triangle/fragment.frag"));

    triangle.HookMouseHover([](IFigure* figure, GLFWwindow* window) {
        std::cout << "Mouse triangle hover: " << figure->GetTitle() << std::endl;
    });

    triangle.HookMouseClick([](IFigure* figure, GLFWwindow* window) {
            std::cout << "Mouse triangle click: " << figure->GetTitle() << std::endl;
    });

    Circle circle("Sample circle", *this, Coord(800, 300), 30, 60, Color(0.3f, 1.0f, 0.6f));

    circle.HookMouseHover([](IFigure* figure, GLFWwindow* window) {
		std::cout << "Mouse cyrcle hover: " << figure->GetTitle() << std::endl;
    });

    circle.HookMouseClick([](IFigure* figure, GLFWwindow* window) {
        std::cout << "Mouse cyrcle click: " << figure->GetTitle() << std::endl;
    });

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
            Color(0.4f, 0.4f, 0.4f)
        );


        gameField.Draw();
        //triangle.Draw();

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
