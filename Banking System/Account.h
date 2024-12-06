#include<iostream>
#include<fstream>
using namespace std;

#define MIN_BALANCE 500

class InsufficientFunds { };
class MinimumBalance {};

class Account
{
private:
	long accountNumber;
	string firstName, lastName;
	float balance;
	static long NextAccountNumber;
public:
	Account() {}
	Account(string fname, string lname, float bal);
	long getAccNo()
	{
		return accountNumber;
	}
	string getFirstName()
	{
		return firstName;
	}
	string getLastName()
	{
		return lastName;
	}
	float getBalance()
	{
		return balance;
	}
	void Deposit(float amt);
	void Withdraw(float amt);
	static void setLastAccountNumber(long accountNumber);
	static long getLastAccountNumber();
	friend ofstream& operator<<(ofstream& ofs, Account& acc);
	friend ifstream& operator>>(ifstream& ifs, Account& acc);
	friend ostream& operator<<(ostream& os, Account& acc);
};

long Account::NextAccountNumber = 0;

void Account::setLastAccountNumber(long accountNumber)
{
	NextAccountNumber = accountNumber;
}

long Account::getLastAccountNumber()
{
	return NextAccountNumber;
}

Account::Account(string fname, string lname, float bal)
{
	NextAccountNumber++;
	accountNumber = NextAccountNumber;
	firstName = fname;
	lastName = lname;
	balance = bal;
}

void Account::Deposit(float amt)
{
	balance += amt;
}

void Account::Withdraw(float amt)
{
	if (balance - amt < MIN_BALANCE)
	{
		if (amt > balance)
			throw InsufficientFunds();
		else
			throw MinimumBalance();
	}

	balance -= amt;
}

ofstream& operator<<(ofstream& ofs, Account& acc)
{
	ofs << acc.accountNumber << endl;
	ofs << acc.firstName << endl;
	ofs << acc.lastName << endl;
	ofs << acc.balance << endl;
	return ofs;
}

ifstream& operator>>(ifstream& ifs, Account& acc)
{
	ifs >> acc.accountNumber;
	ifs >> acc.firstName;
	ifs >> acc.lastName;
	ifs >> acc.balance;
	return ifs;
}

ostream& operator<<(ostream& os, Account& acc)
{
	os << "First Name: " << acc.getFirstName() << endl;
	os << "Last Name: " << acc.getLastName() << endl;
	os << "Account Number: " << acc.getAccNo() << endl;
	os << "Balance: " << acc.getBalance() << endl;
	os << "-------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
	return os;
}