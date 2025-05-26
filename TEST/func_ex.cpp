#include <iostream>
using namespace std;

// Function Declarations
int add(int a, int b);
int passByVal(int x);
void passByRef(int &x);
int factorial(int n); // Recursion

int main() {
    int result = add(5, 3); // Call add
    cout << "Addition result: " << result << endl;

    int value = 15;
    int valResult = passByVal(value); // Pass by value
    cout << "After passByVal (original value): " << value << ", Returned value: " << valResult << endl;

    int refValue = 15;
    passByRef(refValue); // Pass by reference
    cout << "After passByRef (modified value): " << refValue << endl;

    int x = 5;
    int fact = factorial(x); // Call factorial and store result
    cout << "Factorial of " << x << " is: " << fact << endl;

    return 0;
}

// Definition of add function
int add(int a, int b) {
    return a + b;
}

// Pass by value
int passByVal(int x) {
    x = 10;
    return x; // Return modified value
}

// Pass by reference
void passByRef(int &x) {
    x = 10; // Modifies original variable
}

// Recursion example via Factorial
int factorial(int n) {
    if (n <= 1) return 1;
    else return n * factorial(n - 1);
}
