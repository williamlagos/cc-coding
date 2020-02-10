#include <iostream>

using namespace std;

int main()
{
    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    int count = 0;
    int max = 0;
    // vector<int> binary;
    while (n > 0) {
        if (n % 2 == 1) {
            count++;
            if (max < count) max = count;
        } else count = 0;
        n = n / 2;
        // binary.insert(binary.begin(), bit);
        // binary.push_back(bit);
    }
    /* int count = 1;
    int maxCount = 1;
    for (int i = binary.size() - 1; i > 0; i--) {
        if (binary[i - 1] == 1 && binary[i] == 1) {
            count++;
        } else {
            if (maxCount <= count) maxCount = count;
            count = 1;
        }
    } */
    cout << max;
    return 0;
}
