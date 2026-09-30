class Ball
{
public:
    void Move()
    {
        x = x + speed;
    }

    double X()
    {
        return x;
    }

private:
    double x = 10;
    double speed = 5;
};

void SmallMain()
{
    Ball ball;
    ball.Move();
    ball.Move();
    ball.Move();

    Print(ball.X());
}
