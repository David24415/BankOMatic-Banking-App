#include "Bank.h"

#include "misc.h"

#include <fstream>

using namespace std;

//string Bank::getCustomerList()
//{
//	string result;
//	for (int i = 0; i < vCustomer.size(); i++)
//	{
//		result += vCustomer[i].name + "\n";
//	}
//	return result;
//}

Bank::Bank()
{
	random.setSeed(999);
	readCustomerFile();
	readAccountFile();
}

void Bank::readCustomerFile()
{
	string iLine;
	ifstream iFile;
	iFile.open("cust0000.txt");
	while (!iFile.eof())
	{
		getline(iFile, iLine);
		vector<string> field = tokenize(iLine);
		if (field.size() >= 4)
		{
			addCustomerFromFile(stringToInt(field[0]), field[1], field[2], field[3]);
			for (int i = 4; i < field.size(); i++)
			{
				(*(vCustomer.end() - 1)).accountNumbers.push_back(stringToInt(field[i]));
			}
		}
	}
	iFile.close();
}

void Bank::readAccountFile()
{
	string iLine;
	ifstream iFile;
	iFile.open("acnt0000.txt");
	while (!iFile.eof())
	{
		getline(iFile, iLine);
		vector<string> field = tokenize(iLine);
		if (field.size() >= 3)
		{
			addAccountFromFile(stringToInt(field[0]),field[1],dollarStringToInt(field[2]));
			for (int i = 3; i < field.size(); i++)
			{
				(*(vAccount.end() - 1)).customerNumbers.push_back(stringToInt(field[i]));
			}
		}
	}
	iFile.close();
}

Bank::~Bank()
{
	writeCustomerFile();
	writeAccountFile();
}

void Bank::writeCustomerFile()
{
	ofstream oFile;
	oFile.open("cust0000.txt");
	for each(Customer c in vCustomer)
	{
		if (!c.isDeleted) oFile << c.makeDataString() << endl;
	}
	oFile.close();
}

void Bank::writeAccountFile()
{
	ofstream oFile;
	oFile.open("acnt0000.txt");
	for each(Account a in vAccount)
	{
		if (!a.isDeleted) oFile << a.makeDataString() << endl;
	}
	oFile.close();
}

string Bank::clear()
{
	vCustomer.clear();
	indexByCustomerNumber.clear();
	vAccount.clear();
	indexByAccountNumber.clear();
	return "All customers cleared.";
}

string Bank::testAddCustomers(int numberOfTestCus)
{
	for (int i = 0; i < numberOfTestCus; i++)
	{
		string name = randString(5) + " " + randString(10);
		string bDay = randNumberString(6);
		string SSnum = randNumberString(9);
		addCustomer(name, bDay, SSnum);
	}
	return intToString(numberOfTestCus) + " random customers added.";
}

string Bank::testAddAccounts(int numberOfTestAct)
{
	if (vCustomer.size() == 0) throw (string)"Error: There must be some customers before TEST_ADD_ACCOUNTS is used.";
	for (int i = 0; i < numberOfTestAct; i++)
	{
		int randCusIndex = randInt(0, (int)vCustomer.size());
		int cusNumber = vCustomer[randCusIndex].customerNumber;
		int balance = randInt(0, 5000) * 100 + 50;
		string aType;
		switch (randInt(0, 2))
		{
		case 0:
			aType = "Checking";
			break;
		case 1:
			aType = "Savings";
			break;
		}
		addAccount(cusNumber, balance, aType);
	}
	return intToString(numberOfTestAct) + " random accounts added.";
}

string Bank::getCustomerList()
{
	string result;

	result += "\n";

	result += padRight("Customer#", '.', 9) + " ";
	result += padRight("Name", '.', 20) + " ";
	result += padRight("Birthdate", '.', 12) + " ";
	result += padRight("SS#", '.', 12) + "\n";

	result += padRight("", '_', 9) + " ";
	result += padRight("", '_', 20) + " ";
	result += padRight("", '_', 12) + " ";
	result += padRight("", '_', 12) + "\n";


	// by going through the index map instead of the vCustomer we display them in order.
	for each(pair<int, int> p in indexByCustomerNumber)
	{
		try
		{
			result += getFormatedCustomerString(p.first);
		}
		catch (string es)
		{
			// if they are deleted
			if (matchFirst("Error: Previously Deleted Customer#", es))
			{
				//do nothing
			}
			else
			{
				throw es;
			}
		}
	}

	result += padRight("", '_', 9) + " ";
	result += padRight("", '_', 20) + " ";
	result += padRight("", '_', 12) + " ";
	result += padRight("", '_', 12) + "\n";

	return result;
}

