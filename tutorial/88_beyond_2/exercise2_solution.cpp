#include <iostream>
#include <string>

void Greet(const std::string& name)
{
    std::cout << "Hello, " << name << "!\n";
}

int main()
{
    std::string name = "Alex";

    Greet(name);

    return 0;
}
