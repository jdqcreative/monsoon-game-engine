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
	}

	void update() {
		// Swap front and back buffers
		glfwSwapBuffers(m_window);

		// Poll for and process events
		pollEvents();
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

private:
	GLFWwindow* m_window = nullptr;
	int m_width;
	int m_height;
	std::string m_title;
};