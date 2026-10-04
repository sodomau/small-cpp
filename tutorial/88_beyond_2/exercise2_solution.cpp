#include <iostream>
#include <string>

void greet(const std::string& name)
{
    std::cout << "Hello, " << name << "!\n";
}

int main()
{
    std::string name = "Alex";

    greet(name);

    return 0;
}
