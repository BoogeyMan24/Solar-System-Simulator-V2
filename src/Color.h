#pragma once

#define COLOR_BLACK Color(0.0f, 0.0f, 0.0f, 1.0f)
#define COLOR_WHITE Color(1.0f, 1.0f, 1.0f, 1.0f)
#define COLOR_RED Color(1.0f, 0.0f, 0.0f, 1.0f)
#define COLOR_GREEN Color(0.0f, 1.0f, 0.0f, 1.0f)
#define COLOR_BLUE Color(0.0f, 0.0f, 1.0f, 1.0f)
#define COLOR_PURPLE Color(1.0f, 0.0f, 1.0f, 1.0f)
#define COLOR_YELLOW Color(1.0f, 1.0f, 0.0f, 1.0f)

struct Color {
	float r, g, b, a;

	Color();
	Color(float red, float green, float blue);
	Color(float red, float green, float blue, float alpha);
	Color(unsigned int hex);
	int toHex();
};