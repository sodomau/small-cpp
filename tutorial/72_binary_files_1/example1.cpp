void small_main()
{
    File file;

    file.open("save.dat", FileMode::WriteBinary);
    file.write_int(3);
    file.write_int(1250);
    file.write_real(42.5);
    file.close();

    print("Binary save written");
}
