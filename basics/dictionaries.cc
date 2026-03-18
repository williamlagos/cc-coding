#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int count;
    std::unordered_map<std::string, std::string> phoneBook; 
    std::cin >> count;
    for (int i = count; i > 0; i--) {
        std::string name, number;
        std::cin >> name;
        std::cin >> number;
        phoneBook[name] = number;
    }
    std::string str;
    while (std::getline(std::cin >> std::ws, str)) {
        if (phoneBook.find(str) != phoneBook.end()) {
            std::cout << str << "=" << phoneBook[str] << std::endl;
        } else {
            std::cout << "Not found" << std::endl;
        }
    }
    return 0;
}

