#include<memory>
#include<vector>
#include<iostream>
#include<exception>

template<typename T>
class node {
public:
    T value;
    std::vector<std::weak_ptr<node<T>>> neighbors;
    node(T value) : value{value}, neighbors{} { std::cout << "n " << value << std::endl; };
    ~node() { std::cout << "~n " << value << std::endl; };
};

template<typename T>
class graph : public std::vector<std::shared_ptr<node<T>>> {
public:
    std::weak_ptr<node<T>> get(std::size_t i) {
        auto ret = std::weak_ptr<node<T>>{};
        ret = std::vector<std::shared_ptr<node<T>>>::operator[](i);
        return ret;
    };
};

int main (int argc, char** argv) {
    graph<int> g;
    g.emplace_back(std::make_shared<node<int>>(0));
    g.emplace_back(std::make_shared<node<int>>(1));
    g.emplace_back(std::make_shared<node<int>>(2));
    g[0]->neighbors.emplace_back(g.get(1));
    g[1]->neighbors.emplace_back(g.get(0));
    g[2]->neighbors.emplace_back(g.get(0));
    g[2]->neighbors.emplace_back(g.get(1));
    auto ptr = g.get(0);
    std::cout << ptr.lock()->value << std::endl;
    ptr = ptr.lock()->neighbors[0];
    std::cout << ptr.lock()->value << std::endl;
    ptr = ptr.lock()->neighbors[0];
    std::cout << ptr.lock()->value << std::endl;
    ptr = ptr.lock()->neighbors[0];
    std::cout << ptr.lock()->value << std::endl;
    ptr = ptr.lock()->neighbors[0];
    std::cout << ptr.lock()->value << std::endl;
    ptr = ptr.lock()->neighbors[0];
    std::cout << ptr.lock()->value << std::endl;
    std::cout << "graph" << std::endl;
    for(auto n: g) {
        std::cout << "node: " << n->value << std::endl;
        std::cout << "neighbors: ";
        for(auto v: n->neighbors) {
            std::cout << v.lock()->value << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}