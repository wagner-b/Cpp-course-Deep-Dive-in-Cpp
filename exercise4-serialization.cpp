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
* This is a simple exercise demonstrating i/o stream serialization in C++.
* Here, I define the class Item which overloads the extraction and insertion
* operators to read/write the data of an Item object directly from/to a file
* on disk.
*/


#include <iostream>
#include <fstream>
#include <string>

class Item
{
private:
	std::string name;
	double price;
	unsigned int amount;

public:
	void setName(std::string n){name = n;}
	void setPrice(double p){price = p;}
	void setAmount(unsigned int a){amount = a;}

	friend std::ostream & operator<<(std::ostream &out, Item &i);
	friend std::ofstream & operator<<(std::ofstream &fout, Item &i);
	friend std::ifstream & operator>>(std::ifstream &fin, Item &i);
};


std::ostream & operator<<(std::ostream &out, Item &i)
{
	out << "Name: " << i.name << "\n";
	out << "Price: " << i.price << "\n";
	out << "Amount: " << i.amount << "\n";
	return out;
}


std::ofstream & operator<<(std::ofstream &fout, Item &i)
{
	fout << i.name << "\n";
	fout << i.price << "\n";
	fout << i.amount << "\n";
	return fout;
}


std::ifstream & operator>>(std::ifstream &fin, Item &i)
{
	std::getline(fin, i.name);
	fin >> i.price >> i.amount;
	fin.ignore(); // clear '\n' in buffer
	return fin;
}


void getUserData(Item &item)
{
	std::string name;
	double price;
	unsigned int amount;

	std::cout << "Enter name: ";
	std::getline(std::cin, name);

	std::cout << "Enter price: ";
	std::cin >> price;
	std::cin.ignore(); // clear '\n' in buffer

	std::cout << "Enter amount: ";
	std::cin >> amount;
	std::cin.ignore(); // clear '\n' in buffer

	item.setName(name);
	item.setPrice(price);
	item.setAmount(amount);
}


void writeItemListToDisk(std::ofstream &outfile)
{
	unsigned int nitems;

	std::cout << "Enter the number of items to add: ";
	std::cin >> nitems;
	std::cin.ignore(); // clear '\n' in buffer
	std::cout << std::endl;

	for(unsigned int n = 1; n <= nitems; n++)
	{
		Item currentItem;
		std::cout << "Enter data for item number " << n << "\n";
		getUserData(currentItem);
		outfile << currentItem;
		std::cout << std::endl;
	}
}


void readItemListFromDisk(std::ifstream &infile)
{
	unsigned int n = 0;

	while(true)
	{
		Item currentItem;

		if(!(infile >> currentItem))
			break;

		n++;
		std::cout << "Item number " << n << ":\n";
		std::cout << currentItem << "\n";
	}
}


int main()
{
	std::ofstream writeFile("item-list.txt");
	std::ifstream readFile("item-list.txt");

	writeItemListToDisk(writeFile);
	writeFile.close();

	readItemListFromDisk(readFile);
	readFile.close();

	return 0;
}
