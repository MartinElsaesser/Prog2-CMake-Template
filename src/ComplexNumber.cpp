#pragma once
#include <iostream>
#include <cmath>
#include "ComplexNumber.h"

ComplexNumber::ComplexNumber(double re, double im) {
	real = re; img = im;
}
double ComplexNumber::getReal() const {
	return real;
}
double ComplexNumber::getImg() const {
	return img;
}

std::string ComplexNumber::to_string() {
	return "("+ std::to_string(real) + ", " + std::to_string(img) + "i)";
}


ComplexNumber ComplexNumber::operator +(ComplexNumber a) {
	return ComplexNumber(real + a.real, img + a.img);
}
ComplexNumber ComplexNumber::operator -(ComplexNumber a) {
	return ComplexNumber(real - a.real, img - a.img);
}
ComplexNumber ComplexNumber::operator *(ComplexNumber a) {
	return ComplexNumber(real * a.real - img * a.img, real * a.img + img * a.real);
}
ComplexNumber ComplexNumber::operator /(ComplexNumber a) {
	double h = 1 / (a.real * a.real + a.img * a.img);
	return ComplexNumber(h * (real * a.real + img * a.img),  h * (img * a.real - real * a.img));
}
ComplexNumber& ComplexNumber::operator+=(ComplexNumber a) {
	real += a.real;
	img += a.img;
	return *this;
}
ComplexNumber& ComplexNumber::operator-=(ComplexNumber a) {
	real -= a.real;
	img -= a.img;
	return *this;
}
ComplexNumber& ComplexNumber::operator*=(ComplexNumber a) {
	double newReal = real * a.real - img * a.img;
	double newImg = real * a.img + img * a.real;
	real = newReal;
	img = newImg;
	return *this;
}
ComplexNumber& ComplexNumber::operator/=(ComplexNumber a) {

	double h = 1 / (a.real * a.real + a.img * a.img);
	double newReal = h * (real * a.real + img * a.img);
	double newImg =   h * (img * a.real - real * a.img);
	real = newReal;
	img = newImg;
	return *this;
}


std::ostream& operator <<(std::ostream& os, const ComplexNumber& cn) {
	os <<  "(" << std::to_string(cn.real) << ", " << std::to_string(cn.img) << "i)";
	return os;
}



ComplexNumber ComplexNumber::operator~() {
	return ComplexNumber(real, -img);
}
ComplexNumber ComplexNumber::operator+() {
	return ComplexNumber(real, img);
}
ComplexNumber ComplexNumber::operator-() {
	return ComplexNumber(-real, -img);
}
double ComplexNumber::operator!() {
	return sqrt(real * real + img * img);
}
