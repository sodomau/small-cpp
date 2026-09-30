class Ball
{
public:
    void Move()
    {
        x = x + speed;
    }

    void Draw(Window& window)
    {
        window.FillCircle(x, 200, 20, Yellow);
    }

private:
    double x = 50;
    double speed = 2;
};

void SmallMain()
{
    Window window;
    window.Open(640, 400);

    Ball ball;

    while (window.IsOpen())
    {
        ball.Move();

        window.Clear(Black);
        ball.Draw(window);
        window.Show();
        Sleep(0.01);
    }
}
