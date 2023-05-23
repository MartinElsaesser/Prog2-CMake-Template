#pragma once
class Color
{
public:
	Color(int r, int g, int b);
	Color();
	Color(bool isValidColor);

	int getRed() const;
	int getGreen() const;
	int getBlue() const;
	void setRed(int r);
	void setGreen(int g);
	void setBlue(int b);

	Color darken(int amount);
	Color lighten(int amount);

	Color averageWith(const Color &other) const;
	Color averageWith(const Color &other1, const Color &other2, const Color &other3) const;
	Color randomlyChange(int maxAmount) const;
	inline bool equals(const Color& other) const;

	static const Color nullColor;
private:
	int red;
	int green;
	int blue;
};

inline bool Color::equals(const Color& other) const {
	if (this->red != other.red) return false;
	if (this->green != other.green) return false;
	if (this->blue != other.blue) return false;
	return true;
}