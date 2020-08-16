#include <iostream>
#include <iomanip>
#include <limits>

using namespace std;

int main() {
    int i = 4;
    double d = 4.0;
    string s = "HackerRank ";

    
    // Declare second integer, double, and String variables.
    int i0;
    double d0;
    string s0; 
    
    // Read and save an integer, double, and String to your variables.
    cin >> i0;
    cin >> d0;
    getline(cin >> ws, s0);

    // Note: If you have trouble reading the entire string, please go back and review the Tutorial closely.
    
    // Print the sum of both integer variables on a new line.
    cout << i + i0 << endl;
    // Print the sum of the double variables on a new line.
    cout << fixed << setprecision(1) << d + d0 << endl;
    // Concatenate and print the String variables on a new line
    // The 's' variable above should be printed first.
    cout << s + s0 << endl;
    return 0;
}