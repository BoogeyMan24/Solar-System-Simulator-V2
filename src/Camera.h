#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ErrorHandler.h"
#include "Input.h"



static float speed = 250.0f;
static glm::vec2 movement;
static glm::vec2 position = glm::vec2(0.0f);
static bool pressed = false;

static float zoomSpeed = 1.0f;
static float m_Zoom = 1.0f;

static glm::mat4 view = glm::mat4(1.0f);

class Camera {
	public:
		Camera();
		Camera(glm::vec2 position);
		~Camera();

		static void OnUpdate(float deltaTime);
		
		static glm::mat4 GetView();
		static glm::vec2 GetPosition();
		static void SetSpeed(float newSpeed);
		static float GetSpeed();

		static void SetZoomSpeed(float newZoomSpeed);
		static float GetZoomSpeed();

		static void SetZoom(float zoom);
		static float GetZoom();

		static glm::vec2 GetWorldPosition(glm::vec2 position);
	private:
		
};