string Bank::getAccountList()
{
	string result;

	result += "\n";

	result += padRight("Account#", '.', 9) + " ";
	result += padRight("Type", '.', 10) + " ";
	result += padRight("Balance", '.', 12) + "\n";

	result += padRight("", '_', 9) + " ";
	result += padRight("", '_', 10) + " ";
	result += padRight("", '_', 12) + "\n";


	// by going through the index map instead of the vCustomer we display them in order.
	for each(pair<int, int> p in indexByAccountNumber)
	{
		try
		{
			result += getFormatedAccountString(p.first);
		}
		catch (string es)
		{
			// if they are deleted
			if (matchFirst("Error: Previously Deleted Account#", es))
			{
				//do nothing
			}
			else
			{
				throw es;
			}

		}
	}

	result += padRight("", '_', 9) + " ";
	result += padRight("", '_', 10) + " ";
	result += padRight("", '_', 12) + "\n";

	return result;
}

//string Bank::getCustomerList()
//{
//	string result;
//	result += "\n";
//	result += padRight("Customer#", '.', 12) + " " +
//		padRight("Name", '.', 22) + " " +
//		padRight("Birthdate", '.', 12) + " " +
//		padRight("SS#", '.', 12) +
//		"\n";
//	result += padRight("", '_', 12) + " " +
//		padRight("", '_', 22) + " " +
//		padRight("", '_', 12) + " " +
//		padRight("", '_', 12) +
//		"\n";
//
//	for each(Customer c in vCustomer)
//	{
//
//		result +=	padRight(intToString(c.customerNumber),' ',12) +" "+
//					padRight(c.name, ' ', 22) + " " +
//					padRight(c.birthdate, ' ', 12) + " " +
//					padRight(c.SSnumber, ' ', 12) +
//					"\n";
//	}
//	result += padRight("", '_', 12) + " " +
//		padRight("", '_', 22) + " " +
//		padRight("", '_', 12) + " " +
//		padRight("", '_', 12) +
//		"\n";
//	return result;
//}

int Bank::addCustomer( 	string n,	string b, 	string s)
{
	Customer c;
	c.name = n;
	c.birthdate = b;
	c.SSnumber = s;

	//c.customerNumber = rand();

	int newCusNumber;

	do
	{
		newCusNumber = random.getInt(10000, 100010000);
	} while (isCusNumberUsed(newCusNumber));

	//setOfUsedCusNumbers.insert(newCusNumber);
	indexByCustomerNumber[newCusNumber] = (int)vCustomer.size();

	c.customerNumber = newCusNumber;
	vCustomer.push_back(c);
	return c.customerNumber;
}
string Bank::Add_Customer_To_Account(int cusNum, int actNum)
{

	Customer & cusToAdd = getCustomerByCustomerNumber(cusNum);
	Account & addToacct = getAccountByAccountNumber(actNum);
	addToacct.customerNumbers.push_back(cusNum);

	return "Customer #: " + intToString(cusNum)+" was added to account #: "+intToString(actNum);
		
}
string Bank::Get_Customer_Total_Assets(string cusNum)
{
	int cus = stringToInt(cusNum);
	int Total=0;
	Customer &AllAccs = getCustomerByCustomerNumber(cus);
	
	for (int i = 0;i<AllAccs.accountNumbers.size();i++)
	{
		Account &Accs = getAccountByAccountNumber(AllAccs.accountNumbers[i]);
		Total += Accs.balance;
	}
	
	return " the total of all accounts for customer #: " + intToString(cus) + " is equal to $" +(intToDollarString(Total));
}

string Bank::Report_Total_Bank_Holdings()
{
	
	int Total = 0;
	int num=0;

	for (int i = 0; i<vAccount.size(); i++)
	{
		Account &Accs = vAccount[i]; 
		Total += Accs.balance;
	}

	return " The total balance of all accounts in the bank is: $" + (intToDollarString(Total));
}
string Bank::List_Customers_With_Holdings_Above(int amnt)
{
	string higherThan;
	int totalAm = 0;

	for (int i = 0; i < vCustomer.size(); i++)
	{
		for (int x = 0; x < vCustomer[i].accountNumbers.size(); x++)
		{
			Account& currAcc = getAccountByAccountNumber(vCustomer[i].accountNumbers[x]);
			totalAm += currAcc.balance;
		}
		if (totalAm >amnt)
		{
			higherThan += getFormatedCustomerString(vCustomer[i].customerNumber);
		}

		totalAm = 0;
	}

	return "Customers with account balance higher than $"+ intToDollarString(amnt)+ ":\n" + higherThan;
}




