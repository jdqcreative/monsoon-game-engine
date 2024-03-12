#pragma once
#include "InputManager.h"
#include "WindowsWindow.h"
#include "functional"
#include<unordered_map>
#include <iostream>
#include <Windows.h>

class WindowsInputManager : public InputManager {
public:
	WindowsInputManager(Window* window)
		: m_window(window->getWindow()) {
		// Set GLFW callbacks
		glfwSetWindowUserPointer(m_window, this);
		glfwSetKeyCallback(m_window, keyCallback);
		glfwSetMouseButtonCallback(m_window, mouseButtonCallback);
		glfwSetCursorPosCallback(m_window, cursorPositionCallback);
	}

	// typedefs for callback wrappers
	using KeyCallback = std::function<void(int, int)>;
	using MouseButtonCallback = std::function<void(int, int, double, double)>;
	using MousePositionCallback = std::function<void(double, double)>;

	// Callback functions for the Game class to set
	void setKeyCallback(const KeyCallback& callback) {
		m_keyCallback = callback;
	}

	void setMouseButtonCallback(const MouseButtonCallback& callback) {
		m_mouseButtonCallback = callback;
	}

	void setMousePositionCallback(const MousePositionCallback& callback) {
		m_mousePositionCallback = callback;
	}

	// Update function to poll for events
	void update() {
		glfwPollEvents();
	}

private:
	// Callback functions for mouse and keyboard
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		WindowsInputManager* inputManager = static_cast<WindowsInputManager*>(glfwGetWindowUserPointer(window));
		if (inputManager && inputManager->m_keyCallback) {
			inputManager->m_keyCallback(key, action);
		}
	}

	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
		WindowsInputManager* inputManager = static_cast<WindowsInputManager*>(glfwGetWindowUserPointer(window));
		if (inputManager && inputManager->m_mouseButtonCallback) {
			double xPos, yPos;
			glfwGetCursorPos(window, &xPos, &yPos);
			inputManager->m_mouseButtonCallback(button, action, xPos, yPos);
		}
	}

	static void cursorPositionCallback(GLFWwindow* window, double xPos, double yPos) {
		WindowsInputManager* inputManager = static_cast<WindowsInputManager*>(glfwGetWindowUserPointer(window));
		if (inputManager && inputManager->m_mousePositionCallback) {
			inputManager->m_mousePositionCallback(xPos, yPos);
		}
	}

	GLFWwindow* m_window;
	KeyCallback m_keyCallback;
	MouseButtonCallback m_mouseButtonCallback;
	MousePositionCallback m_mousePositionCallback;
};