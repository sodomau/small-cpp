void small_main()
{
    print("Five dice rolls:");
    for (int i = 0; i < 5; i++)
        print(random_int(1, 6));

    print("Three random real numbers from 0.0 up to 1.0:");
    for (int i = 0; i < 3; i++)
        print(random_real(0.0, 1.0));
}
