#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

class Difference {
    private:
    std::vector<int> elements;
  
    public:
    int maximumDifference;
    
    explicit Difference(std::vector<int> elements) : elements{std::move(elements)}, maximumDifference{0} {}

    // Add your code here
    void computeDifference() {
        int max = 0;
        for (std::size_t i = 0; i < this->elements.size(); i++) {
            for (std::size_t j = 0; j < this->elements.size(); j++) {
                int diff = std::abs(elements[i] - elements[j]);
                if (diff > max) max = diff;
            }
        }
        this->maximumDifference = max;
    }

}; // End of Difference class

int main() {
    int N;
    std::cin >> N;
    
    std::vector<int> a;
    
    for (int i = 0; i < N; i++) {
        int e;
        std::cin >> e;
        
        a.push_back(e);
    }
    
    Difference d(a);
    
    d.computeDifference();
    
    std::cout << d.maximumDifference;
    
    return 0;
}