
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "glm/glm.hpp"

#include <iostream>

#include "Input.h"
#include "ErrorHandler.h"
#include "SolarSystem.h"
#include "Camera.h"
#include "Window.h"
#include "Settings.h"


/* 
TODO
Idle Breakout Save:
MTksMzAxNiwwLDAsMCwxOTIwLDE5MjAsMCwxLDgyOSwyLDEsMSwwLDQ1MTgyLjMzLDk5OTk5OSw4OTExLDg5MTEsNTEwOSw1MTA5LDEwODksMTA4OSwxMDMzLDEwMzMsMCwwLDAsMCw5LDYsMiwwLDAsMCwwLDAsMCw0LDQsMSwyLDAsMCwwLDAsMCwwLDAsMCwwLDAsMTEsMCwwLDAsMCwwLDAsMCwwLDAsMCwwLDAsMCwwLDAsMCwwLDEsMSwwLDAsMCwwLDAsMCwwLDAsMCwwLDAsMCwwLDEsMCwwLDAsMCwwLDAsMCwwLDAsMCwwLDAsMCwwLDAsMCwwLDAsMCwwLDAsMCwwLDEsMCwxLDAsMCw=


*/

//SETTINGS
int Settings::entitySelected = -1;
bool Settings::debug = false;


//CAMERA SETTINGS
float Camera::speed = 250.0f;
glm::vec2 Camera::movement;
glm::vec2 Camera::position = glm::vec2(0.0f);
bool Camera::pressed = false;

float Camera::zoomSpeed = 1.0f;
float Camera::m_Zoom = 1.0f;

glm::mat4 Camera::view = glm::mat4(1.0f);

Color Settings::backgroundColor = COLOR_BLACK;

void ImGuiInit(GLFWwindow* window) {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();
	ImGui::StyleColorsDark();
}

void ImGuiNew() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Solar System");
}

void ImGuiEnd() {
	ImGui::End();
			
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Terminate() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	GLCall(glfwTerminate());
}

// void MousePositionCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
// 	inputs[key] = std::vector<int>(key, action);
// }

int main(void)
{
	GLFWwindow* window;

	if (!glfwInit())
		return -1;

	const char* glsl_version = "#version 150";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif
	
	
	window = glfwCreateWindow(Window::GetResolutionX(), Window::GetResolutionY(), "Solar System Simulator", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	if(glewInit() != GLEW_OK)
	{
		std::cout << "Error! Failed to init GLEW" << std::endl;
		return -1;
	}
	Window windowManager;
	windowManager.init(glm::vec2(1024.0f, 600.0f), window);

	glfwSetWindowSizeLimits(window, 480, 300, GLFW_DONT_CARE, GLFW_DONT_CARE);

	Input input;
	input.init(window);
	
	std::cout << glGetString(GL_VERSION) << std::endl;


	{
		SolarSystem solarSystem;

		ImGuiInit(window);

		double currentTime = glfwGetTime();

		while (!glfwWindowShouldClose(window)) {

			double newTime = glfwGetTime();
			double deltaTime = newTime - currentTime;

			if (deltaTime > 0.05f)
				deltaTime = 0.05f;
			currentTime = newTime;

			ImGuiNew();
			
			solarSystem.OnImGuiRender();


			solarSystem.OnUpdate(deltaTime);
			solarSystem.OnRender();

			
			ImGuiEnd();

			glfwSwapBuffers(window);

			Input::clear();
			glfwPollEvents();
		}
	}

	Terminate();
	return 0;
}