#pragma once

#include <GL/glew.h>
#include "GLFW/glfw3.h"

#include <iostream>

#define ASSERT(x) if (!(x)) 1 / (x+(-x));
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__));

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);