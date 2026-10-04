#pragma once
#include "Enemy.h"
#include "TimeManager.h"
#include <cmath>

class HelicopteroEnemy : public Enemy
{
private:
	float totalTime = 0.0f;
public:

	HelicopteroEnemy(Vector2 startPos,Score* sharedScore, HordeTracker* tracker)
		: Enemy("resources/helicoptero.png", startPos, sharedScore, tracker)
	{
		life = 70;
		scoreValue = 5070;
		_type = TypeObject::BOSS;
	}

	void Update() override
	{
		totalTime += TIME.GetDeltaTime();
		_transform->scale = Vector2(3.f, 3.f);
		Enemy::Update();
		if (life <= 0)
			Destroy();
	}

	bool GetLife() { return life; }
};