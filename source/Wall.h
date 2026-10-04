#pragma once
#include "ImageObject.h"
#include "RigidBody.h"

class Wall : public ImageObject
{
public:
	Wall(Vector2 position, Vector2 size)
		: ImageObject("resources/WallX.png", position, size)
	{
		_transform->position = position;
		_transform->size = size;
		_physics->AddCollider(new AABB(_transform->position, _transform->size));
		_type = TypeObject::WALL;
	}

	~Wall() {}

	void Update() override {
		Object::Update();
	}

	RigidBody* GetRigidBody() const { return _physics.get(); }
};
