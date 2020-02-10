#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
class Book{
    protected:
        string title;
        string author;
    public:
        Book(string t,string a){
            title=t;
            author=a;
        }
        virtual void display()=0;

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
        MyBook(string title, string author, int price) :
        Book(title, author) {
            this->price = price;
            // Write your constructor here
        }
    
        //   Function Name: display
        //   Print the title, author, and price in the specified format.
        //
        void display() {
            cout << "Title: " << this->title << endl;
            cout << "Author: " << this->author << endl;
            cout << "Price: " << this->price << endl;
        }
        // Write your method here
    
// End class
};

int main() {
    string title,author;
    int price;
    getline(cin,title);
    getline(cin,author);
    cin>>price;
    MyBook novel(title,author,price);
    novel.display();
    return 0;
}
