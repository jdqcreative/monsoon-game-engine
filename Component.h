#pragma once
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"

class Entity;
class Component;
class EntityManager;

class Component {
public:
	virtual ~Component() = default;
	virtual void init() {}
	virtual void update(float deltaTime) {}
	virtual void render(const glm::mat4& parentTransform = glm::mat4(1.0f)) {}
};