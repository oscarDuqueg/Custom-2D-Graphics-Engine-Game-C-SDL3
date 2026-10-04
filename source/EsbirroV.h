#pragma once
#include "Enemy.h"
#include "TimeManager.h"
#include <cmath>

enum class EsbirroVState
{
	MOVE_UP,
	IDLE
};

class EsbirroVEnemy : public Enemy
{
private:
	float totalTime = 0.f;
	float stateTime = 0.f;
	EsbirroVState state = EsbirroVState::MOVE_UP;

public:
	EsbirroVEnemy(Vector2 startPos, Score* sharedScore, HordeTracker* tracker)
		: Enemy("resources/esbirroV.png",startPos, sharedScore,tracker)
	{
		life = 3;
		scoreValue = 150;
	}

	void Update() override
	{
		float dt = TIME.GetDeltaTime();
		stateTime += dt;
		totalTime += dt;

		switch (state)
		{
		case EsbirroVState::MOVE_UP:UpdateUp(); break;
		case EsbirroVState::IDLE:UpdateIdle(); break;
		}
		
		if (totalTime >= 16.f)
		{
			tracker->OnEnemyRemoved();
			Destroy();
		}

		Enemy::Update();
	}
	void ChangeState(EsbirroVState newState)
	{
		state = newState;
		stateTime = 0.f;
	}
	void UpdateUp()
	{
		_physics->SetVelocity({ 0.f, -150.f });

		if (stateTime >= 1.f)
			ChangeState(EsbirroVState::IDLE);
	}
	void UpdateIdle()
	{
		_physics->SetVelocity({ 0.f, 0.f });

		if (stateTime >= 1.f)
			ChangeState(EsbirroVState::MOVE_UP);
	}
};