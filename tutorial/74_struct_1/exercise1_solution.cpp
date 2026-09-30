struct Point
{
    double x;
    double y;
};

void SmallMain()
{
    Point point;
    point.x = 3.5;
    point.y = 7.0;

    Print(point.x, ", ", point.y);
}
