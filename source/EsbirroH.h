#pragma once
#include "Enemy.h"
#include <cmath>

class EsbirroHEnemy : public Enemy
{
private:
	float totalTime = 0.f;

public:
	EsbirroHEnemy(Vector2 startPos, Score* sharedScore, HordeTracker* tracker)
		: Enemy("resources/esbirroH.png", startPos, sharedScore, tracker)
	{
		life = 3;
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
