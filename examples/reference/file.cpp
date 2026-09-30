void SmallMain()
{
    File file;

    // Text file
    file.Open("example.txt", FileMode::Write);
    file.Print("Alice");
    file.Print(10);
    file.Write("Score: ", 95);
    file.Print();
    file.Close();

    file.Open("example.txt");
    Print("File open: ", file.IsOpen());
    while (!file.End())
        Print(file.Input());
    file.Close();

    file.Open("example.txt", FileMode::Read);
    Print("First line again: ", file.Input());
    file.Close();

    file.Open("example.txt", FileMode::Append);
    file.Print("One more line");
    file.Close();

    // Binary file: values are written using their native C++ representation.
    file.Open("numbers.txt", FileMode::Write);
    file.Print(123);
    file.Print(4.5);
    file.Close();

    file.Open("numbers.txt");
    int textInt = file.InputInt();
    double textReal = file.InputReal();
    file.Close();
    Print("Text integer: ", textInt);
    Print("Text real: ", textReal);

    file.Open("save.dat", FileMode::WriteBinary);
    file.WriteInt(100);
    file.WriteReal(3.14);
    file.Close();

    file.Open("save.dat", FileMode::ReadBinary);
    int score = file.ReadInt();
    double value = file.ReadReal();
    file.Close();

    Print("Binary score: ", score);
    Print("Binary real: ", value);
}
