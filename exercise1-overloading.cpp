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
* This is a simple exercise to create a class and overload operators in C++.
* Here I define the class Rational and overload the 4 basic operations,
* as well as the insertion operator (to print the object using std::cout).
*
* The user types the values for the numerator and denominator of 2 rational
* numbers, and then the program outputs the results of the 4 basic operations
* between those numbers provided by the user.
*/


#include <iostream>

class Rational
{
private:
	int p;
	int q;

public:
	Rational(int numerator = 0, int denominator = 1)
	{
		setP(numerator);
		setQ(denominator);
	}

	Rational(Rational &r)
	{
		this->p = r.p;
		this->q = r.q;
	}


	int getP(){return p;}
	int getQ(){return q;}

	void setP(int numerator);
	void setQ(int denominator);

	Rational operator+(Rational r);
	Rational operator-(Rational r);
	Rational operator*(Rational r);
	Rational operator/(Rational r);

	friend std::ostream & operator<<(std::ostream &out, Rational &r);
};


void Rational::setP(int numerator){p = numerator;}

void Rational::setQ(int denominator)
{
	if(denominator == 0)
	{
		std::cout << "Error! Denominator can not be zero! Setting it to 1.\n";
		q = 1;
	}
	else
		q = denominator;
}


Rational Rational::operator+(Rational r)
{
	Rational sum;
	sum.p = (this->p * r.q) + (this->q * r.p);
	sum.q = this->q * r.q;
	return sum;
}


Rational Rational::operator-(Rational r)
{
	Rational sub;
	sub.p = (this->p * r.q) - (this->q * r.p);
	sub.q = this->q * r.q;
	return sub;
}


Rational Rational::operator*(Rational r)
{
	Rational prod;
	prod.p = this->p * r.p;
	prod.q = this->q * r.q;
	return prod;
}


Rational Rational::operator/(Rational r)
{
	Rational div;

	if(r.p == 0)
	{
		std::cout << "Error! Division by " << r << " is not possible!\n";
		std::cout << "Result object is returned as " << div << std::endl;
	}
	else
	{
		div.p = this->p * r.q;
		div.q = this->q * r.p;
	}

	return div;
}


std::ostream & operator<<(std::ostream &out, Rational &r)
{
	out<<r.p<<'/'<<r.q;
	return out;
}


int main()
{
	Rational r1, r2, rSum, rSubtr, rProd, rDiv;
	int r1p, r1q, r2p, r2q;

	std::cout << "Enter numerator (p) for the 1st rational number: ";
	std::cin >> r1p;
	std::cout << "Enter denominator (q) for the 1st rational number: ";
	std::cin >> r1q;
	std::cout << "Enter numerator (p) for the 2nd rational number: ";
	std::cin >> r2p;
	std::cout << "Enter denominator (q) for the 2nd rational number: ";
	std::cin >> r2q;

	std::cout << std::endl;

	r1.setP(r1p); r1.setQ(r1q); r2.setP(r2p); r2.setQ(r2q);

	rSum = r1 + r2;
	std::cout << r1 << " plus " << r2 << " equals " << rSum << "\n";

	rSubtr = r1 - r2;
	std::cout << r1 << " minus " << r2 << " equals " << rSubtr << "\n";

	rProd = r1 * r2;
	std::cout << r1 << " times " << r2 << " equals " << rProd << "\n";

	rDiv = r1 / r2;
	std::cout << r1 << " divided by " << r2 << " equals " << rDiv << "\n";

	return 0;
}
