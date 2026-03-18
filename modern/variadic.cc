#include<iostream>

void print() {}
template <typename First, typename... Rest>
void print(const First &first, Rest &&... args)
{
    std::cout << first << std::endl;
    print(std::forward<Rest>(args)...);
}

int main(int argc, char** argv) {
    print(1, "lol", 1.1);
    return 0;
}