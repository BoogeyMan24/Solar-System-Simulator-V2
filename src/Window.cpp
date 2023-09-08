#include "Window.h"

void WindowResizeCallback(GLFWwindow* window, int width, int height)
{
	Window::UpdateProjection();
    Window::UpdateResolution(window);
}


Window::Window()
{
}

Window::~Window()
{
}

void Window::init(glm::vec2 res, GLFWwindow* window)
{
	width = res.x;
	height = res.y;
	aspect = width / height;
	m_Projection = glm::ortho(-res.x / 2, res.x / 2, -res.y / 2, res.y / 2, -1.0f, 1.0f);
	
	glfwSetFramebufferSizeCallback(window, WindowResizeCallback);
}

glm::vec2 Window::GetResolution()
{
	return glm::vec2(width, height);
}

int Window::GetResolutionX()
{
	return width;
}

int Window::GetResolutionY()
{
	return height;
}

glm::mat4 Window::GetProjection()
{
	return m_Projection;
}

void Window::SetResolution(glm::vec2 resolution)
{
	width = resolution.x;
	height = resolution.y;
}

void Window::UpdateProjection() {
	m_Projection = glm::ortho((float) -width / 2 * Camera::GetZoom(), (float) width / 2 * Camera::GetZoom(), (float) -height / 2 * Camera::GetZoom(), (float) height / 2 * Camera::GetZoom(), -1.0f, 1.0f);
}

void Window::UpdateResolution(GLFWwindow* window)
{
	glfwGetWindowSize(window, &width, &height);
	aspect = width / height;
	GLCall(glViewport(0, 0, width * 2, 	height * 2));
}
