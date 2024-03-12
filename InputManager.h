#pragma once
#include "Game.h"
#include <functional>

class InputManager {
public:
	//virtual ~InputManager();

	virtual void update() = 0;

	using KeyCallback = std::function<void(int, int)>;
	using MouseButtonCallback = std::function<void(int, int, double, double)>;
	using MousePositionCallback = std::function<void(double, double)>;

	virtual void setKeyCallback(const KeyCallback& callback) = 0;

	virtual void setMouseButtonCallback(const MouseButtonCallback& callback) = 0;

	virtual void setMousePositionCallback(const MousePositionCallback& callback) = 0;

	// virtual functions for handling controller?

	// other input related functions
};
