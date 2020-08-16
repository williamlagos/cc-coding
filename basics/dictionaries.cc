#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int count;
    unordered_map<string, string> phoneBook; 
    cin >> count;
    for (int i = count; i > 0; i--) {
        string name, number;
        cin >> name;
        cin >> number;
        phoneBook[name] = number;
    }
    string str;
    while(getline(cin >> ws, str)) {
        if (phoneBook.find(str) != phoneBook.end()) {
            cout << str << "=" << phoneBook[str] << endl;
        } else {
            cout << "Not found" << endl;
        }
    }
    return 0;
}

