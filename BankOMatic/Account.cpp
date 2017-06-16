#include "Account.h"
#include "misc.h"
#include "Bank.h"



Account::Account()
{
	isDeleted = false;
}

//string Account::makeFormatedString(Bank * pBank)
//{
//	string result;
//	result += padLeft(intToString(accountNumber), '0', 9) + " ";
//	result += padRight(accountType, ' ', 10) + " ";
//	result += padRight(intToDollarString(balance), ' ', 12) + " ";
//	for each(int cn in customerNumbers)
//	{
//		result += padRight(intToString(cn), ' ', 12) + " ";
//		//string cusName = ((*pBank).vCustomer[((*pBank).indexByCustomerNumber[cn])]).name;
//		string cusName = "(" + ((*pBank).getCustomerByCustomerNumber(cn)).name + ") ";
//		result += cusName;
//	}
//	result += "\n";
//
//	return result;
//}
string Account::makeFormatedSimpleString()
{
	string result;
	result += padLeft(intToString(accountNumber), '0', 9) + " ";
	result += padRight(accountType, ' ', 10) + " ";
	result += padRight(intToDollarString(balance), ' ', 12) + " ";
	result += "\n";

	return result;
}

string Account::makeDataString()
{
	string result;
	result += intToString(accountNumber) + " ";
	result += accountType + ";";
	result += intToDollarString(balance);
	for each (int cn in customerNumbers)
	{
		result += ";"+intToString(cn);
	}
	return result;
}