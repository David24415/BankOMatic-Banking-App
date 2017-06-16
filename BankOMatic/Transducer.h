
#pragma once

#include <string>
#include "Bank.h"

using namespace std;




class Transducer
{
public:
	string transduce(string command);
private:
	//Add main functional object here 
	Bank bank;
};