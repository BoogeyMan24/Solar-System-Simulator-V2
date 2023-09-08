#pragma once

#include <GL/glew.h>
#include "GLFW/glfw3.h"

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <unordered_map>

#include "ErrorHandler.h"
#include "Input.h"
#include "Camera.h"

static int width = 1024, height = 600;
static float aspect = width / height;
static glm::mat4 m_Projection;

class Window {
	public:
		Window();
		~Window();

		static void init(glm::vec2 resolution, GLFWwindow* window);

		static glm::vec2 GetResolution();
		static int GetResolutionX();
		static int GetResolutionY();
		static glm::mat4 GetProjection();

		static void SetResolution(glm::vec2 resolution);

		static void UpdateProjection();
		static void UpdateResolution(GLFWwindow* win);
};