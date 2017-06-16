#include "Customer.h"
#include "misc.h"
#include "Account.h"
#include "Bank.h"
#include <algorithm>

using namespace std;



Customer::Customer()
{
	isDeleted = false;
}

//string Customer::makeFormatedString(Bank * pBank)
//{
//	string result;
//	result += padLeft(intToString(customerNumber), '0', 9) + " ";
//	result += padRight(name, ' ', 20) + " ";
//	result += padRight(birthdate, ' ', 12) + " ";
//	result += padRight(SSnumber, ' ', 12) + "\n";
//	for each(int aNum in accountNumbers)
//	{
//		Account a = (*pBank).getAccountByAccountNumber(aNum);
//		if (!a.isDeleted)
//		{
//			result += "\t" + intToString(aNum) + " ";
//			result += a.accountType + " " + intToDollarString(a.balance) + "\n";
//		}
//	}
//	result += "\n";
//	return result;
//}

string Customer::makeFormatedSimpleString()
{
	string result;
	result += padLeft(intToString(customerNumber), '0', 9) + " ";
	result += padRight(name, ' ', 20) + " ";
	result += padRight(birthdate, ' ', 12) + " ";
	result += padRight(SSnumber, ' ', 12) + " ";
	result += "\n";
	return result;
}

string Customer::makeDataString()
{
	string result;
	result += intToString(customerNumber) + " ";
	result += name + ";";
	result += birthdate + ";";
	result += SSnumber;
	for each (int an in accountNumbers)
	{
		result += ";" + intToString(an);
	}
	return result;
}

void Customer::removeAccountNumber(int actNum)
{
	vector<int>::iterator iter = find(accountNumbers.begin(), accountNumbers.end(), actNum);
	if (iter != accountNumbers.end()) accountNumbers.erase(iter);
}
