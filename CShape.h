#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include "Component.h"

class CShape : public Component {
public:
	float m_width = 100;
	float m_height = 100;
	GLuint m_vbo = 0;
	GLuint m_vao = 0;

	CShape(float width, float height)
		: m_width(width), m_height(height) {
		// Define vertex data for a rectangle
		float vertices[] = {
			-m_width / 2, -m_height / 2, // Bottom-left
			m_width / 2, -m_height / 2, // Bottom-right
			m_width / 2, m_height / 2, // Top-right
			-m_width / 2, m_height / 2 // top-left
		};

		// Generate VBO and VAO
		glGenBuffers(1, &m_vbo);
		glGenVertexArrays(1, &m_vao);

		// Bind VAO
		glBindVertexArray(m_vao);

		// Bind VBO and buffer data
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// Enable vertex attribute
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// Unbind VAO
		glBindVertexArray(0);
	}

	~CShape() {
		// Delete VBO and VAO
		glDeleteBuffers(1, &m_vbo);
		glDeleteVertexArrays(1, &m_vao);
	}

	void render(const glm::mat4& parentTransform = glm::mat4(1.0f)) {
		// Apply parent transform
		glm::mat4 model = parentTransform;

		// Render shape
		glBindVertexArray(m_vao);
		glDrawArrays(GL_QUADS, 0, 4);
		glBindVertexArray(0);
	}
};