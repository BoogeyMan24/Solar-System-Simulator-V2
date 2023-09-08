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
	m_Renderer.ClearColor(COLOR_BLACK);
	m_Renderer.Clear();
	m_Renderer.SetUniform(Window::GetProjection() * Camera::GetView(), Window::GetResolution(), Camera::GetZoom());
	m_Renderer.DrawAll(m_EntityManager.GetEntities());
}

void SolarSystem::OnImGuiRender()
{
	ImGui::SliderFloat("Tick", &tick, 0.0f, 1000.0f, "%.3f");
}

void SolarSystem::OnImGuiRenderInspect()
{
	if (Settings::entitySelected != -1) {
		std::vector<Entity>& entities = *m_EntityManager.GetEntities();
		int index = Settings::entitySelected;


		ImGui::Text("%s", entities[index].name.c_str());
		ImGui::InputFloat2("Position", &entities[index].transform.position.x, "%.2f", ImGuiInputTextFlags_EnterReturnsTrue);
		ImGui::InputFloat2("Velocity", &entities[index].transform.velocity.x, "%.2f", ImGuiInputTextFlags_EnterReturnsTrue);
		ImGui::ColorEdit4("Velocity", &entities[index].color.r, ImGuiInputTextFlags_EnterReturnsTrue);
		ImGui::InputFloat("Mass", &entities[index].mass, 0.1f, 0.1f, "%.2f", ImGuiInputTextFlags_EnterReturnsTrue);
		ImGui::InputFloat("Radius", &entities[index].radius, 0.1f, 0.1f, "%.2f", ImGuiInputTextFlags_EnterReturnsTrue);
		ImGui::Checkbox("Affected By Gravity", &entities[index].affectedByGravity);
		ImGui::Checkbox("Affects Others", &entities[index].affectsOthers);
	} else {
		ImGui::Text("No object selected.");
		ImGui::Text("Select an object by left clicking on it.");
	}
}

void SolarSystem::OnImGuiRenderDebug(bool debug)
{
	if (ImGui::SliderFloat("Zoom", &zoom, 0.5f, 3.5f, "%.3f")) {
		Camera::SetZoom(zoom);
	}
	if (ImGui::SliderFloat("Zoom Speed", &zoomSpeed, 0.05f, 1.0f, "%.3f")) {
		Camera::SetZoomSpeed(zoomSpeed);
	}
	if (ImGui::SliderFloat("Camera Speed", &speed, 25.0f, 1000.0f, "%.1f")) {
		Camera::SetSpeed(speed);
	}
	if (ImGui::Button("Reload Shader")) {
		m_Renderer.ReloadShader();
	}
}


EntityManager SolarSystem::GetEntityManager() const {
	return m_EntityManager;
}