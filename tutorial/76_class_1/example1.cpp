class Counter
{
public:
    void add_one()
    {
        value = value + 1;
    }

    int get_value()
    {
        return value;
    }

private:
    int value = 0;
};

void small_main()
{
    Counter counter;

    counter.add_one();
    counter.add_one();

    print(counter.get_value());
}
