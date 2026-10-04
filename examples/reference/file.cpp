void small_main()
{
    File file;

    // Text file
    file.open("example.txt", FileMode::Write);
    file.print("Alice");
    file.print(10);
    file.write("Score: ", 95);
    file.print();
    file.close();

    file.open("example.txt");
    print("File open: ", file.is_open());
    while (!file.end())
        print(file.input());
    file.close();

    file.open("example.txt", FileMode::Read);
    print("First line again: ", file.input());
    file.close();

    file.open("example.txt", FileMode::Append);
    file.print("One more line");
    file.close();

    // Binary file: values are written using their native C++ representation.
    file.open("numbers.txt", FileMode::Write);
    file.print(123);
    file.print(4.5);
    file.close();

    file.open("numbers.txt");
    int text_int = file.input_int();
    double text_real = file.input_real();
    file.close();
    print("Text integer: ", text_int);
    print("Text real: ", text_real);

    file.open("save.dat", FileMode::WriteBinary);
    file.write_int(100);
    file.write_real(3.14);
    file.close();

    file.open("save.dat", FileMode::ReadBinary);
    int score = file.read_int();
    double value = file.read_real();
    file.close();

    print("Binary score: ", score);
    print("Binary real: ", value);
}
