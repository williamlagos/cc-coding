#include<iostream>

int main(int argc, char** argv) {
    auto vec = { 1, 2, 3 };
    auto text = "Hello World!";
    std::cout << text << std::endl;
    for(auto v: vec) {
        std::cout << v << std::endl;
    }
    decltype(vec) vct = { 'a', 'b', 'c' };
    std::tuple<int, int> tup = {1, 2};
    auto [v1, v2] = tup;
    std::cout << v1 << v2 << std::endl;
    return 0;
}