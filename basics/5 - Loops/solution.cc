#include <iostream>

using namespace std;

int main()
{
    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    for (int t = 1; t <= 10; t++) {
        cout << n << " x " << t << " = " << n * t << endl;
    }
    return 0;
}
