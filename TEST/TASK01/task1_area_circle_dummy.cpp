#include <iostream>
using namespace std;

int main() {
    const double pi = 3.14159; //Pi constant
    double radius;
    double area;

    // Enter radius
    cout << "Enter the radius of the circle: ";
    cin >> radius;

    // Calculation
    area = pi * radius * radius;

    // Output result
    cout << "The area of the circle is: " << area << endl;
    return 0;
}
