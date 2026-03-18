#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

class Book {
    protected:
        std::string title;
        std::string author;
    public:
        Book(std::string t, std::string a) : title{std::move(t)}, author{std::move(a)} {}
        virtual void display() = 0;
};

class MyBook : Book {
// Write your MyBook class here
    private:
        int price;
    public:
        //   Class Constructor
        //   
        //   Parameters:
        //   title - The book's title.
        //   author - The book's author.
        //   price - The book's price.
        //
        MyBook(std::string title, std::string author, int price) :
        Book(std::move(title), std::move(author)), price{price} {
            // Write your constructor here
        }
    
        //   Function Name: display
        //   Print the title, author, and price in the specified format.
        //
        void display() override {
            std::cout << "Title: " << this->title << std::endl;
            std::cout << "Author: " << this->author << std::endl;
            std::cout << "Price: " << this->price << std::endl;
        }
        // Write your method here
    
// End class
};

int main() {
    std::string title, author;
    int price;
    std::getline(std::cin, title);
    std::getline(std::cin, author);
    std::cin >> price;
    MyBook novel(title, author, price);
    novel.display();
    return 0;
}
