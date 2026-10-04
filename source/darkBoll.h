#pragma once
#include "ImageObject.h"
#include "RenderManager.h"
#include "Player.h"
#include "TimeManager.h"
#include "PowerUp.h"

class DarkBall : public ImageObject {
private:
	int damage = 1;
	float loTime = 0.02f;
public:
	DarkBall(Transform* playerTransform, Vector2 direction) : ImageObject("resources/darkBoll.png", Vector2(0.f, 0.f), Vector2(306.f, 562.f)) {

		_transform->position = playerTransform->position + Vector2(60.f, -20.f); //offset diferente puesto que es el laser
		_transform->scale = Vector2(1.f, 1.f);
		_transform->rotation = 0.f;

		direction.Normalize();
		_physics->SetVelocity(direction * 600.f);

		_physics->SetLinearDrag(0.f);
		_physics->SetAngularDrag(0.f);
		_type = TypeObject::PLAYERBULLET;

		_physics->SetVelocity(direction * 600.f);
		_physics->AddCollider(new AABB(_transform->position, _transform->size));
	}

	~DarkBall() = default;

	void Update() override {
		loTime += TIME.GetDeltaTime();

		if (loTime >= 0.8f)
		{
			Object::Destroy();
			loTime = 0;
		}
		Object::Update();
	}

	void OnCollision(Object* other) override
	{
		if (other->GetObjectType() == TypeObject::WALL)
		{
			Object::Destroy();
		}

		if (other->GetObjectType() == TypeObject::ENEMY || other->GetObjectType() == TypeObject::BOSS)
		{
			Object::Destroy();
			other->LoseLife(damage);
		}
	}
};
