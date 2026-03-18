#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int t;
    std::cin >> t;
    std::vector<std::string> strings;
    for (int i = 0; i < t; i++) {
        std::string str;
        std::getline(std::cin >> std::ws, str);
        strings.push_back(str);
    }
    for (int i = 0; i < t; i++) {
        const std::string& s = strings[i];
        std::string odd, eve;
        for (std::size_t j = 0; j < s.length(); j++) {
            if (j % 2 == 0) eve += s[j];
            else odd += s[j];
        }
        std::cout << eve << " " << odd << std::endl;
    }
    return 0;
}