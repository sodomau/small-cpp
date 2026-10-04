struct Point
{
    double x;
    double y;
};

void small_main()
{
    Point point;
    point.x = 3.5;
    point.y = 7.0;

    print(point.x, ", ", point.y);
}
