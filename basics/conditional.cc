#include <iostream>
#include <limits>

int main()
{
    int N;
    std::cin >> N;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (N % 2 != 0) {
        std::cout << "Weird" << std::endl;
    } else if (N % 2 == 0) {
        if (N >= 2 && N <= 5) std::cout << "Not Weird" << std::endl;
        else if (N >= 6 && N <= 20) std::cout << "Weird" << std::endl;
        else if (N > 20) std::cout << "Not Weird" << std::endl;
    }

    return 0;
}
