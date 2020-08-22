#include<iostream>
#include<cmath>

constexpr int square(int x) {
  return x * x;
}

// `unsigned long long` parameter required for integer literal.
long long operator "" _celsius(unsigned long long tempCelsius) {
  return std::llround(tempCelsius * 1.8 + 32);
}

int main(int argc, char** argv) {
    int x = 1;

    std::cout << square(x) << std::endl;

    std::cout << 24_celsius << std::endl; // == 75

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