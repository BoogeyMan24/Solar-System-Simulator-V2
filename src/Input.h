#pragma once

#include <GL/glew.h>
#include "GLFW/glfw3.h"

#include <unordered_map>

#include "ErrorHandler.h"

#include "Window.h"

static GLFWwindow* m_Window;
static std::unordered_map<int, int> inputs;
static std::unordered_map<int, int> inputsMouse;
static glm::vec2 scroll(0.0f);
static glm::dvec2 mousePosition(0.0f);
static int entered;

class Input {
	public:
		Input();
		~Input();

		static void init(GLFWwindow* window);

		static bool IsKeyPressed(int key);
		static bool IsKeyDown(int key);
		static bool IsKeyReleased(int key);
		static bool IsKeyUp(int key);

		static bool IsButtonPressed(int key);
		static bool IsButtonDown(int key);
		static bool IsButtonReleased(int key);
		static bool IsButtonUp(int key);

		static bool Entered();

		static glm::vec2 GetScroll();
		static glm::vec2 GetMousePosition();

		static void clear();
};