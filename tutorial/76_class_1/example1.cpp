class Counter
{
public:
    void AddOne()
    {
        value = value + 1;
    }

    int Value()
    {
        return value;
    }

private:
    int value = 0;
};

void SmallMain()
{
    Counter counter;

    counter.AddOne();
    counter.AddOne();

    Print(counter.Value());
}
