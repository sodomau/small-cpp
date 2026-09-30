#include <iostream>
#include <string>

int main()
{
    std::string name;

    std::cout << "Name: ";
    std::getline(std::cin, name);

    std::cout << "Hello, " << name << "\n";

    return 0;
}
