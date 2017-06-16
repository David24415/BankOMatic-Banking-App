#include "Transducer.h"
#include <vector>
#include "misc.h"
using namespace std;


string Transducer::transduce(string command)
{
	try
	{
		string result;
		vector<string> token = tokenize(command);
		if (token.size() == 0) return "";
		if ((token[0] == "HELP") || (token[0] == "H"))
		{
			if (token.size() != 1) throw (string)"ERROR: Wrong number of parameters for this command.";
			result = "Commands:\n";
			result += "-------------------\n";
			result += "\tHELP(H)\n";
			result += "\tCLEAR\n";
			result += "\tQUIT(Q)\n";
			result += "-------------------\n";
			result += "\tADD_CUSTOMER(AC) <NAME>;<DOB>;<SS#>\n";
			result += "\tREMOVE_CUSTOMER(RC) <Customer#>\n";
			result += "\tFIND_CUSTOMER(FC) <Customer#>\n";
			result += "\tSHOW_CUSTOMER_LIST(SCL)\n";
			result += "\tTEST_ADD_CUSTOMERS(TAC) <numberOfTestCustomers>\n";
			result += "-------------------\n";
			result += "\tADD_ACCOUNT(AA) <Customer#>;<InitialAmmount>;<AccountType>\n";
			result += "\tREMOVE_ACCOUNT(RA) <Account#>\n";
			result += "\tFIND_ACCOUNT(FA) <Account#>\n";
			result += "\tSHOW_ACCOUNT_LIST(SAL)\n";
			result += "\tTEST_ADD_ACCOUNTS(TAA) <numberOfTestAccounts>\n";
			result += "-------------------\n";
			result += "\tMAKE_DEPOSIT(MD) <Account#>;<Amount>\n";
			result += "\tMAKE_WITHDRAWAL(MW) <Account#>;<Amount>\n";
			result += "\tMAKE_TRANSFER(MT) <SourceAccount#>; <DestinationAccount#>;<Amount>\n";
			result += "\tADD_CUSTOMER_TO_ACCOUNT(ACTA) <Customer#>;<Account#>\n";
			result += "\tGET_CUSTOMER_TOTAL_ASSETS(GCTA) <Customer#>\n";
			result += "\tREPORT_TOTAL_BANK_HOLDINGS(RTBH)\n";
			result += "\tLIST_CUSTOMERS_WITH_HOLDINGS_ABOVE (LCWHA) <Amount>\n";
			result += "-------------------\n";





		}
		else if ((token[0] == "QUIT") || (token[0] == "Q"))
		{
			if (token.size() != 1) throw (string)"ERROR: Wrong number of parameters for this command.";
			result = "Goodbye.";
		}
		else if (token[0] == "CLEAR")
		{
			if (token.size() != 1) throw (string)"ERROR: Wrong number of parameters for this command.";
			result = bank.clear();
		}
		else if ((token[0] == "ADD_CUSTOMER") || (token[0] == "AC"))
		{
			if (token.size() != 4) throw (string)"ERROR: Wrong number of parameters for this command.";
			result = "Customer added. Number = " + intToString(bank.addCustomer(token[1], token[2], token[3]));
		}
		else if ((token[0] == "REMOVE_CUSTOMER") || (token[0] == "RC"))
		{
			if (token.size() != 2) throw (string)"ERROR: Wrong number of parameters for this command.";
			result = bank.removeCustomer(stringToInt(token[1]));
		}
		else if ((token[0] == "FIND_CUSTOMER") || (token[0] == "FC"))
		{
			if (token.size() != 2) throw (string)"ERROR: Wrong number of parameters for this command.";
			result = bank.findCustomer(stringToInt(token[1]));
		}
		else if ((token[0] == "SHOW_CUSTOMER_LIST") || (token[0] == "SCL"))
		{
			if (token.size() != 1) throw (string)"ERROR: Wrong number of parameters for this command.";
			result = bank.getCustomerList();
		}
		else if ((token[0] == "TEST_ADD_CUSTOMERS") || (token[0] == "TAC"))
		{
			if (token.size() != 2) throw (string)"ERROR: Wrong number of parameters for this command.";
			result = bank.testAddCustomers(stringToInt(token[1]));
		}
		else if ((token[0] == "ADD_ACCOUNT") || (token[0] == "AA"))
		{
			if (token.size() != 4) throw (string)"ERROR: Wrong number of parameters for this command.";
			result = intToString(bank.addAccount(stringToInt(token[1]), dollarStringToInt(token[2]), token[3]));
		}
		else if ((token[0] == "REMOVE_ACCOUNT") || (token[0] == "RA"))
		{
			if (token.size() != 2) throw (string)"ERROR: Wrong number of parameters for this command.";
			result = bank.removeAccount(stringToInt(token[1]));
		}
		else if ((token[0] == "FIND_ACCOUNT") || (token[0] == "FA"))
		{
			if (token.size() != 2) throw (string)"ERROR: Wrong number of parameters for this command.";
			result = bank.findAccount(stringToInt(token[1]));
		}
		else if ((token[0] == "SHOW_ACCOUNT_LIST") || (token[0] == "SAL"))
		{
			if (token.size() != 1) throw (string)"ERROR: Wrong number of parameters for this command.";
			result = bank.getAccountList();;
		}
		else if ((token[0] == "TEST_ADD_ACCOUNTS") || (token[0] == "TAA"))
		{
			if (token.size() != 2) throw (string)"ERROR: Wrong number of parameters for this command.";
			result = bank.testAddAccounts(stringToInt(token[1]));
		}
		else if ((token[0] == "MAKE_DEPOSIT") || (token[0] == "MD"))
		{
			if (token.size() != 3) throw (string)"ERROR: Wrong number of parameters for this command.";
			result = bank.makeDeposit(stringToInt(token[1]), dollarStringToInt(token[2]));
		}
		else if ((token[0] == "MAKE_WITHDRAWAL") || (token[0] == "MW"))
		{
			if (token.size() != 3) throw (string)"ERROR: Wrong number of parameters for this command.";
			result = bank.makeWithdrawal(stringToInt(token[1]), dollarStringToInt(token[2]));
		}
		else if ((token[0] == "MAKE_TRANSFER") || (token[0] == "MT"))
		{
			if (token.size() != 4) throw (string)"ERROR: Wrong number of parameters for this command.";
			result = bank.Make_Transfer(stringToInt(token[1]), stringToInt(token[2]), dollarStringToInt(token[3]));
		}
		else if ((token[0] == "ADD_CUSTOMER_TO_ACCOUNT") || (token[0] == "ACTA"))
		{
			if (token.size() != 3) throw (string)"ERROR: Wrong number of parameters for this command.";
			result = bank.Add_Customer_To_Account(stringToInt(token[1]), stringToInt(token[2]));
		}
		else if ((token[0] == "GET_CUSTOMER_TOTAL_ASSETS") || (token[0] == "GCTA"))
		{
			if (token.size() != 2) throw (string)"ERROR: Wrong number of parameters for this command.";
			
			result = bank.Get_Customer_Total_Assets(token[1]);
		}	
		else if ((token[0] == "REPORT_TOTAL_BANK_HOLDINGS") || (token[0] == "RTBH"))
		{
			if (token.size() != 1) throw (string)"ERROR: Wrong number of parameters for this command.";
			result = bank.Report_Total_Bank_Holdings();
		}
		else if ((token[0] == "LIST_CUSTOMERS_WITH_HOLDINGS_ABOVE") || (token[0] == "LCWHA"))
		{
			if (token.size() != 2) throw (string)"ERROR: Wrong number of parameters for this command.";

			result = bank.List_Customers_With_Holdings_Above(dollarStringToInt(token[1]));
		}
		else
		{
			 throw (string)"ERROR: Unrecognized Command.";
		}
		return result;
	}
	catch (string s)
	{
		if (s == "FATAL ERROR") exit(999);
		return s;
	}
	catch (...)
	{
		return "Something went wrong but I don't know what!";
	}
}



