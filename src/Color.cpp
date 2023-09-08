#include "Color.h"

Color::Color(float red, float green, float blue) 
{
	r = red;
	g = green;
	b = blue;
	a = 1.0f;
}

Color::Color(float red, float green, float blue, float alpha) 
{
	r = red;
	g = green;
	b = blue;
	a = alpha;
}

Color::Color(unsigned int hex) 
{
	int red, green, blue;

	red = hex >> 16;

	green = (hex & 0x00ff00) >> 8;

	blue = (hex & 0x0000ff);

	r = red / 255.0f;
	g = green / 255.0f;
	b = blue / 255.0f;
}

Color::Color() 
{
	r = 1.0f;
	g = 1.0f;
	b = 1.0f;
	a = 1.0f;
}

int Color::toHex() 
{
	return ((int)(r * 255) << 16 | (int)(g * 255) << 8 | (int)(b * 255));
}