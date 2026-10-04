#pragma once
#include "ImageObject.h"
#include "RenderManager.h"
#include "Player.h"
#include "TimeManager.h"
#include "PowerUp.h"

class PlayerBullet : public ImageObject {
private:
	int damage = 1;
	float totalTime = 0.02f;
public: 
	PlayerBullet(Transform* playerTransform, Vector2 direction, Vector2 offset) : ImageObject("resources/bolaDeFuego.png", Vector2(0.f, 0.f), Vector2(306.f, 562.f)) {

		_transform->position = playerTransform->position + Vector2(60.f, -10.f) + offset;
		_transform->scale = Vector2(0.3f, 0.3f);
		_transform->rotation = 0.f;

		direction.Normalize();
		_physics->SetVelocity(direction * 600.f);

		_physics->SetLinearDrag(0.f);
		_physics->SetAngularDrag(0.f);
		_type = TypeObject::PLAYERBULLET;

		_physics->AddCollider(new AABB(_transform->position, _transform->size));
	}

	~PlayerBullet() = default;

	void Update() override 
	{
		totalTime += TIME.GetDeltaTime();

		if (totalTime >= 3.f)
		{
			Object::Destroy();
			totalTime = 0;
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

		if (other->GetObjectType() == TypeObject::POWERUP)
		{
			other->LoseLife(damage);
			Object::Destroy();

		}
	}
};
