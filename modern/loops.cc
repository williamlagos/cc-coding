#include<iostream>

int main(int argc, char** argv) {
    auto vec = { 1, 2, 3 };
    for(auto v: vec) {
        std::cout << v << std::endl;
    }
    return 0;
}