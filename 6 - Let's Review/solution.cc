#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int t;
    cin >> t;
    vector<string> strings;
    for (int i = 0; i < t; i++) {
        string str;
        getline(cin >> ws, str);
        strings.push_back(str);
    }
    for (int i = 0; i < t; i++) {
        string s = strings[i];
        string odd, eve;
        for (int j = 0; j < s.length(); j++) {
            if (j % 2 == 0) eve += s[j];
            else if (j % 2 != 0) odd += s[j];
        }
        cout << eve << " " << odd << endl;
    }
    return 0;
}