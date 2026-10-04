#pragma once
#include "Enemy.h"
#include "TimeManager.h"
#include <cmath>

enum class MontaState
{
	ENTER,
	MOVE_LEFT,
	MOVE_RIGHT
};

class MontaEnemy : public Enemy
{
private:
	float totalTime = 0.f;
	float stateTime = 0.f;
	MontaState state = (MontaState::ENTER);
public:
	MontaEnemy(Vector2 startPos, Score* sharedScore, HordeTracker* tracker)
		: Enemy("resources/monta.png", startPos, sharedScore, tracker)
	{
		life = 4;
		scoreValue = 150;
	}

	void Update() override
	{
		float dt = TIME.GetDeltaTime();
		stateTime += dt;

		switch (state)
		{
		case MontaState::ENTER:UpdateEnter(); break;
		case MontaState::MOVE_LEFT:UpdateMoveLeft(); break;
		case MontaState::MOVE_RIGHT:UpdateMoveRight(); break;
		}
		Enemy::Update();
	}
	void ChangeState(MontaState newState)
	{
		state = newState;
		stateTime = 0.f;
	}
	void UpdateEnter()
	{
		_physics->SetVelocity({-117.5f,0.f});

		if (stateTime >= 3.5f)
			ChangeState(MontaState::MOVE_RIGHT);
	}
	void UpdateMoveRight()
	{
		_physics->SetVelocity({10.f,0.f});

		if (stateTime >= 0.5f)
			ChangeState(MontaState::MOVE_LEFT);
	}
	void UpdateMoveLeft()
	{
		_physics->SetVelocity({-180.f,0.f});

		if (stateTime >= 6.f)
		{
			tracker->OnEnemyRemoved();
			Destroy();
		}
	}
};
