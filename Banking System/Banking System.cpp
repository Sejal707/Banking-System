#include"Bank.h";
#include "Banking System.h"
using namespace std;
int main()
{
	int choice;
	string fname, lname;
	float balance;
	float amount;
	long accountnumber;
	bool exception_occured;
	Account acc;
	Bank b;
	cout << "\033[31m***Banking System***\033[0m" << endl;
	do {
		cout << "\033[34m\n\tSelect one option from below\033[0m";
		cout << "\033[33m\n\t1. Open an Account";
		cout << "\n\t2. Balance Enquiry";
		cout << "\n\t3. Deposit";
		cout << "\n\t4. Withdrawal";                 
		cout << "\n\t5. Close an Account";
		cout << "\n\t6. Show All Accounts";
		cout << "\n\t7. Quit\033[0m";
		cout << "\033[32m\n\n\tEnter your choice: ";
		cin >> choice;
		cout << "-------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
		switch (choice)
		{
		case 1:
			cout << "Enter First Name: ";
			cin >> fname;
			cout << "Enter Last Name: ";
			cin >> lname;
			do
			{
				exception_occured = false;
				try {
					cout << "Enter intial Balance(BALANCE MUST BE 500): ";
					cin >> balance;
					if (balance < MIN_BALANCE)
						throw MinimumBalance();
				}
				catch (MinimumBalance e)
				{
					cout << "Balance less than 500!" << endl;
					exception_occured = true;
				}
			} while (exception_occured);
			acc = b.OpenAccount(fname, lname, balance);
			cout << "-------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
			cout << "CONGRATULATIONS! Account is created." << endl;
			cout << acc;
			break;
		case 2:
			do {
				exception_occured = false;
				try {
					cout << "Enter Account Number: ";
					cin >> accountnumber;
					acc = b.BalanceEnquiry(accountnumber);
					cout << endl << "Account Details: " << endl;
					cout << acc;

				}
				catch (InvalidAccountNumber e)
				{
					cout << "Account " << accountnumber << " does not exist!" << endl;
					exception_occured = true;
				}
			} while (exception_occured);
			break;
		case 3:
			do {
				exception_occured = false;
				try {
					cout << "Enter Account Number: ";
					cin >> accountnumber;
					cout << "Enter amount to deposit: ";
					cin >> amount;
					acc = b.Deposit(accountnumber, amount);
					cout << "-------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
					cout << "Amount " << amount << " is deposited to account " << accountnumber << "." << endl;
					cout << acc;

				}
				catch (InvalidAccountNumber e)
				{
					cout << "Account " << accountnumber << " does not exist!" << endl;
					exception_occured = true;
				}
			} while (exception_occured);
			break;
		case 4:
			do {
				exception_occured = false;
				try {
					cout << "Enter Account Number: ";
					cin >> accountnumber;
					do {
						exception_occured = false;
						cout << "Enter amount to withdraw: ";
						cin >> amount;
						try {
							acc = b.Withdraw(accountnumber, amount);
							cout << "-------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
							cout << "Amount " << amount << " is withdrawn from account " << accountnumber << "." << endl;
							cout << acc;

						}
						catch (MinimumBalance e)
						{
							cout << "MINIMUM BALANCE! Cannot withdraw " << amount << " to maintain minimum balance." << endl;
							exception_occured = true;
						}
						catch (InsufficientFunds e)
						{
							cout << "INSUFFICIENT FUNDS! Amount " << amount << " is more than balance." << endl;
							exception_occured = true;
						}

					} while (exception_occured);
				}
				catch (InvalidAccountNumber e)
				{
					cout << "Account " << accountnumber << " does not exist!" << endl;
					exception_occured = true;
				}
			} while (exception_occured);
			break;
		case 5:
			do {
				exception_occured = false;
				try {
					cout << "Enter Account Number: ";
					cin >> accountnumber;
					b.CloseAccount(accountnumber);

				}
				catch (InvalidAccountNumber e)
				{
					cout << "Account " << accountnumber << " does not exist!" << endl;
					exception_occured = true;
				}
			} while (exception_occured);
			break;
		case 6:
			b.ShowAllAccounts();
			break;
		case 7:
			break;
		default:
			cout << "Invalid choice! Enter correct choice.";
			break;
		}

	} while (choice != 7);
	if (choice == 7)
	{
		cout << "Thank you!" << endl;
		cout << "-------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
	}
	return 0;
}