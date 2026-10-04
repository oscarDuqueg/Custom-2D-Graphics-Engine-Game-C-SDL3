#pragma once
#include "ImageObject.h"
#include "RigidBody.h"

class WallY : public ImageObject
{
public:
	WallY(Vector2 position, Vector2 size)
		: ImageObject("resources/WallY.png", position, size)
	{
		_transform->position = position;
		_transform->size = size;
		_physics->AddCollider(new AABB(_transform->position, _transform->size));
		_type = TypeObject::WALL;
	}

	~WallY() {}

	void Update() override {
		Object::Update();
	}

	RigidBody* GetRigidBody() const { return _physics.get(); }
};