void Bank::addCustomerFromFile(int cusNum,	string n,	string b,	string s)
{
	Customer c;
	c.name = n;
	c.birthdate = b;
	c.SSnumber = s;
	c.customerNumber = cusNum;
	//setOfUsedCusNumbers.insert(cusNum);
	indexByCustomerNumber[cusNum] = (int)vCustomer.size();
	vCustomer.push_back(c);
}

//bool Bank::isCusNumberUsed(int cusNum)
//{
//	vector<Customer>::iterator iter;
//	iter = vCustomer.begin();
//	while (iter != vCustomer.end())
//	{
//		if ((*iter).customerNumber == cusNum)
//		{
//			return true;
//		}
//		iter++;
//	}
//	return false;
//}

bool Bank::isCusNumberUsed(int cusNum)
{
	map<int, int>::iterator findIter;
	findIter = indexByCustomerNumber.find(cusNum);
	if (findIter != indexByCustomerNumber.end()) return true;
	return false;
}

bool Bank::isActNumberUsed(int actNum)
{
	map<int, int>::iterator findIter;
	findIter = indexByAccountNumber.find(actNum);
	if (findIter != indexByAccountNumber.end()) return true;
	return false;
}

//string Bank::removeCustomer(int cusNumToBeDeleted)
//{
//	string result;
//	vector<Customer>::iterator iter;
//	iter = vCustomer.begin();
//	while (iter != vCustomer.end())
//	{
//		if ((*iter).customerNumber == cusNumToBeDeleted)
//		{
//			result = (*iter).name + " was deleted";
//			vCustomer.erase(iter);
//			return result;
//		}
//		iter++;
//	}
//
//	result = "No vCustomer with number " + intToString(cusNumToBeDeleted) + " was found.";
//	return result;
//}
//string Bank::removeCustomer(int cusNumToBeDeleted)
//{
//	map<int, int>::iterator iter;
//	iter = indexByCustomerNumber.find(cusNumToBeDeleted);
//	if (iter == indexByCustomerNumber.end()) return "No customer with number " + intToString(cusNumToBeDeleted) + " was found.";
//	vCustomer[(*iter).second].isDeleted = true;
//	return vCustomer[(*iter).second].name + " was deleted";
//}

string Bank::removeCustomer(int cusNumToBeDeleted)
{
	Customer & cus = getCustomerByCustomerNumber(cusNumToBeDeleted);
	cus.isDeleted = true;
	return cus.name + "[" + intToString(cusNumToBeDeleted) + "] was deleted.";
}
//string Bank::removeAccount(int actNumToBeDeleted)
//{
//	map<int, int>::iterator iter;
//	iter = indexByAccountNumber.find(actNumToBeDeleted);
//	if (iter == indexByAccountNumber.end()) return "No accouunt with number " + intToString(actNumToBeDeleted) + " was found.";
//	vAccount[(*iter).second].isDeleted = true;
//	return "Account was deleted.";
//}
string Bank::removeAccount(int actNumToBeDeleted)
{
	Account & acc = getAccountByAccountNumber(actNumToBeDeleted);
	acc.isDeleted = true;
	for each(int cn in acc.customerNumbers)
	{
		Customer & cus = getCustomerByCustomerNumber(cn);
		cus.removeAccountNumber(actNumToBeDeleted);
	}
	return "Account [" + intToString(actNumToBeDeleted) + "] was deleted.";
}

// sequential search is slow
//string Bank::findCustomer(int cusNum)
//{
//	string result;
//	vector<Customer>::iterator iter;
//	iter = vCustomer.begin();
//	while (iter != vCustomer.end())
//	{
//		if ((*iter).customerNumber == cusNum)
//		{
//			result = (*iter).makeFormatedString();
//			return result;
//		}
//		iter++;
//	}
//
//	result = "No vCustomer with number " + intToString(cusNum) + " was found.";
//	return result;
//}

// requires two lookups
//string Bank::findCustomer(int cusNum)
//{
//	if (!isCusNumberUsed(cusNum)) return "No customer with number " + intToString(cusNum) + " was found.";
//	return vCustomer[indexByCustomerNumber[cusNum]].makeFormatedString();
//}

string Bank::findCustomer(int cusNum)
{
	//map<int, int>::iterator iter;
	//iter = indexByCustomerNumber.find(cusNum);
	//if ((iter == indexByCustomerNumber.end()) || (vCustomer[(*iter).second].isDeleted))
	//{
	//	return "No customer with number " + intToString(cusNum) + " was found.";
	//}
	//return vCustomer[(*iter).second].makeFormatedString();
	return getFormatedCustomerString(cusNum);
}

