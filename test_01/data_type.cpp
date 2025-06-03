#include <iostream>
using namespace std;

int main() {
    //Integer Types
    int a = 42;
    long b = 123456789;
    long long c = 9876543210;

    cout << "int: " << a << endl;
    cout << "long: " << b << endl;
    cout << "long long: " << c << endl;

    //TO-DO: sizeof()

    //Floating-Point Types
    float f = 3.14f;
    double d = 3.1415926535;
    long double ld = 3.141592653589793238L;

    cout << "float: " << f << endl;
    cout << "double: " << d << endl;
    cout << "long double: " << ld << endl;

    //Character Type (char)
    char letter = 'A';
    cout << "Character: " << letter << endl;

    //Boolean Type (bool)
    bool isCodingFun = true;
    cout << "Is coding fun? " << isCodingFun << endl;

    return 0;
}
