#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "ErrorHandler.h"
#include "EntityManager.h"
#include "Renderer.h"
#include "Camera.h"
#include "Window.h"
#include "Input.h"
#include "Settings.h"

struct Vertex 
{
	float Position[3];
	float Color[4];
};

class SolarSystem {
	public:
		SolarSystem();
		~SolarSystem();

		void OnUpdate(float deltaTime);
		void OnRender();
		void OnImGuiRender();
		void OnImGuiRenderInspect();
		void OnImGuiRenderDebug(bool debug);

		EntityManager GetEntityManager() const;
	private:
		float tick = 1.0f;

		float zoom = 1.0f;
		float zoomSpeed = 1.0f;
		float speed = 250.0f;

		EntityManager m_EntityManager;
		Renderer m_Renderer;
		Camera camera;

		u_int64_t vertexCapacity = 1024;
};