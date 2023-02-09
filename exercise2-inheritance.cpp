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
* This is a simple exercise about class inheritance in C++.
* Here I use multilevel inheritance with 3 classes, and I create
* only 1 object in the main function (employee1), which can access and
* modify values from all 3 classes with the help of functions.
*/


#include <iostream>
#include <string>

class Employee
{
private:
	std::string name;
	unsigned int id;

public:
	void setEmployee();
	void displayEmployee();
};


// EmployeeDept class inherits from Employee class

class EmployeeDept : public Employee
{
private:
	std::string deptName;
	std::string employeePosition;

public:
	void setEmployeeDept();
	void displayEmployeeDept();
};


// EmployeeDeptWage class inherits from EmployeeDept class

class EmployeeDeptWage : public EmployeeDept
{
private:
	double wage;

public:
	void setEmployeeWage();
	void displayEmployeeWage();
};


// Class functions

void Employee::setEmployee()
{
	std::cout << "Enter employee name: ";
	std::getline(std::cin, name);
	std::cout << "Enter employee id number: ";
	std::cin >> id;
	std::cin.ignore(); // clear '\n' char in buffer
}


void Employee::displayEmployee()
{
	std::cout << "Employee name: " << name << std::endl;
	std::cout << "Employee id: " << id << std::endl;
}


void EmployeeDept::setEmployeeDept()
{
	std::cout << "Enter employee department: ";
	std::getline(std::cin, deptName);
	std::cout << "Enter employee job / position: ";
	std::getline(std::cin, employeePosition);
}


void EmployeeDept::displayEmployeeDept()
{
	std::cout << "Department: " << deptName << std::endl;
	std::cout << "Job: " << employeePosition << std::endl;
}


void EmployeeDeptWage::setEmployeeWage()
{
	std::cout << "Enter employee monthly wage: ";
	std::cin >> wage;
	std::cin.ignore(); // clear '\n' char in buffer
}


void EmployeeDeptWage::displayEmployeeWage()
{
	std::cout << "Monthly wage: ";
	std::printf("%.2lf", wage);
	std::cout << std::endl;
}


int main()
{
	EmployeeDeptWage employee1;

	employee1.setEmployee();
	employee1.setEmployeeDept();
	employee1.setEmployeeWage();

	std::cout << std::endl;

	employee1.displayEmployee();
	employee1.displayEmployeeDept();
	employee1.displayEmployeeWage();

	return 0;
}
