#include <iostream>
#include <string>

void SmallMain()
{
    std::string name;

    std::cout << "Name: ";
    std::getline(std::cin, name);

    std::cout << "Hello, " << name << "\n";
}
