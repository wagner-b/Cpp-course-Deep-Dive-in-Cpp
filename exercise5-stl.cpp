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
* This is a simple exercise using the vector data structure in C++.
* Here, I define the class Employee and use a vector to store objects of
* the class Employee. Unlike arrays, a vector can be expanded to store
* more elements than what its initial size would allow.
*/


#include <iostream>
#include <string>
#include <vector>

class Employee
{
private:
	std::string name, department;
	unsigned short age;
	double wage;

public:
	void setName(std::string n){name = n;}
	void setDepartment(std::string d){department = d;}
	void setAge(unsigned short a){age = a;}
	void setWage(double w){wage = w;}

	friend std::ostream & operator<<(std::ostream &out, Employee &emp);
};


std::ostream & operator<<(std::ostream &out, Employee &emp)
{
	out << "Name: " << emp.name << "\n";
	out << "Department: " << emp.department << "\n";
	out << "Age: " << emp.age << "\n";
	out << "Wage: " << emp.wage << "\n";
	return out;
}


void getUserData(Employee &emp)
{
	std::string name, department;
	unsigned short age;
	double wage;

	std::cout << "Enter name: ";
	std::getline(std::cin, name);
	std::cout << "Enter department: ";
	std::getline(std::cin, department);
	std::cout << "Enter age: ";
	std::cin >> age;
	std::cin.ignore(); // clear '\n' in buffer
	std::cout << "Enter wage: ";
	std::cin >> wage;
	std::cin.ignore(); // clear '\n' in buffer

	emp.setName(name);
	emp.setDepartment(department);
	emp.setAge(age);
	emp.setWage(wage);
}


void pushEmployees(std::vector<Employee> &EmployeeVector)
{
	unsigned int nEmp;
	std::cout << "Enter the number of employees to add: ";
	std::cin >> nEmp;
	std::cin.ignore(); // clear '\n' in buffer
	std::cout << std::endl;

	for(unsigned int n = 1; n <= nEmp; n++)
	{
		Employee currentEmployee;
		getUserData(currentEmployee);
		std::cout << std::endl;
		EmployeeVector.push_back(currentEmployee);
	}
}


void displayEmployees(std::vector<Employee> Employees)
{
	unsigned int n = 1;
	std::vector<Employee>::iterator itr;

	for(itr = Employees.begin(); itr != Employees.end(); itr++, n++)
	{
		std::cout << "Employee number " << n << ":\n";
		std::cout << *itr << "\n";
	}
}


int main()
{
	std::vector<Employee> myVector;

	pushEmployees(myVector);
	std::cout << "Enter more employees \n\n";
	pushEmployees(myVector);
	displayEmployees(myVector);

	return 0;
}
