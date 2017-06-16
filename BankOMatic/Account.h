#pragma once
#include <string>
#include <vector>

using namespace std;


//class Bank;

class Account
{

public:
	friend class Bank;
	Account();
	string makeFormatedSimpleString();
	string makeDataString();

private:

	bool isDeleted;
	int balance;  // kept as the number of pennies in the account
	int accountNumber;
	string accountType;  // "Checking" or "Savings"
	vector<int> customerNumbers;
};
