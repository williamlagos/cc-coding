#include<iostream>

template <typename First, typename... Args>
auto sum(const First first, const Args... args) -> decltype(first) {
    const auto values = {first, args...};
    return std::accumulate(values.begin(), values.end(), First{0});
}

int main(int argc, char** argv) {
    std::tuple<int, int> tup = {1, 2};
    auto [v1, v2] = tup;
    std::cout << v1 << v2 << std::endl;
    return 0;
}