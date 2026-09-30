#include <iostream>
#include <vector>

int Sum(const std::vector<int>& numbers)
{
    int total = 0;

    for (int value : numbers)
        total = total + value;

    return total;
}

int main()
{
    std::vector<int> numbers = {3, 7, 2, 9, 4};

    std::cout << "Sum: " << Sum(numbers) << "\n";

    return 0;
}
