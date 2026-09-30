void SmallMain()
{
    File file;

    file.Open("state.dat", FileMode::WriteBinary);
    file.WriteInt(7);
    file.WriteReal(3.5);
    file.Close();

    file.Open("state.dat", FileMode::ReadBinary);
    int number = file.ReadInt();
    double value = file.ReadReal();
    file.Close();

    Print(number);
    Print(value);
}
