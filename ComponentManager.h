#pragma once
#include <vector>
#include "CTransform.h"
#include "CShape.h"

using EntityID = std::size_t;

class ComponentManager {
public:
	ComponentManager() {
		// preallocate space for components
		m_transformComponents.resize(1000);
		m_shapeComponents.resize(1000);
	}

	// Add component functions
	void addTransformComp(EntityID entityID, CTransform transform) {

		m_transformComponents[entityID] = std::move(transform);
		m_transformComponents[entityID].has = true;
	}

	void addShapeComp(EntityID entityID, CShape shape) {

		m_shapeComponents[entityID] = std::move(shape);
		m_shapeComponents[entityID].has = true;
	}

	// Get component functions
	CTransform* getTransformComp(EntityID entityID) {
		if (entityID < m_transformComponents.size() && m_transformComponents[entityID].has) {
			return &m_transformComponents[entityID];
		}
		return nullptr;
	}

	CShape* getShapeComp(EntityID entityID) {
		if (entityID < m_shapeComponents.size() && m_shapeComponents[entityID].has) {
			return &m_shapeComponents[entityID];
		}
		return nullptr;
	}

private:
	std::vector<CTransform> m_transformComponents;
	std::vector<CShape>     m_shapeComponents;
};