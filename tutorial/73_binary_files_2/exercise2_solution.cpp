void small_main()
{
    File file;

    file.open("state.dat", FileMode::WriteBinary);
    file.write_int(7);
    file.write_real(3.5);
    file.close();

    file.open("state.dat", FileMode::ReadBinary);
    int number = file.read_int();
    double value = file.read_real();
    file.close();

    print(number);
    print(value);
}
