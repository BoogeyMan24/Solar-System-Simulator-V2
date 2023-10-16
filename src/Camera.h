#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ErrorHandler.h"
#include "Input.h"



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


		static float speed;
		
		static glm::vec2 position;
		static bool pressed;

		static float zoomSpeed;
		static float m_Zoom;
	private:
		static glm::vec2 movement;
		static glm::mat4 view;
};
