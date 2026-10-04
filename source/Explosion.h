#pragma once
#include "ImageObject.h"
#include "RenderManager.h"
#include "Player.h"
#include "TimeManager.h"
#include "PowerUp.h"

class Explosion : public ImageObject {
private:
	int damage = 1;
	float loTime = 0.02f;
public:
	Explosion(Transform* enemyTransform) : ImageObject("resources/loboom.png", Vector2(0.f, 0.f), Vector2(306.f, 562.f)) {

		_transform->position = enemyTransform->position;
		_transform->scale = Vector2(1.f, 1.f);
		_transform->rotation = 0.f;

		_physics->SetLinearDrag(0.f);
		_physics->SetAngularDrag(0.f);
		_type = TypeObject::BASE;
	}

	~Explosion() = default;

	void Update() override {
		loTime += TIME.GetDeltaTime();

		if (loTime >= 0.3f)
		{
			Object::Destroy();
			loTime = 0;
		}
		Object::Update();
	}
};
