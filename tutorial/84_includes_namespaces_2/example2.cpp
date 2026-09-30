#include <iostream>
#include <string>

void SmallMain()
{
    Small::String smallText = "Small namespace";
    Small::Print(smallText);

    std::string standardText = "Standard namespace";
    std::cout << standardText << "\n";
}
