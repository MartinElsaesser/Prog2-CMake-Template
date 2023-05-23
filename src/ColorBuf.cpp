#pragma once
#include "Color.h"
#include "ColorBuf.h"
#include "ViewPortGL/ViewPortGL.h"
#include "stdexcept"
using namespace std;

ColorBuf::ColorBuf(unsigned int widthP, unsigned int heightP) : width{widthP}, height{heightP}
{
	colorState = new Color *[width];
	for (int i = 0; i < width; i++)
		colorState[i] = new Color[height];
};

ColorBuf::~ColorBuf()
{
	for (int i = 0; i < width; i++)
		delete[] colorState[i]; // delete array within matrix
	delete[] colorState;
};

Color &ColorBuf::get(unsigned int x, unsigned int y)
{
	return colorState[x][y];
};

void ColorBuf::set(unsigned int x, unsigned int y, const Color &c)
{
	colorState[x][y] = c;
};

void ColorBuf::drawTo(ViewPortGL &vp)
{
	if (vp.getXSize() != width || vp.getYSize() != height)
	{
		string error = "selected viewport has a different size than the color buffer: \n";
		error += "viewport size width:" + to_string(vp.getXSize()) + ", height:" + to_string(vp.getYSize()) + "\n";
		error += "buffer size width:" + to_string(width) + ", height:" + to_string(height);
		throw std::logic_error(error);
	}

	int maxPixelsDrawn = ViewPortGL::getMaxNumberOfPreparedPixels();
	int countPixelsDrawn = 0;
	vp.sendPixels(); // clears View Port Pixel Buffer !important, will result in a buffer overflow, if deleted

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			if (countPixelsDrawn >= maxPixelsDrawn)
			{
				countPixelsDrawn = 0;
				vp.sendPixels();
			}

			Color c = colorState[x][y];
			vp.preparePix(x, y, c.getRed(), c.getGreen(), c.getBlue());
			countPixelsDrawn++;
		}
	}
}
void ColorBuf::clear()
{
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			colorState[x][y] = Color::nullColor;
		}
	}
}
