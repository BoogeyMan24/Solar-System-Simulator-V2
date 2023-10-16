#include "EntityManager.h"

EntityManager::EntityManager()
{
	NewEntity(Entity("Planet 0", glm::vec2(0.0f), glm::vec2(0.0f), 5000000, 50, COLOR_GREEN));
	// NewEntity(Entity(glm::vec2(100.0f, 0.0f), glm::vec2(0.0f, -glm::sqrt(5.0f)), 5, 5, COLOR_BLUE));
	NewEntity(Entity("Planet 1", glm::vec2(300.0f, 0.0f), glm::vec2(0.0f, -glm::sqrt(1.666671f)), 5, 5, COLOR_RED));
}

EntityManager::~EntityManager()
{
	m_Entities.clear();
}

void EntityManager::OnUpdate(float deltaTime)
{
	if (Input::IsButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) {
		glm::vec2 position = Camera::GetWorldPosition(Input::GetMousePosition());
		for (auto& entity : m_Entities) {
			if (glm::distance(position, entity.transform.position) < entity.radius) {
				Settings::entitySelected = entity.id;
				
			}
		}
	} else if (Input::IsButtonPressed(GLFW_MOUSE_BUTTON_RIGHT)) {
		glm::vec2 position = Camera::GetWorldPosition(Input::GetMousePosition());
		NewEntity(Entity("Planet 1", position, glm::vec2(0.0f), 5, 5, COLOR_RED));
	}
}

void EntityManager::OnUpdateEntities(float deltaTime)
{
	for (auto& entity : m_Entities) 
	{
		glm::vec2 acceleration(0.0f);

		if (!entity.affectedByGravity)
			continue;

		for (auto& other : m_Entities) {
			if (entity.id != other.id && other.affectsOthers) {
				glm::vec2 difference = other.transform.position - entity.transform.position;
				glm::vec2 direction = glm::normalize(difference);
				float distanceSqr = glm::pow(difference.x, 2) + glm::pow(difference.y, 2);

				acceleration += direction * G_CONSTANT * other.mass / distanceSqr;
			}
		}

		entity.transform.velocity += acceleration * deltaTime;
		entity.transform.position += entity.transform.velocity * deltaTime;
	}
}

void EntityManager::OnImGuiRender()
{
	
}

void EntityManager::AddMass(Entity entity)
{
	m_Entities.push_back(entity);
}

void EntityManager::NewEntity(Entity entity)
{
	entity.id = ids;
	AddMass(entity);
	ids++;
}

void EntityManager::NewEntity(std::string& name, glm::vec2 position, glm::vec2 velocity, float mass, float radius, Color color)
{
	AddMass(Entity(ids, name, position, velocity, mass, radius, color));
	ids++;
}

void EntityManager::ClearMass()
{
	m_Entities.clear();
}

std::vector<Entity>* EntityManager::GetEntities()
{
	return &m_Entities;
}
