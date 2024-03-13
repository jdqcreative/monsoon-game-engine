#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
public:
	//Window();
	//~Window();

	// create window
	virtual void create() = 0;

	virtual void update() = 0;

	virtual void clear() = 0;

	virtual bool isOpen() const = 0;

	virtual void pollEvents() = 0;

	virtual void close() = 0;

	virtual GLuint getShader() = 0;

	virtual GLFWwindow* getWindow() = 0;
};