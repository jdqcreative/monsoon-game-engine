#pragma once
#include <vector>
#include <memory>
#include <unordered_map>
#include "Entity.h"

class Entity;
class Component;
class EntityManager;

using ComponentID = std::size_t;

class EntityManager {
public:
	// Create entity and return its ID
	EntityID createEntity() {
		EntityID id = m_nextEntityID++;
		m_entities.emplace_back(std::make_unique<Entity>(id));
		return id;
	}

	std::vector<std::unique_ptr<Entity>>& getEntities() {
		return m_entities;
	}

	void destroyEntity(EntityID id) {
		// TODO
	}

private:
	EntityID m_nextEntityID = 0;
	std::vector<std::unique_ptr<Entity>> m_entities;
};