#include<iostream>
#include<map>
#include"Account.h"
using namespace std;

class InvalidAccountNumber {};

class Bank
{
private:
	map<long, Account> accounts;
public:
	Bank();
	Account OpenAccount(string fname, string lname, float bal);
	Account BalanceEnquiry(long acn);
	Account Deposit(long acn, float amt);
	Account Withdraw(long acn, float amt);
	void CloseAccount(long acn);
	void ShowAllAccounts();
	~Bank();
};

Bank::Bank()
{
	Account account;
	ifstream infile;
	infile.open("Bank.data", ios::in);
	if (!infile.is_open())
	{
		return;
	}
	while (!infile.eof())
	{
		infile >> account;
		if (infile) {
			accounts.insert(pair<long, Account>(account.getAccNo(), account));

		}
	}
	Account::setLastAccountNumber(account.getAccNo());
	infile.close();
}

Account Bank::OpenAccount(string fname, string lname, float bal)
{
	ofstream outfile;
	Account account(fname, lname, bal);
	accounts.insert(pair<long, Account>(account.getAccNo(), account));
	outfile.open("Bank.data", ios::out | ios::trunc);
	map<long, Account>::iterator itr;
	for (itr = accounts.begin(); itr != accounts.end(); itr++)
	{
		outfile << itr->second;
	}
	outfile.close();
	return account;
}

Account Bank::BalanceEnquiry(long acn)
{
	map<long, Account>::iterator itr = accounts.find(acn);
	if (itr == accounts.end())
		throw InvalidAccountNumber();
	return itr->second;
}

Account Bank::Deposit(long acn, float amt)
{
	map<long, Account>::iterator itr = accounts.find(acn);
	if (itr == accounts.end())
		throw InvalidAccountNumber();
	itr->second.Deposit(amt);
	return itr->second;
}

Account Bank::Withdraw(long acn, float amt)
{
	map<long, Account>::iterator itr = accounts.find(acn);
	if (itr == accounts.end())
		throw InvalidAccountNumber();
	itr->second.Withdraw(amt);
	return itr->second;
}

void Bank::CloseAccount(long acn)
{
	map<long, Account>::iterator itr = accounts.find(acn);
	if (itr == accounts.end())
		throw InvalidAccountNumber();
	cout << "-------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "Account CLosed!" << endl << itr->second;
	accounts.erase(acn);
}

void Bank::ShowAllAccounts()
{
	int i = 0;
	if (accounts.empty())
		cout << "No Accounts!" << endl;
	else
	{
		map<long, Account>::iterator itr;
		for (itr = accounts.begin(); itr != accounts.end(); itr++)
		{
			i++;
			cout << i << ")" << itr->second << endl;


		}
	}
}

Bank::~Bank()
{
	ofstream outfile;
	outfile.open("Bank.data", ios::out | ios::trunc);
	if (!outfile.is_open())
	{

		return;
	}
	map<long, Account>::iterator itr;
	for (itr = accounts.begin(); itr != accounts.end(); itr++)
	{
		outfile << itr->second;

	}
	outfile.close();
}