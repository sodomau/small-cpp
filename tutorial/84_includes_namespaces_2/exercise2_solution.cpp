#include <iostream>
#include <string>

void small_main()
{
    std::string name;

    std::cout << "Name: ";
    std::getline(std::cin, name);
    std::cout << "Hello, " << name << "\n";
}
