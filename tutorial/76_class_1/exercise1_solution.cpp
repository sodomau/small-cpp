class Counter
{
public:
    void AddOne()
    {
        value = value + 1;
    }

    void Reset()
    {
        value = 0;
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
    counter.Reset();
    Print(counter.Value());
}
