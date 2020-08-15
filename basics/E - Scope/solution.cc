#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Difference {
    private:
    vector<int> elements;
  
  	public:
  	int maximumDifference;
    
    Difference(vector<int> elements) {
        this->elements = elements;
    }

	// Add your code here
    void computeDifference() {
        int max = 0;
        for (int i = 0; i < this->elements.size(); i++) {
            for (int j = 0; j < this->elements.size(); j++) {
                int diff = abs(elements[i] - elements[j]);
                if (diff > max) max = diff;
            }
        }
        this->maximumDifference = max;
    }

}; // End of Difference class

int main() {
    int N;
    cin >> N;
    
    vector<int> a;
    
    for (int i = 0; i < N; i++) {
        int e;
        cin >> e;
        
        a.push_back(e);
    }
    
    Difference d(a);
    
    d.computeDifference();
    
    cout << d.maximumDifference;
    
    return 0;
}