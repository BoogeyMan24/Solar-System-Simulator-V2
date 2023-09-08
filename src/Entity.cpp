#include "Entity.h"


Entity::Entity(unsigned int id, std::string name, glm::vec2 position, glm::vec2 velocity, float mass, float radius, Color color)
{
	this->id = id;
	if (name.size() > 0) {
		this->name = name;
	} else {
		this->name = "Planet";
	}
	
	this->transform.position = position;
	this->transform.velocity = velocity;
	this->mass = mass;
	this->radius = radius;
	this->color = color;

	this->affectedByGravity = true;
	this->affectsOthers = true;

}

Entity::Entity(std::string name, glm::vec2 position, glm::vec2 velocity, float mass, float radius, Color color)
{
	if (name.size() > 0) {
		this->name = name;
	} else {
		this->name = "Planet";
	}
	this->transform.position = position;
	this->transform.velocity = velocity;
	this->mass = mass;
	this->radius = radius;
	this->color = color;

	this->affectedByGravity = true;
	this->affectsOthers = true;
}

Entity::Entity(glm::vec2 position, glm::vec2 velocity, float mass, float radius, Color color)
{
	this->name = "Planet";
	this->transform.position = position;
	this->transform.velocity = velocity;
	this->mass = mass;
	this->radius = radius;
	this->color = color;

	this->affectedByGravity = true;
	this->affectsOthers = true;
}
