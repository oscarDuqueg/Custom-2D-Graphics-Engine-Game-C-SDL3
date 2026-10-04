#pragma once
#include "Enemy.h"
#include "TimeManager.h"
#include <cmath>

enum class ValquiriaState
{
	ENTER,
	IDLE,
	EXIT,
};

class ValquiriaEnemy : public Enemy
{
private:
	int steps = 0.f;
	float stateTime = 0.f;
	ValquiriaState state = ValquiriaState::ENTER;
public:
	ValquiriaEnemy(Vector2 startPos,Score* sharedScore, HordeTracker* tracker)
		: Enemy("resources/valquiria.png", startPos, sharedScore, tracker)
	{
		life = 3;
		scoreValue = 150;
	}

	void Update() override
	{
		float dt = TIME.GetDeltaTime();
		stateTime += dt;

		switch(state)
		{
		case ValquiriaState::ENTER:UpdateEnter(); break;
		case ValquiriaState::IDLE:UpdateIdle(); break;
		case ValquiriaState::EXIT:UpdateExit(); break;
		}
		
		Enemy::Update();
	}

	void ChangeState(ValquiriaState newState)
	{
		state = newState;
		stateTime = 0.f;  
	}
	void UpdateEnter()
	{
		_physics->SetVelocity({-500.f,0.f});

		if (stateTime >= 1.6f && steps == 0)
		{
			ChangeState(ValquiriaState::IDLE);
			steps++;
		}
		if(stateTime >= 2.f && steps == 1)
		{
			ChangeState(ValquiriaState::IDLE);
			steps++;
		}
	}
	void UpdateIdle()
	{
		_physics->SetVelocity({0.f,0.f});

		if (stateTime >= 1.4f)
			ChangeState(ValquiriaState::EXIT);
	}
	void UpdateExit()
	{
		_physics->SetVelocity({+500.f,0.f});

		if (stateTime >= 2.f && steps == 1)
			ChangeState(ValquiriaState::ENTER);
		if (stateTime >= 2.f && steps == 2)
		{
			Destroy();
			tracker->OnEnemyRemoved();
		}
	}
};