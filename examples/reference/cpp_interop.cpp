#include <cmath>
#include <iostream>
#include <string>

void small_main()
{
    std::string native_text = "Hello from standard C++";
    Small::String text = native_text; // std::string -> Small::String


    std::cout << text << '\n';
    std::cout << text.c_str() << '\n';

    double x = std::sqrt(2.0);
    Small::print("sqrt(2) = ", x);
}
