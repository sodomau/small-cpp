#include <iostream>
#include <vector>

int main()
{
    std::vector<int> numbers = {10, 20, 30};
    int total = 0;

    for (int value : numbers)
        total = total + value;

    std::cout << total << "\n";

    return 0;
}
