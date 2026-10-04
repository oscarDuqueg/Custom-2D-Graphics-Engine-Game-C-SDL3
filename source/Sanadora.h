#pragma once
#include "Enemy.h"
#include "TimeManager.h"
#include <cmath>

class SanadoraEnemy : public Enemy
{
private:
	float totalTime = 0.02f;
public:
	SanadoraEnemy(Vector2 startPos, Score* sharedScore, HordeTracker* tracker)
		: Enemy("resources/sanadora.png", startPos,sharedScore, tracker)
	{
		life = 4;
		scoreValue = 750;
	}

	void Update() override
	{
		totalTime += TIME.GetDeltaTime();

		//No hace falta maquina de estados para un enemigo que solo tiene un comportamiento
		_physics->SetVelocity({ 0.f, -200.f });

		if (totalTime >= 8.f)
		{
			tracker->OnEnemyRemoved();
			Destroy();
		}
		Enemy::Update();
	}
};
