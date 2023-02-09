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
*   This is a simple exercise demonstrating polymorphism in C++.
* Here I show the advantages of runtime polymorphism. The program can
* call functions from different classes at runtime, while using the
* same function names and the same base class pointer in main function.
* It all depends on the object the base class pointer is pointing to.
*
*   I also make sure to free the memory allocated on heap, to prevent
* memory leaks.
*/


#include <iostream>

#define PI 3.14159

// Abstract base class with only pure virtual functions
class Shape
{
public:
	virtual ~Shape(){}
	virtual double area() = 0;
	virtual double perimeter() = 0;
	virtual void getUserData() = 0;
};


// Inherits from Shape and overrides virtual functions
class Circle : public Shape
{
private:
	double radius;

public:
	Circle(double r = 0.0)
	{
		if(r > 0)
			radius = r;
	}

	double area(){return PI * radius * radius;}
	double perimeter(){return 2 * PI * radius;}
	void getUserData();
};


// Also inherits from Shape and overrides virtual functions
class Rectangle : public Shape
{
private:
	double length;
	double breadth;

public:
	Rectangle(double l = 0.0, double b = 0.0)
	{
		if(l > 0 && b > 0)
		{
			length = l;
			breadth = b;
		}
	}

	double area(){return length * breadth;}
	double perimeter(){return (breadth + length) * 2;}
	void getUserData();
};


// Functions to get data from user
void Circle::getUserData()
{
	double r = 0.0;
	std::cout << "Enter the data for the circle\n";
	std::cout << "Radius: ";
	std::cin >> r;

	if(r > 0)
		radius = r;
}


void Rectangle::getUserData()
{
	double l = 0.0, b = 0.0;
	std::cout << "Enter the data for the rectangle\n";
	std::cout << "Length: "; std::cin >> l;
	std::cout << "Breadth: "; std::cin >> b;

	if(l > 0 && b > 0)
	{
		length = l;
		breadth = b;
	}
}


int main()
{
	// Base class pointer (Shape), derived class object (Circle)
	Shape *ptrShape = new Circle(); // allocated dynamically on the heap
	ptrShape->getUserData(); // will call Circle::getUserData

	std::cout << "Area of circle is: " << ptrShape->area() << "\n";
	std::cout << "Perimeter of circle is: " << ptrShape->perimeter() << "\n\n";

	// free the memory here, or the program will leak memory
	delete ptrShape;

	// ptrShape is now pointing to a Rectangle object
	ptrShape = new Rectangle(); // allocated dynamically on the heap
	ptrShape->getUserData(); // will call Rectangle::getUserData

	std::cout << "Area of rectangle is: " << ptrShape->area() << "\n";
	std::cout << "Perimeter of rectangle is: " << ptrShape->perimeter() << "\n";

	// free the memory here, or the program will leak memory
	delete ptrShape;

	ptrShape = nullptr;

	return 0;
}
