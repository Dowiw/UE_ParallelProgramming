#include <iostream>
#include <string>
using namespace std;

class BankAccount {
private:
    string customerName;
    double balance;

public:
    // Constructor
    BankAccount(const string& name, double balance) {
        this->customerName = name;
        this->balance = balance;
    }

    // Deposit function
    void deposit(double amount) {
        if (amount > 0) {
            cout << "You are depositing: " << amount << ".\n";
            balance += amount;
            cout << "Successful, current balance: " << balance << ".\n";
        }
        else {
            cout << "Error depositing amount: ensure numeric postive value.\n";
        }
    }

    // Withdraw function
    void withdraw(double amount) {
        if (amount < 0) {
            cout << "Error withdrawing: ensure numeric positive value.\n";
        } else if (amount > balance) {
            cout << "You're balance " << balance <<  "is lower than withdrawal amount " << amount << ".\n";
        } else {
            balance -= amount;
            cout << "Successful, current balance: " << balance << ".\n";
        }
    }

    // Display balance
    void display() const {
        cout << "Your current balance is: %d\n" << balance;
    }
};

int main() {
    //Create instance
    BankAccount KB("KB", 1000.0);

    KB.deposit(1000.0);
    KB.withdraw(1000.0);
    return 0;
}
