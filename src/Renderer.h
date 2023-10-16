#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "ErrorHandler.h"
#include "Color.h"
#include "Entity.h"
#include "Shader.h"

class Renderer {
	public:
		Renderer();
		~Renderer();

		void init(unsigned int vertexCapacity);

		void Clear() const;
		void ClearColor(Color color);

		void ReloadShader();

		void SetUniform(glm::mat4 mvp, glm::vec2 resoluion, float zoom);

		void DrawAll(std::vector<Entity> entities);

	private:
		GLuint m_VAO, m_VBO, m_IBO;
		unsigned int vertexCapacity;
		unsigned int indicesCapacity;

		std::unique_ptr<Shader> m_Shader;
		std::string m_Path = "res/shaders/circle.shader";
};