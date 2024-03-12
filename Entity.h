#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <unordered_map>
#include "EntityManager.h"
#include "Component.h"
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include "CTransform.h"

class Entity;
class Component;
class EntityManager;

using EntityID = std::size_t;

class Entity {
public:
	// Constructor
	Entity(EntityID id)
		: m_id(id) {}

	// Get entity ID
	EntityID getId() const {
		return m_id;
	}

private:
	EntityID m_id;
	bool m_isActive = true;
};
