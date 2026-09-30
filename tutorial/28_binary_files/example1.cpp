void SmallMain()
{
    File file;

    file.Open("save.dat", FileMode::WriteBinary);
    file.WriteInt(3);
    file.WriteInt(1250);
    file.WriteReal(42.5);
    file.Close();

    Print("Binary save written");
}
