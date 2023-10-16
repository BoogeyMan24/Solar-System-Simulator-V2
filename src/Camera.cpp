#include "Camera.h"

Camera::Camera()
{

}

Camera::Camera(glm::vec2 pos)
{
	view = glm::translate(glm::mat4(-1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	position = pos;
}

Camera::~Camera()
{
	
}

void Camera::OnUpdate(float deltaTime)
{
	if (Input::IsKeyDown(GLFW_KEY_W) && !(Input::IsKeyDown(GLFW_KEY_S))) {
		movement += glm::vec2(0.0f, 1.0f);
		pressed = true;
	}

	if (Input::IsKeyDown(GLFW_KEY_A) && !(Input::IsKeyDown(GLFW_KEY_D))) {
		movement += glm::vec2(-1.0f, 0.0f);
		pressed = true;
	}

	if (Input::IsKeyDown(GLFW_KEY_S) && !(Input::IsKeyDown(GLFW_KEY_W))) {
		movement += glm::vec2(0.0f, -1.0f);
		pressed = true;
	}

	if (Input::IsKeyDown(GLFW_KEY_D) && !(Input::IsKeyDown(GLFW_KEY_A))) {
		movement += glm::vec2(1.0f, 0.0f);
		pressed = true;
	}

	if (pressed) {
		glm::vec2 normalized = glm::normalize(movement);
		position += speed * normalized * deltaTime;
	}
	view = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f));

	movement = glm::vec2(0.0f);
	pressed = false;


	Camera::SetZoom(Camera::GetZoom() + Input::GetScroll().y * zoomSpeed * deltaTime);
	Window::UpdateProjection();
}

glm::mat4 Camera::GetView()
{
	return view;
}

glm::vec2 Camera::GetPosition()
{
	return position;
}

void Camera::SetSpeed(float newSpeed)
{
	speed = newSpeed;
}

float Camera::GetSpeed()
{
	return speed;
}

void Camera::SetZoomSpeed(float newZoomSpeed)
{
	zoomSpeed = newZoomSpeed;
}

float Camera::GetZoomSpeed()
{
	return zoomSpeed;
}

void Camera::SetZoom(float zoom)
{
	m_Zoom = std::max(std::min(zoom, 3.5f), 0.5f);
	Window::UpdateProjection();
}


float Camera::GetZoom()
{
	return m_Zoom;
}

glm::vec2 Camera::GetWorldPosition(glm::vec2 position)
{
	glm::vec2 resolution = Window::GetResolution();
	float aspect = (resolution.x / resolution.y) / 2;
	glm::vec2 glPosition = glm::vec2((position.x - (resolution.x / 2)) / (resolution.x / 2) * Camera::GetZoom(), -(position.y - (resolution.y / 2)) / (resolution.y / 2) * Camera::GetZoom());

	glm::vec2 worldPosition = glPosition * (resolution / 2.0f) - Camera::GetPosition();

	return worldPosition;
}