#include "Game.h"
#include "WindowsWindow.h"
#include "WindowsInputManager.h"
#include <chrono>

// Game class constructor
Game::Game()
	: window(nullptr), sceneManager(nullptr), inputManager(nullptr), assetManager(nullptr),
	soundManager(nullptr), physicsManager(nullptr), entityManager(nullptr), componentManager(nullptr), isRunning(false)
{}

// calculate time elapsed since last frame
float calculateDeltaTime()
{
	static auto previousTime = std::chrono::high_resolution_clock::now();
	auto currentTime = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> deltaTime = currentTime - previousTime;
	previousTime = currentTime;
	return deltaTime.count();
}

void Game::initialize()
{
	// initialize all managers and subsystems
#ifdef _WIN32

	// Set Windows specific manager and subsystems
	window = new WindowsWindow(800, 600, "Monsuun Engine");

	// initialize game window
	window->create();

	// initialize input manager
	inputManager = new WindowsInputManager(window);

	inputManager->setKeyCallback([this](int key, int action) {
		handleKeyInput(key, action);
		});

	inputManager->setMouseButtonCallback([this](int button, int action, double xPos, double yPos) {
		handleMouseButtonInput(button, action, xPos, yPos);
		});

	inputManager->setMousePositionCallback([this](double xPos, double yPos) {
		handleMousePositionInput(xPos, yPos);
		});

	sceneManager = new SceneManager();
	assetManager = new AssetManager();
	soundManager = new SoundManager();
	physicsManager = new PhysicsManager();
	entityManager = new EntityManager();
	componentManager = new ComponentManager();

#endif

	// load initial assets and set game scene
	assetManager->loadAssets();
	sceneManager->setInitialScene();

	// other initialization
	isRunning = window->isOpen();

	// ==== TEST CODE ===================================
	auto player = entityManager->createEntity();
	auto shape = CShape{ 10000, 10000 };
	auto transform = CTransform{ Vec2{50.0f, 50.0f} };
	componentManager->addTransformComp(player, transform);
	componentManager->addShapeComp(player, shape);
	// ==== END OF TEST CODE ============================
}

void Game::update(float deltaTime)
{
	// Update game logic and managers
	inputManager->update();
	sceneManager->update(deltaTime);
	physicsManager->update(deltaTime);
	//entityManager->update(deltaTime);
}

void Game::render()
{
	window->clear();

	// render the current scene and objects
	sceneManager->render();

	// ==== TEST CODE ===================================
	for (auto& e : entityManager->getEntities()) {
		if (componentManager->getShapeComp(e->getId())->has) {
			componentManager->getShapeComp(e->getId())->render(
				componentManager->getTransformComp(e->getId())->position, window->getShader()
			);
			std::cout << "Entity should be rendering now." << std::endl;
		}
		//std::cout << "looping through entities" << std::endl;
	}
	// ==== END OF TEST CODE ============================

	// additional rendering tasks like UI, HUD, etc.

	// Update window
	window->update();
}

void Game::run()
{
	initialize();

	while (isRunning)
	{
		float deltaTime = calculateDeltaTime(); // calculate time elapsed since last frame
		update(deltaTime);
		render();
	}

	shutdown();
}

void Game::handleKeyInput(int key, int action) {
	// Handle key input
	if (action == GLFW_PRESS) {
		std::cout << "Key pressed: " << key << std::endl;
	}
	else if (action == GLFW_RELEASE) {
		std::cout << "Key released: " << key << std::endl;
	}
}

void Game::handleMouseButtonInput(int button, int action, double xPos, double yPos) {
	// Handle mouse button input
	std::cout << "Mouse button input " << button << " happened." << std::endl;
}

void Game::handleMousePositionInput(double xPos, double yPos) {
	// Handle mouse move input
	std::cout << "Mouse position is " << xPos << "," << yPos << "." << std::endl;
}

void Game::shutdown()
{
	// Clean up and shut down the game
	sceneManager->clearScenes();
	assetManager->unloadAssets();
	window->close();

	// delete allocated memory
	delete sceneManager;
	delete inputManager;
	delete assetManager;
	delete soundManager;
	delete physicsManager;
	delete window;
}