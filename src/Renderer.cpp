#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "Renderer.h"

#define toVOIDptr(i) (const void*)(uintptr_t)(i)

struct Vertex {
	glm::vec2 vertexPosition;
	glm::vec2 position;
	glm::vec4 color;
	float radius;
};

static std::array<Vertex, 4> CreateQuad(glm::vec2 position, float radius, Color color) {

	Vertex v0;
	v0.vertexPosition = { position.x - (radius / 2),   position.y - (radius / 2) };
	v0.position = { position.x , position.y };
	v0.color = glm::vec4(color.r, color.g, color.b, color.a);
	v0.radius = radius;

	Vertex v1;
	v1.vertexPosition = { position.x + (radius / 2),   position.y - (radius / 2) };
	v1.position = { position.x , position.y };
	v1.color = glm::vec4(color.r, color.g, color.b, color.a);
	v1.radius = radius;

	Vertex v2;
	v2.vertexPosition = { position.x + (radius / 2),   position.y + (radius / 2) };
	v2.position = { position.x , position.y };
	v2.color = glm::vec4(color.r, color.g, color.b, color.a);
	v2.radius = radius;

	Vertex v3;
	v3.vertexPosition = { position.x - (radius / 2),   position.y + (radius / 2) };
	v3.position = { position.x , position.y };
	v3.color = glm::vec4(color.r, color.g, color.b, color.a);
	v3.radius = radius;

	return { v0, v1, v2, v3 };
}

Renderer::Renderer() 
{
	
}

Renderer::~Renderer() {
	GLCall(glDeleteVertexArrays(1, &m_VAO));
	GLCall(glDeleteBuffers(1, &m_VBO));
	GLCall(glDeleteBuffers(1, &m_IBO));
}

void Renderer::init(unsigned int vertexCapacity)
{
	this->vertexCapacity = vertexCapacity;
	this->indicesCapacity = vertexCapacity * (3/2);
	
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	GLCall(glGenVertexArrays(1, &m_VAO));
	GLCall(glBindVertexArray(m_VAO));

	GLCall(glGenBuffers(1, &m_VBO));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_VBO));
	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertexCapacity, NULL, GL_DYNAMIC_DRAW));

	GLCall(glEnableVertexAttribArray(0));
	GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), toVOIDptr(offsetof(Vertex, vertexPosition))));

	GLCall(glEnableVertexAttribArray(1));
	GLCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), toVOIDptr(offsetof(Vertex, position))));

	GLCall(glEnableVertexAttribArray(2));
	GLCall(glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), toVOIDptr(offsetof(Vertex, color))));

	GLCall(glEnableVertexAttribArray(3));
	GLCall(glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), toVOIDptr(offsetof(Vertex, radius))));
	
	
	uint32_t indices[indicesCapacity];
	unsigned int offset = 0;
	for(int i = 0; i < indicesCapacity; i += 6) {
		indices[i + 0] = 0 + offset;
		indices[i + 1] = 1 + offset;
		indices[i + 2] = 2 + offset;

		indices[i + 3] = 2 + offset;
		indices[i + 4] = 3 + offset;
		indices[i + 5] = 0 + offset;

		offset += 4;
	}

	GLCall(glGenBuffers(1, &m_IBO));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));

	m_Shader = std::make_unique<Shader>(m_Path);
	m_Shader->Bind();
}

void Renderer::Clear() const {
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::ClearColor(Color color)
{
	GLCall(glClearColor(color.r, color.g, color.b, 1.0f));
}

void Renderer::ReloadShader() {
	m_Shader = std::make_unique<Shader>(m_Path);
	m_Shader->Bind();
}

void Renderer::SetUniform(glm::mat4 mvp, glm::vec2 resolution, float zoom) {
	m_Shader->SetUniformMat4f("u_MVP", mvp);
	m_Shader->SetUniform2f("u_Resolution", resolution);
	m_Shader->SetUniform1f("u_Zoom", zoom);
}

void Renderer::DrawAll(std::vector<Entity> entitiesPtr)
{
	std::vector<Entity> entities = entitiesPtr;

	Vertex vertices[entities.size() * 4];

	for (int e = 0; e < entities.size(); e++) {
		auto entityQuad = CreateQuad(entities[e].transform.position, entities[e].radius, entities[e].color);
		

		memcpy(vertices + entityQuad.size() * e, entityQuad.data(), entityQuad.size() * sizeof(Vertex));
	}

	

	// GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_VBO));
	GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices));


	// GLCall(glBindVertexArray(m_VAO));
	GLCall(glDrawElements(GL_TRIANGLES, entities.size() * 6, GL_UNSIGNED_INT, nullptr));
}