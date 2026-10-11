#include <iostream>
#include <string>

void small_main()
{
    Small::String small_text = "Small namespace";
    Small::print(small_text);

    std::string standard_text = "Standard namespace";
    std::cout << standard_text << "\n";
}
