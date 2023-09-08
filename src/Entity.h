#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <vector>
#include <string>

#include "Color.h"

struct Transform {
	glm::vec2 position;
	glm::vec2 velocity;
};

struct Entity
{ 
	unsigned int id;
	std::string name;

	Color color;

	Transform transform;

	float mass;
	float radius;

	bool affectedByGravity = true;
	bool affectsOthers = true;

	Entity(unsigned int id, std::string name, glm::vec2 position, glm::vec2 velocity, float mass, float radius, Color color);
	Entity(std::string name, glm::vec2 position, glm::vec2 velocity, float mass, float radius, Color color);
	Entity(glm::vec2 position, glm::vec2 velocity, float mass, float radius, Color color);
};