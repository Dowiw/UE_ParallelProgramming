#include <iostream>
using namespace std;

int main() {
	int number = 10;
	int *ptr;
	ptr = &number;

	cout << number << endl;
	cout << &number << endl;
	cout << *ptr << endl;
	cout << &ptr << endl;
	cout << ptr << endl;

	cout << number << endl;
	number = 11;
	cout << number << endl;
	return (0);
}
