#pragma once

#include "ErrorHandler.h"
#include "Entity.h"

#include "Input.h"
#include "Settings.h"

class EntityManager {
	public:
		EntityManager();
		~EntityManager();

		void OnUpdate(float deltaTime);
		void OnUpdateEntities(float deltaTime);
		void OnImGuiRender();

		void AddMass(Entity entity);
		void NewEntity(Entity entity);
		void NewEntity(std::string& name, glm::vec2 position, glm::vec2 velocity, float mass, float radius, Color color);
		void ClearMass();

		std::vector<Entity>* GetEntities();
	private:
		unsigned int ids = 0;

		const float G_CONSTANT = 0.0001f;

		std::vector<Entity> m_Entities;
};
