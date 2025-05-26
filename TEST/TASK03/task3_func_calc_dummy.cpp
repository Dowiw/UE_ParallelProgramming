#include <iostream>
using namespace std;

int main() {

    //variable declarations
    double x, y, result;
    char sign;

    cout << "Enter first number: ";
    cin >> x;

    cout << "Enter operator (+, -, *, /): ";
    cin >> sign;

    cout << "Enter second number: ";
    cin >> y;

    switch (sign) {
        case '+':
            result = x + y;
            cout << "Result: " << result << endl;
        break;
        case '-':
            result = x - y;
            cout << "Result: " << result << endl;
        break;
        case '*':
            result = x * y;
            cout << "Result: " << result << endl;
        break;
        case '/':
            result = x / y;
            cout << "Result: " << result << endl;
        break;
        default:
        cout << "Operator is not valid. Please try again." << endl;
    }
    return 0;
}
