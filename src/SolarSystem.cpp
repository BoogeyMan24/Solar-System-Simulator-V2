#include "SolarSystem.h"


SolarSystem::SolarSystem()
{
	m_Renderer.init(vertexCapacity);
}

SolarSystem::~SolarSystem()
{

}

void SolarSystem::OnUpdate(float deltaTime)
{
	Camera::OnUpdate(deltaTime);
	m_EntityManager.OnUpdate(deltaTime * tick);
	m_EntityManager.OnUpdateEntities(deltaTime * tick);
}

void SolarSystem::OnRender()
{
	m_Renderer.ClearColor(Settings::backgroundColor);
	m_Renderer.Clear();
	m_Renderer.SetUniform(Window::GetProjection() * Camera::GetView(), Window::GetResolution(), Camera::GetZoom());
	m_Renderer.DrawAll(m_EntityManager.GetEntities());
}

void SolarSystem::OnImGuiRender()
{
	if (ImGui::BeginTabBar("Main")) {
		if (ImGui::BeginTabItem("Main")) {
			ImGui::SliderFloat("Tick", &tick, 0.0f, 1000.0f, "%.3f");

			if (Settings::debug) {
				ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			}
			
			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Inspect")) {
			OnImGuiRenderInspect();

			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Camera")) {
			OnImGuiRenderCamera();

			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Debug")) {
			OnImGuiRenderDebug(Settings::debug);
			ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

			ImGui::EndTabItem();
		}
		
		ImGui::EndTabBar();
	}
}

void SolarSystem::OnImGuiRenderInspect()
{
	if (Settings::entitySelected != -1) {
		std::vector<Entity>& entities = *m_EntityManager.GetEntities();
		int index = Settings::entitySelected;

		ImGui::Text("%s", entities[index].name.c_str());
		ImGui::InputFloat2("Position", &entities[index].transform.position.x, "%.2f", ImGuiInputTextFlags_EnterReturnsTrue);
		ImGui::InputFloat2("Velocity", &entities[index].transform.velocity.x, "%.2f", ImGuiInputTextFlags_EnterReturnsTrue);
		ImGui::ColorEdit4("Color", &entities[index].color.r, ImGuiInputTextFlags_EnterReturnsTrue);
		ImGui::InputFloat("Mass", &entities[index].mass, 0.1f, 0.1f, "%.2f", ImGuiInputTextFlags_EnterReturnsTrue);
		ImGui::InputFloat("Radius", &entities[index].radius, 0.1f, 0.1f, "%.2f", ImGuiInputTextFlags_EnterReturnsTrue);
		ImGui::Checkbox("Affected By Gravity", &entities[index].affectedByGravity);
		ImGui::Checkbox("Affects Others", &entities[index].affectsOthers);
	} else {
		ImGui::Text("No object selected.");
		ImGui::Text("Select an object by left clicking on it.");
	}
}

void SolarSystem::OnImGuiRenderCamera()
{
	ImGui::InputFloat2("Position", &Camera::position.x, "%.0f", ImGuiInputTextFlags_EnterReturnsTrue);

	if (ImGui::SliderFloat("Zoom", &zoom, 0.5f, 3.5f, "%.3f")) {
		Camera::SetZoom(zoom);
	}
	
	ImGui::SliderFloat("Zoom Speed", &Camera::zoomSpeed, 0.05f, 1.0f, "%.3f");
	ImGui::SliderFloat("Camera Speed", &Camera::speed, 25.0f, 1000.0f, "%.1f");

	ImGui::ColorEdit4("Background Color", &Settings::backgroundColor.r);

}

void SolarSystem::OnImGuiRenderDebug(bool debug)
{
	if (ImGui::Button("Reload Shader")) {
		m_Renderer.ReloadShader();
	}

	ImGui::Checkbox("Debug", &Settings::debug);
}


EntityManager SolarSystem::GetEntityManager() const {
	return m_EntityManager;
}