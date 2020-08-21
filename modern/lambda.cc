#include<iostream>

int main(int argc, char** argv) {
    int x = 1;

    // [] - captures nothing.
    // [=] - capture local objects (local variables, parameters) in scope by value.
    // [&] - capture local objects (local variables, parameters) in scope by reference.
    // [this] - capture this by reference.
    // [a, &b] - capture objects a by value, b by reference.

    auto getX = [=] { return x; };
    std::cout << getX() << std::endl; // == 1

    auto addX = [=](int y) { return x + y; };
    std::cout << addX(1) << std::endl; // == 2

    auto getXRef = [&]() -> int& { return x; };
    std::cout << getXRef() << std::endl; // int& to `x`
    return 0;
}