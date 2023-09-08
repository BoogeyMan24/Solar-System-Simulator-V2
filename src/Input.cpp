#include "Input.h"

// void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) 
// {
// 	auto input = inputs.find(key);

// 	if (input != inputs.end() && input->second != 0 ) {
// 		if (action == GLFW_RELEASE) {
// 			input->second = 0;
// 		} else if (input->second >= 1 && (action == GLFW_PRESS || action == GLFW_REPEAT)){
// 			input->second++;
// 		}
// 	} else {
// 		inputs[key] = 1;
// 	}

// 	std::cout << inputs[key] << std::endl;
// }

// void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
// {
// 	auto input = inputs.find(button);

// 	if (input != inputs.end()) {
// 		if (action == GLFW_RELEASE) {
// 			inputsMouse[button] = 0;
// 		} else if (input->second >= 1 && (action == GLFW_PRESS || action == GLFW_REPEAT)){
// 			input->second++;
// 		}
// 	} else {
// 		inputsMouse[button] = 1;
// 	}
// }




void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	inputs[key] = action;
}

void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	inputsMouse[button] = action;
}

void MouseEnterCallback(GLFWwindow* window, int enter)
{
    entered = enter;
}

void MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	scroll = { xoffset, yoffset };
}

Input::Input()
{

}

Input::~Input()
{

}

void Input::init(GLFWwindow* window) {
	m_Window = window;

	glfwSetKeyCallback(m_Window, KeyCallback);
	glfwSetMouseButtonCallback(m_Window, MouseButtonCallback);
	glfwSetScrollCallback(m_Window, MouseScrollCallback);
	glfwSetCursorEnterCallback(m_Window, MouseEnterCallback);
}




bool Input::IsKeyPressed(int key)
{
	if(inputs.count(key))
		return (inputs[key] == GLFW_PRESS);
	return false;
}

bool Input::IsKeyDown(int key)
{
	return (glfwGetKey(m_Window, key) == GLFW_PRESS);
}

bool Input::IsKeyReleased(int key)
{
	if(inputs.count(key))
		return (inputs[key] == GLFW_RELEASE);
	return false;
}

bool Input::IsKeyUp(int key)
{
	return (glfwGetKey(m_Window, key) == GLFW_RELEASE);
}






bool Input::IsButtonPressed(int button)
{
	if(inputsMouse.count(button))
		return (inputsMouse[button] == GLFW_PRESS);
	return false;
}

bool Input::IsButtonDown(int button)
{
	return (glfwGetMouseButton(m_Window, button) == GLFW_PRESS);
}

bool Input::IsButtonReleased(int button)
{
	if(inputsMouse.count(button))
		return (inputsMouse[button] == GLFW_RELEASE);
	return false;
}

bool Input::IsButtonUp(int button)
{
	return (glfwGetMouseButton(m_Window, button) == GLFW_RELEASE);
}

bool Input::Entered()
{
	return entered;
}

glm::vec2 Input::GetScroll()
{
	return -scroll;
}

glm::vec2 Input::GetMousePosition()
{
	glfwGetCursorPos(m_Window, &mousePosition.x, &mousePosition.y);
	return mousePosition;
}

void Input::clear() {
	inputs.clear();
	inputsMouse.clear();
	scroll = glm::vec2(0.0f);
}