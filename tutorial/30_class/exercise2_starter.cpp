class Ball
{
public:
    void Move()
    {
        // Move x.
    }

    double X()
    {
        return 0;
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
