#include<iostream>

int main(int argc, char** argv) {
    std::tuple<int, int> tup = {1, 2};
    auto [v1, v2] = tup;
    std::cout << v1 << v2 << std::endl;
    return 0;
}