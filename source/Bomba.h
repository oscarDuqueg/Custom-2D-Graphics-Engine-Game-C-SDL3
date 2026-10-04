#pragma once
#pragma once
#include "Enemy.h"
#include <cmath>

class BombaEnemy : public Enemy
{
private:
	float totalTime = 0.f;
public:
	BombaEnemy(Vector2 startPos, Score* sharedScore, HordeTracker* tracker)
		: Enemy("resources/bomba.png", startPos, sharedScore, tracker)
	{
		life = 1000;
	}

	void Update() override
	{
		totalTime += TIME.GetDeltaTime();
		_physics->SetVelocity({-200,0});
		Object::Update();
		_transform->scale = Vector2(0.3f, 0.3f);
		if (totalTime >= 6.f)
			Destroy();
	}
};
