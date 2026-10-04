#pragma once
#include "Enemy.h"
#include <cmath>

class RompemuroEnemy : public Enemy
{
private:
	float totalTime = 0.02f;
public:
	RompemuroEnemy(Vector2 startPos, Score* sharedScore, HordeTracker* tracker)
		: Enemy("resources/rompemuro.png", startPos, sharedScore, tracker)
	{
		life = 4;
		scoreValue = 150;
	}

	void Update() override
	{
		totalTime += TIME.GetDeltaTime();

		//No hace falta maquina de estados para un enemigo que solo tiene un comportamiento
		_physics->SetVelocity({ -200.f, 0.f });

		if (totalTime >= 8.f)
		{
			tracker->OnEnemyRemoved();
			Destroy();
		}

		Enemy::Update();
	}
};
