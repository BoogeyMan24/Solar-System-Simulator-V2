#include "EntityManager.h"

EntityManager::EntityManager()
{
	// NewEntity(Entity("Planet 0", glm::vec2(0.0f), glm::vec2(0.0f), 5000000, 50, COLOR_GREEN));
	// NewEntity(Entity("Planet 1", glm::vec2(300.0f, 0.0f), glm::vec2(0.0f, -glm::sqrt(1.666671f)), 5, 5, COLOR_RED));
	// 									  start pos multiplier velocity^2            velocity adjustment for start pos   mass adjustment      mass multiplier
	NewEntity(Entity("Planet 0", glm::vec2(-0.97000436f, 0.24308753f) * 400.0f,  glm::vec2( 0.4662036850f, 0.4323657300f) / 20.0f * 20.0f, 1 * 400.0f, 45, COLOR_RED));
	NewEntity(Entity("Planet 1", glm::vec2( 0.0f, 0.0f),                         glm::vec2(-0.93240737f,   -0.86473146f)  / 20.0f * 20.0f, 1 * 400.0f, 45, COLOR_GREEN));
	NewEntity(Entity("Planet 2", glm::vec2( 0.97000436f, -0.24308753f) * 400.0f, glm::vec2( 0.4662036850f, 0.4323657300f) / 20.0f * 20.0f, 1 * 400.0f, 45, COLOR_BLUE));
}

EntityManager::~EntityManager()
{
	m_Entities.clear();
}

void EntityManager::OnUpdate(float deltaTime)
{
	if (Input::IsButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) {
		glm::vec2 position = Camera::GetWorldPosition(Input::GetMousePosition());
		for (auto& [id, entity] : m_Entities) {
			if (glm::distance(position, entity.transform.position) < entity.radius) {
				Settings::entitySelected = id;
			}
		}
	} else if (Input::IsButtonPressed(GLFW_MOUSE_BUTTON_RIGHT)) {
		glm::vec2 position = Camera::GetWorldPosition(Input::GetMousePosition());
	
		float radius = glm::distance(m_Entities.at(Settings::mainEntity).transform.position, position);
		glm::vec2 difference = m_Entities.at(Settings::mainEntity).transform.position - position;
		glm::vec2 direction = glm::normalize(difference);
		float distanceSqr = glm::pow(difference.x, 2) + glm::pow(difference.y, 2);

		glm::vec2 acceleration = (glm::vec2) G_CONSTANT * m_Entities.at(Settings::mainEntity).mass / distanceSqr;

		NewEntity(Entity("Planet 1", position, glm::vec2(direction.y, -direction.x) * glm::sqrt(glm::abs(acceleration * radius)), 5, 5, COLOR_RED));
	}
}

void EntityManager::OnUpdateEntities(float deltaTime)
{
	for (auto& [id, entity] : m_Entities) 
	{
		glm::vec2 acceleration(0.0f);

		if (!entity.affectedByGravity)
			continue;

		for (auto& [id, other] : m_Entities) {
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
	
	m_Entities.insert({entity.id, entity});
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

void EntityManager::RemoveEntity(unsigned int id)
{
	m_Entities.erase(id);
}

void EntityManager::ClearEntities()
{
	std::vector<unsigned int> indexes;
	std::cout << m_Entities.size();
	for (auto& [id, entity] : m_Entities) {
		std::cout << id << std::endl;
		if (entity.id > 0) {
			indexes.push_back(entity.id);
		}
	}

	for (int i = 0; i < indexes.size(); i++) {
		RemoveEntity(indexes[i]);
	}
}

void EntityManager::ClearMass()
{
	m_Entities.clear();
}

std::vector<Entity> EntityManager::GetEntities()
{
	std::vector<Entity> entitiesVector;
	for (auto& [id, entity] : m_Entities) {
		entitiesVector.push_back(entity);
	}
	return entitiesVector;
}

std::unordered_map<unsigned int, Entity>* EntityManager::GetMappedEntities()
{
	return &m_Entities;
}
