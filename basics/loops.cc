#include <iostream>
#include <limits>

int main()
{
    int n;
    std::cin >> n;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    for (int t = 1; t <= 10; t++) {
        std::cout << n << " x " << t << " = " << n * t << std::endl;
    }
    return 0;
}
