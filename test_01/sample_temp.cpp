#include <iostream>
using namespace std;


static int func()
{
    float pi = 3.14;
}
int main() {
    // Declaring different data types
    int age = 25;
    float temperature = 36.5;
    double pi = 3.141592653589;
    char grade = 'A';
    bool isSunny = true;
    string name = "Alice";

    // Using sizeof() to check memory usage
    cout << "Size of int: " << sizeof(int) << " bytes" << endl;
    cout << "Size of float: " << sizeof(float) << " bytes" << endl;
    cout << "Size of double: " << sizeof(double) << " bytes" << endl;
    cout << "Size of char: " << sizeof(char) << " bytes" << endl;
    cout << "Size of bool: " << sizeof(bool) << " bytes" << endl;
    return 0;
}
