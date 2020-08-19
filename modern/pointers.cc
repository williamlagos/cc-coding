#include<iostream>
#include<memory>

int main(int argc, char** argv)
{
    auto p1 = std::make_shared<int>(5);
    auto p2 = std::make_unique<int>(10);
    auto p3 = p1;
    std::cout << p1.use_count() << std::endl;
    std::cout << "Hello World for " << *p1 << " and " << *p2 << std::endl;
    return 0;
}