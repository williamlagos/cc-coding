#include <iostream>
#include <iomanip>
#include <limits>

int main() {
    int i = 4;
    double d = 4.0;
    std::string s = "HackerRank ";

    
    // Declare second integer, double, and String variables.
    int i0;
    double d0;
    std::string s0; 
    
    // Read and save an integer, double, and String to your variables.
    std::cin >> i0;
    std::cin >> d0;
    std::getline(std::cin >> std::ws, s0);

    // Note: If you have trouble reading the entire string, please go back and review the Tutorial closely.
    
    // Print the sum of both integer variables on a new line.
    std::cout << i + i0 << std::endl;
    // Print the sum of the double variables on a new line.
    std::cout << std::fixed << std::setprecision(1) << d + d0 << std::endl;
    // Concatenate and print the String variables on a new line
    // The 's' variable above should be printed first.
    std::cout << s + s0 << std::endl;
    return 0;
}