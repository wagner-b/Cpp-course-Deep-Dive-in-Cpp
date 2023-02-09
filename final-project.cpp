/*
BSD 3-Clause License

Copyright (c) 2023, Wagner Bertholdo Burghausen

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


/*
* This is the final project of my C++ course. Here I will develop
* a simulation of a simple banking system. The program should allow
* opening accounts, deleting accounts, changing the balance,
* displaying a particular account, and displaying all accounts.
* The program should also write the data on a file on persistent
* storage (like a database), and load this database when it starts.
*/


#include <iostream>
#include <fstream>
#include <string>
#include <map>

#define FILENAME "bankdb.txt"


class Account
{
private:
	std::string fullName;
	unsigned long accountNo;
	static unsigned long lastAccountNo;
	long double balance;

public:
	Account(){}
	Account(std::string name, long double balance)
	{
		lastAccountNo++;
		fullName = name;
		accountNo = lastAccountNo;
		this->balance = balance;
	}

	std::string getName(){return fullName;}
	unsigned long getAccountNo(){return accountNo;}
	long double getBalance(){return balance;}

	void deposit(long double d){balance += d;}
	void withdraw(long double w){balance -= w;}

	static unsigned long getLastAccountNo(){return lastAccountNo;}
	static void setLastAccountNo(unsigned long n){lastAccountNo = n;}

	friend std::ostream & operator<<(std::ostream &out, Account &acc);
	friend std::ofstream & operator<<(std::ofstream &ofs, Account &acc);
	friend std::ifstream & operator>>(std::ifstream &ifs, Account &acc);
};

unsigned long Account::lastAccountNo = 0;


std::ostream & operator<<(std::ostream &out, Account &acc)
{
	out << "Name: " << acc.fullName << "\n";
	out << "Account Number: " << acc.accountNo << "\n";
	out << "Balance: " << acc.balance << "\n";
	return out;
}


std::ofstream & operator<<(std::ofstream &ofs, Account &acc)
{
	ofs << acc.fullName << "\n";
	ofs << acc.accountNo << "\n";
	ofs << acc.balance << "\n";
	return ofs;
}


std::ifstream & operator>>(std::ifstream &ifs, Account &acc)
{
	std::getline(ifs, acc.fullName);
	ifs >> acc.accountNo >> acc.balance;
	ifs.ignore(); // clear '\n' in buffer
	return ifs;
}


void loadDiskData(std::map<unsigned long, Account> &memData)
{
	std::ifstream diskData(FILENAME);

	while(true)
	{
		Account currentAcc;
		if(!(diskData >> currentAcc))
			break;

		unsigned long accNo = currentAcc.getAccountNo();
		Account::setLastAccountNo(accNo);
		memData.insert(std::pair<unsigned long, Account>
			(accNo, currentAcc));
	}

	diskData.close();
}


void openAccount(std::map<unsigned long, Account> &memData)
{
	std::string name;
	long double balance;
	unsigned long accNo;
	std::ofstream diskData(FILENAME, std::ios::app);

	std::cout << "Enter full name: ";
	std::getline(std::cin, name);
	std::cout << "Enter balance: ";
	std::cin >> balance;
	std::cin.ignore(); // clear '\n' in buffer

	Account newAcc(name, balance);
	std::cout << "\nAccount created successfully!\n";
	std::cout << newAcc << "\n";

	accNo = newAcc.getAccountNo();
	memData.insert(std::pair<unsigned long, Account>
		(accNo, newAcc));
	diskData << newAcc;
	diskData.close();
}


void displayAccount(std::map<unsigned long, Account> data)
{
	unsigned long accNo;
	std::cout << "Type the account number: ";
	std::cin >> accNo;
	std::cin.ignore(); // clear '\n' in buffer
	std::cout << "\n" << data.at(accNo) << "\n";
}


void displayAllAccounts(std::map<unsigned long, Account> data)
{
	std::map<unsigned long, Account>::iterator it;

	std::cout << "\n";
	for(it = data.begin(); it != data.end(); it++)
		std::cout << it->second << "\n";
}


void writeDataToDisk(std::map<unsigned long, Account> &memData)
{
	std::ofstream diskData(FILENAME, std::ios::trunc);
	std::map<unsigned long, Account>::iterator it;

	for(it = memData.begin(); it != memData.end(); it++)
		diskData << it->second;

	diskData.close();
}


void depositToAccount(std::map<unsigned long, Account> &memData)
{
	unsigned long accNo;
	long double amount;

	std::cout << "Type the account number: ";
	std::cin >> accNo;
	std::cout << "Type the amount to deposit: ";
	std::cin >> amount;
	std::cin.ignore(); // clear '\n' in buffer

	memData.at(accNo).deposit(amount);
	writeDataToDisk(memData);

	std::cout << "\nDeposited " << amount << " to account ";
	std::cout << accNo << ":\n" << memData[accNo] << "\n";
}


void withdrawFromAccount(std::map<unsigned long, Account> &memData)
{
	unsigned long accNo;
	long double amount;

	std::cout << "Type the account number: ";
	std::cin >> accNo;
	std::cout << "Type the amount to withdraw: ";
	std::cin >> amount;
	std::cin.ignore(); // clear '\n' in buffer

	memData.at(accNo).withdraw(amount);
	writeDataToDisk(memData);

	std::cout << "\nWithdrawn " << amount << " from account ";
	std::cout << accNo << ":\n" << memData[accNo] << "\n";
}


void deleteAccount(std::map<unsigned long, Account> &memData)
{
	unsigned long accNo;

	std::cout << "Type the account number: ";
	std::cin >> accNo;
	std::cin.ignore(); // clear '\n' in buffer

	memData.at(accNo); // throws exception if out of range

	std::cout << "\nDeleted account number " << accNo;
	std::cout << ":\n" << memData[accNo] << "\n";

	memData.erase(accNo);
	writeDataToDisk(memData);
}


void printMenu()
{
	std::cout << "\nChoose an option below:\n";
	std::cout << "1 - Open an account\n";
	std::cout << "2 - Display account information\n";
	std::cout << "3 - Display all accounts\n";
	std::cout << "4 - Deposit to an account\n";
	std::cout << "5 - Withdraw from an account\n";
	std::cout << "6 - Delete an account\n";
	std::cout << "7 - Quit\n\n";
	std::cout << "Enter your choice [1 - 7]: ";
}


int main()
{
	short userChoice;
	std::map<unsigned long, Account> memoryData;
	loadDiskData(memoryData);

	std::cout << "\nWelcome to banking simulator!\n";

	do
	{
		printMenu();
		std::cin >> userChoice;
		std::cin.ignore(); // clear '\n' in buffer

		switch(userChoice)
		{
			case 1:
				openAccount(memoryData);
				break;

			case 2:
				displayAccount(memoryData);
				break;

			case 3:
				displayAllAccounts(memoryData);
				break;

			case 4:
				depositToAccount(memoryData);
				break;

			case 5:
				withdrawFromAccount(memoryData);
				break;

			case 6:
				deleteAccount(memoryData);
				break;

			case 7: break;

			default:
				std::cout << "Error! Please, type an ";
				std::cout << "integer between 1 and 7.\n";
		}
	}
	while(userChoice != 7);

	return 0;
}