string Bank::findAccount(int actNum)
{
	return getFormatedAccountString(actNum);
}

int Bank::addAccount(int cn, int ba, string ty)
{
	if (!isCusNumberUsed(cn)) throw("Customer number " + intToString(cn) + " was not found.");
	Account a;


	a.customerNumbers.push_back(cn);
	a.balance = ba;
	a.accountType = ty;


	int newActNumber;

	do
	{
		newActNumber = random.getInt(10000, 100010000);
	} while (isActNumberUsed(newActNumber));

	indexByAccountNumber[newActNumber] = (int)vAccount.size();

	getCustomerByCustomerNumber(cn).accountNumbers.push_back(newActNumber);

	a.accountNumber = newActNumber;
	vAccount.push_back(a);
	return newActNumber;
}

void Bank::addAccountFromFile(int an, string ty, int ba)
{
	Account a;

	a.accountNumber = an;
	a.balance = ba;
	a.accountType = ty;
	indexByAccountNumber[an] = (int)vAccount.size();
	vAccount.push_back(a);
}

Customer & Bank::getCustomerByCustomerNumber(int cusNum)
{
	map<int, int>::iterator findIter;
	findIter = indexByCustomerNumber.find(cusNum);
	if (findIter == indexByCustomerNumber.end()) throw "Error: Unfound Customer# " + intToString(cusNum);
	if (vCustomer[(*findIter).second].isDeleted)throw  "Error: Previously Deleted Customer# " + intToString(cusNum);
	return vCustomer[(*findIter).second];
}

Account & Bank::getAccountByAccountNumber(int actNum)
{
	// if (!isActNumberUsed(actNum)) throw "Account Number " + intToString(actNum) + " was not found.";
	// return vAccount[indexByAccountNumber[actNum]];

	// We are doing this crap instead of the line above so we don't have to search for the actNum twice.
	map<int, int>::iterator findIter;
	findIter = indexByAccountNumber.find(actNum);
	if (findIter == indexByAccountNumber.end()) throw "Error: Unfound Account# " + intToString(actNum);
	if (vAccount[(*findIter).second].isDeleted) throw "Error: Previously Deleted Account# " + intToString(actNum);
	return vAccount[(*findIter).second];
}

string Bank::makeDeposit(int actNum, int ammount)
{
	Account & act = getAccountByAccountNumber(actNum);
	act.balance += ammount;
	return intToDollarString(ammount) + " deposit was made to Account# " + intToString(actNum) + " New balance: " + intToDollarString(act.balance);
}
string Bank::makeWithdrawal(int actNum, int ammount)
{
	Account & act = getAccountByAccountNumber(actNum);

	if (act.balance-ammount < 0)
	{
		"insufficient funds for transaction to be completed/n";
		return "withdrawal of amount: $" + intToDollarString(ammount) +
			" could not be made\n"+"Your current balance for account# " +
			intToString(actNum) + " is: $" + intToDollarString(act.balance);
	}else
		act.balance -= ammount;
	return intToDollarString(ammount) + " withdrawal was made from Account# " + intToString(actNum) + " New balance: " + intToDollarString(act.balance);
}
string Bank::Make_Transfer(int SourceAcct,int DestinationAcct,int ammount)
{
	Account & sourceAct = getAccountByAccountNumber(SourceAcct);
	Account & destinationAct = getAccountByAccountNumber(DestinationAcct);

	if (sourceAct.balance - ammount < 0)
	{
		"Insufficient funds in source account";
	}
	else
		sourceAct.balance -= ammount;
		destinationAct.balance += ammount;
		return "$"+intToDollarString(ammount) + " was transferred from account#: " + 
				intToString(SourceAcct) + " to account#: " + intToString(DestinationAcct);

}

string Bank::getFormatedCustomerString(int cusNum)
{
	Customer cus = getCustomerByCustomerNumber(cusNum);

	string result;
	result = cus.makeFormatedSimpleString();
	for each(int aNum in cus.accountNumbers)
	{
		Account a = getAccountByAccountNumber(aNum);
		result += "\t" + a.makeFormatedSimpleString();
	}
	result += "\n";
	return result;
}

string Bank::getFormatedAccountString(int actNum)
{
	Account act = getAccountByAccountNumber(actNum);

	string result;
	result = act.makeFormatedSimpleString();
	for each(int cNum in act.customerNumbers)
	{
		Customer cus = getCustomerByCustomerNumber(cNum);
		result += "\t" + cus.makeFormatedSimpleString();
	}
	result += "\n";
	return result;
}
