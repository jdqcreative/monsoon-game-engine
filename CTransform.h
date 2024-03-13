#pragma once
#include "Vec2.h"
#include "Component.h"

class CTransform : public Component {
public:
	bool has = false;
	Vec2 position = {0.0f, 0.0f};
	Vec2 prevPosition = {0.0f, 0.0f};
	Vec2 scale = {1.0f, 1.0f};
	Vec2 velocity = {0.0f, 0.0f};
	float rotation = 0.0f;

	CTransform() {}

	CTransform(const Vec2& pos)
		: position(pos), prevPosition(pos) {}

	CTransform(const Vec2& pos, Vec2& vel)
		: position(pos), prevPosition(pos), velocity(vel) {}

	CTransform(const Vec2& pos, Vec2& vel, float rot)
		: position(pos), prevPosition(pos), velocity(vel), rotation(rot) {}

	CTransform(const Vec2& pos, Vec2& vel, float rot, Vec2& scal)
		: position(pos), prevPosition(pos), velocity(vel), rotation(rot), scale(scal) {}
};