#pragma once
#include <string>
#include <iostream>

class ComplexNumber {
public:
	ComplexNumber(double re, double im);
	double getReal() const;
	double getImg() const;
	std::string to_string();

	ComplexNumber operator +(ComplexNumber a);
	ComplexNumber operator -(ComplexNumber a);
	ComplexNumber operator *(ComplexNumber a);
	ComplexNumber operator /(ComplexNumber a);
	ComplexNumber& operator +=(ComplexNumber a);
	ComplexNumber& operator -=(ComplexNumber a);
	ComplexNumber& operator *=(ComplexNumber a);
	ComplexNumber& operator /=(ComplexNumber a);
	friend std::ostream& operator<<(std::ostream& os, const ComplexNumber& cn);

	ComplexNumber operator~();
	ComplexNumber operator+();
	ComplexNumber operator-();
	double operator!();

private:
	double real;
	double img;
};
std::ostream& operator <<(std::ostream& os, const ComplexNumber& cn);
