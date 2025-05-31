#include <iostream>
#include <limits>
#include <vector>
using namespace std;

class Account {
	protected:
	int accountNumber;
	string holderName;
	float balance;

	public:
	Account(int accNum, const string& accName, float accBal)
	: accountNumber(accNum), holderName(accName), balance(accBal) {
		if (accBal < 0) {
			throw invalid_argument("Initital Balance cannot be less than 0.");
		}
	}

	// Boolean for duplicate account
	static bool isDuplicateAccount(const vector<Account*>& accounts, int newAccountNumber) {
		for (const auto& account : accounts) {
			if (account->accountNumber == newAccountNumber) {
				return (true);
			}
		}
		return (false);
	}

	int getAccountNumber() {
		return (accountNumber);
	}

	// Account desructor
	virtual ~Account() {
		cout << "Account destructor called! Deleting accounts... \n";
	};

	// Account depositor
	void deposit(float amount) {
		if (amount < 0) {
			throw invalid_argument("Deposit amount must be a positive value.");
		}
		balance += amount;
	}

	// Account withdrawer
	void withdraw(float amount) {
		if (amount < 0) {
			throw invalid_argument("Withdraw amount must be a positive value.");
		}
		if (amount > balance) {
			throw runtime_error("Insufficient balance.");
		}
		balance -= amount;
	}

	// Virtual method for display (possible update to overide in savings)
	virtual void displayDetails() const {
		cout << "Account Number: " << accountNumber << endl;
		cout << "Account Holder: " << holderName << endl;
		cout << "Account balance: " << balance << "€" << endl;
	}

	virtual void applyInterest() {}; // Virtual method for inheritance
};

class SavingsAccount : public Account {
	private:
	float interestRate;

	//Inherit Account class
	public:
	SavingsAccount (int accNum, const string &accName, float firstBalance, float rate)
	: Account(accNum, accName, firstBalance), interestRate(rate) {}

	// Override abstract method applyInterest
	void applyInterest() override {
		balance += balance * (interestRate / 100);
	}

	// Override display to display rate
	void displayDetails() const override {
		Account::displayDetails();
		cout << "Interest rate: " << interestRate << "%\n";
	}
};

// Menu Function for easy access
void showMenu() {
	cout << "\nBank Account Management System menu:\n";
	cout << "1. Create new account.\n";
	cout << "2. Deposit.\n";
	cout << "3. Withdraw.\n";
	cout << "4. Display all accounts.\n";
	cout << "5. Apply interest (for savings).\n";
	cout << "6. Exit.\n";
}

// Function to get integer and check if valid while printing out string passed by reference
int	integerGetterAndChecker(const string& print) {
	int out;
	string input;

	while (true) {
		cout << print;
		cin >> input;

		try {
			size_t pos;
			out = stoi(input, &pos);

			if (pos != input.size())
				throw invalid_argument("Input contains non-integer characters.\n");
			return out;
		} catch (const exception&) {
			cout << "Enter a valid integer input!\n";
		}
	}
}

// Function to get float and check if valid while printing out string passed by reference
float	floatGetterAndChecker(const string& print) {
	float out;
	while (true) {
		cout << print;
		cin >> out;

		if (cin.fail()) {
			cin.clear(); // To clear the fail flag
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard characters in stream
			cout << "Enter a valid decimal number! (float).\n";
		} else {
			return (out);
		}
	}
}

int main() {
	vector<Account *> accounts; //Account * for overidden methods
	bool buffer = true;
	int option;

	while (buffer) {
		showMenu();
		option = integerGetterAndChecker("\nEnter a choice: ");

		try {
			switch (option) {
			case 1: {
				int accNum;
				string accName;
				float accBal, rate;

				accNum = integerGetterAndChecker("Enter Account Number: ");
				if (Account::isDuplicateAccount(accounts, accNum)) {
					cout << "Account already exists! \n";
				} else {
					cin.ignore(); // Ignore new line for string
					cout << "Enter Account Name: ";
					cin >> accName;
					accBal = floatGetterAndChecker("Enter Account Balance: ");
					rate = floatGetterAndChecker("Enter Account Interest Rate (for savings): ");
					accounts.push_back(new SavingsAccount(accNum, accName, accBal, rate));
					cout << "Account made successfully!\n";
				}
				break;
			}
			case 2: {
				int accNum = integerGetterAndChecker("Enter account number: ");
				float amount = floatGetterAndChecker("Enter deposit amount: ");

				bool found = false;
				for (auto account : accounts) {
					if (account->getAccountNumber() == accNum) {
						account->deposit(amount);
						cout << "Deposit successful!\n";
						found = true;
						break;
					}
				}
				if (!found) {
					cout << "Account not found!\n";
				}
				break;
			}
			case 3: {
				int accNum = integerGetterAndChecker("Enter account number: ");
				float amount = floatGetterAndChecker("Enter deposit amount: ");

				bool found = false;
				for (auto account : accounts) {
					if (account->getAccountNumber() == accNum) {
						account->withdraw(amount);
						cout << "Withdraw successful!\n";
						found = true;
						break;
					}
				}
				if (!found) {
					cout << "Account not found!\n";
				}
				break;
			}
			case 4: {
				for (auto account : accounts) {
					cout << "-------------------\n";
					account->displayDetails();
					cout << "-------------------\n";
				}
				break;
			}
			case 5: {
				int accNum = integerGetterAndChecker("Enter account number: ");

				bool found = false;
				for (auto account : accounts) {
					if (account->getAccountNumber() == accNum) {
						account->applyInterest();
						cout << "Apply interest successful!\n";
						found = true;
						break;
					}
				}
				if (!found) {
					cout << "Account not found!\n";
				}
				break;
			}
			case 6: {
				size_t i;
				for (auto account : accounts) {
					cout << "Deletion called " << i << " time(s).\n";
					delete account;
					i++;
				}
				cout << "Exiting program. Good bye :)\n";
				return (0);
			}
			default:
				cout << "Invalid choice! Try again (1 - 6).\n";
			}
		} catch (const exception& e) {
			cout << "Error: " << e.what() << endl;
		}
	}
	return (0);
}
