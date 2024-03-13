#pragma once
#include <stdexcept>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

class WindowsWindow : public Window {
public:
	WindowsWindow(int width, int height, const std::string& title)
		: m_width(width), m_height(height), m_title(title) {

	}

	~WindowsWindow() {
		if (m_window) {
			glfwDestroyWindow(m_window);
			m_window = nullptr;
		}
		glfwTerminate();
	}

	void create() {
		// Initialize GLFW
		if (!glfwInit()) {
			throw std::runtime_error("Failed to initialize GLFW");
		}

		// Set GLFW window hints
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		// Create GLFW window
		m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), NULL, NULL);
		if (!m_window) {
			glfwTerminate();
			throw std::runtime_error("Failed to create GLFW window");
		}

		// Make the OpenGL context current
		glfwMakeContextCurrent(m_window);

		// Initialize GLAD
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			glfwTerminate();
			throw std::runtime_error("Failed to initialize GLAD");
		}

		glViewport(0, 0, m_width, m_height);
	}

	void update() {
		// Swap front and back buffers
		glfwSwapBuffers(m_window);

		// Poll for and process events
		pollEvents();
	}

	void clear() {
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	bool isOpen() const {
		// Gets flag that can be used to close the window(game) loop
		return !glfwWindowShouldClose(m_window);
	}

	void pollEvents() {
		// Poll for and process events
		glfwPollEvents();
	}

	void close() {
		if (m_window) {
			// Sets flag that can be used to close the window(game) loop
			glfwSetWindowShouldClose(m_window, true);
		}
	}

	GLFWwindow* getWindow() {
		return m_window;
	}

	// Shader setup functions

	// Function to compile shader
	GLuint compileShader(GLenum type, const char* source) {
		GLuint shader = glCreateShader(type);
		glShaderSource(shader, 1, &source, nullptr);
		glCompileShader(shader);

		// Check for compilation errors
		GLint success;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			char infoLog[512];
			glGetShaderInfoLog(shader, 512, nullptr, infoLog);
			std::cerr << "Shader compilation error: " << infoLog << std::endl;
			glDeleteShader(shader);
			return 0;
		}

		return shader;
	}

	// Function to create shader program
	GLuint getShader() {

		// Shader variables
		const char* vertexShaderSource = R"(
			#version 330 core
			layout (location = 0) in vec3 aPos;
			void main() {
				gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
			}
		)";

		const char* fragmentShaderSource = R"(
			#version 330 core
			out vec4 FragColor;
			void main() {
				FragColor = vec4(1.0, 0.5, 0.2, 1.0);
			}
		)";

		// Compile vertex shader
		GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
		if (vertexShader == 0) {
			return 0;
		}

		// Compile fragment shader
		GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
		if (fragmentShader == 0) {
			glDeleteShader(vertexShader);
			return 0;
		}

		// Create shader program
		GLuint shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);

		// Check for linking errors
		GLint success;
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success) {
			char infoLog[512];
			glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
			std::cerr << "Shader program linking error: " << infoLog << std::endl;
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);
			glDeleteProgram(shaderProgram);
			return 0;
		}

		// Delete shaders (no longer needed after linking)
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		return shaderProgram;
	}

private:
	GLFWwindow* m_window = nullptr;
	int m_width;
	int m_height;
	std::string m_title;
};