#include "Color.h"
#include <string>
#include <stdexcept>
#include <algorithm>
#include "Utils.h"

void throwIfOutOfBounds(int color_component) {
	if (color_component < 0 || color_component > 255) {
		std::string err = "Color argument " + std::to_string(color_component) + " not in range [0-255]";
		throw std::invalid_argument(err);
	}
}


Color::Color() {
	this->red = 0;
	this->blue = 0;
	this->green = 0;
}

Color::Color(bool isValidColor) {
	if (isValidColor) {
		this->red = 0;
		this->blue = 0;
		this->green = 0;
		return;
	}
	this->red = -1;
	this->blue = -1;
	this->green = -1;
}

Color::Color(int r, int g, int b) {
	throwIfOutOfBounds(r);
	throwIfOutOfBounds(g);
	throwIfOutOfBounds(b);

	this->red = r;
	this->blue = b;
	this->green = g;
}


int Color::getRed() const {
	return this->red;
}
int Color::getGreen() const {
	return this->green;
}
int Color::getBlue() const {
	return this->blue;
}
void Color::setRed(int r) {
	throwIfOutOfBounds(r);
	this->red = r;
}
void Color::setGreen(int g) {
	throwIfOutOfBounds(g);
	this->green = g;
}
void Color::setBlue(int b) {
	throwIfOutOfBounds(b);
	this->blue = b;
}

const Color Color::nullColor = Color(false);


Color Color::lighten(int amount) {
	throwIfOutOfBounds(amount);
	int red = limit(0, 255, this->red + amount);
	int blue = limit(0, 255, this->blue + amount);
	int green = limit(0, 255, this->green + amount);
	return Color(red, green, blue);
}

Color Color::darken(int amount) {
	throwIfOutOfBounds(amount);
	int red = limit(0, 255, this->red - amount);
	int blue = limit(0, 255, this->blue - amount);
	int green = limit(0, 255, this->green - amount);
	return Color(red, green, blue);
}

Color Color::averageWith(const Color& other) const {
	int newRed = (this->red + other.red) / 2;
	int newGreen = (this->green + other.green) / 2;
	int newBlue = (this->blue + other.blue) / 2;
	
	return Color(newRed, newGreen, newBlue);
};

Color Color::averageWith(const Color &other1, const Color &other2, const Color &other3) const {	
	int newRed = (this->red + other1.red + other2.red + other3.red) / 4;
	int newGreen = (this->green + other1.green + other2.green + other3.green) / 4;
	int newBlue = (this->blue + other1.blue + other2.blue + other3.blue) / 4;
	
	return Color(newRed, newGreen, newBlue);
};


Color Color::randomlyChange(int maxAmount) const {
	int upper = abs(maxAmount);
	int lower = -abs(maxAmount);

	int newRed = limit(0, 255, this->red + randomNum(lower, upper));
	int newGreen = limit(0, 255, this->green + randomNum(lower, upper));
	int newBlue = limit(0, 255, this->blue + randomNum(lower, upper));

	return Color(newRed, newGreen, newBlue);
}
