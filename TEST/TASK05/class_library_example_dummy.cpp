#include <iostream>
#include <string>
using namespace std;

class Book {
public:
    //Member Variables
    string title = "Little Prince";
    string author = "Expury Loin";
    size_t bookID = 122245643321;
    int year = 2005;

    // Display method
    void display() {
        cout << "Title: " << title << "\nAuthor: " << author << "\nYear: " << year << endl;
    }
};

int main() {
    //create object and assign values
    Book KB;

    //display value
    KB.display();
}
