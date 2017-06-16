#pragma once
#include <string>
#include <vector>
#include <set>
#include <map>
#include "Customer.h"
#include "Account.h"
#include "TomRandom.h"
using namespace std;


class Bank
{
public:
	friend class Account;
	Bank();
	~Bank();

	void readCustomerFile();
	void writeCustomerFile();

	void readAccountFile();
	void writeAccountFile();

	int addCustomer(string n, string b, string s);
	void addCustomerFromFile(int cusNum, string n, string b, string s);
	string removeCustomer(int cusNum);
	string findCustomer(int cusNum);
	string clear();
	string testAddCustomers(int numberOfTestCus);
	bool isCusNumberUsed(int cusNum);
	string getCustomerList();

	int addAccount(int cn, int ba, string ty);
	void addAccountFromFile(int an, string ty, int ba);

	bool isActNumberUsed(int actNum);
	string getAccountList();
	string removeAccount(int actNumToBeDeleted);
	Customer & getCustomerByCustomerNumber(int cusNum);
	string findAccount(int actNum);
	string testAddAccounts(int numberOfTestAct);

	Account & getAccountByAccountNumber(int actNum);

	string makeDeposit(int actNum, int ammount);
	string makeWithdrawal(int actNum, int ammount);
	string Make_Transfer(int SourceAcct, int DestinationAcct, int ammount);
	string Add_Customer_To_Account(int cusNum, int actNum);
	string Get_Customer_Total_Assets(string cusNum);
	string Report_Total_Bank_Holdings();
	string List_Customers_With_Holdings_Above(int amnt);


	string getFormatedCustomerString(int cusNum);
	string getFormatedAccountString(int actNum);



private:
	TomRandom random;
	vector<Customer> vCustomer;
	map<int, int> indexByCustomerNumber;
	// We can use the map indexByCustomerNumber instead of the set
	//set<int> setOfUsedCusNumbers;

	vector<Account> vAccount;
	map<int, int> indexByAccountNumber;

};

