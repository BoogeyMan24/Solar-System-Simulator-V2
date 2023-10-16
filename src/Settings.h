#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "ErrorHandler.h"
#include "Color.h"
#include "Entity.h"
#include "Shader.h"

class Settings {
	public:
		Settings();
		~Settings();

		static bool debug;
		static unsigned int entitySelected;
		static unsigned int mainEntity;
		
		static Color backgroundColor;
};