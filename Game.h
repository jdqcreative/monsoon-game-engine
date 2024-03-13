#pragma once
#include "Window.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "AssetManager.h"
#include "SoundManager.h"
#include "PhysicsManager.h"
#include "EntityManager.h"
#include "ComponentManager.h"

class Game {
private:
	Window* window;
	SceneManager* sceneManager;
	InputManager* inputManager;
	AssetManager* assetManager;
	SoundManager* soundManager;
	PhysicsManager* physicsManager;
	EntityManager* entityManager;
	ComponentManager* componentManager;
	bool isRunning;

public:
	Game();

	void initialize();

	void update(float deltaTime);

	void render();

	void run();

	// Input polling
	void handleKeyInput(int key, int action);

	void handleMouseButtonInput(int button, int action, double xPos, double yPos);

	void handleMousePositionInput(double xPos, double yPos);

	void shutdown();
};