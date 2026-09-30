#include <cmath>
#include <iostream>
#include <string>

void SmallMain()
{
    std::string nativeText = "Hello from standard C++";
    Small::String text = nativeText; // std::string -> Small::String


    std::cout << text << '\n';
    std::cout << text.c_str() << '\n';

    double x = std::sqrt(2.0);
    Small::Print("sqrt(2) = ", x);
}
