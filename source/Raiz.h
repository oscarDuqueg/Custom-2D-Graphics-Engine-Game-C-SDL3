#pragma once
#include "Enemy.h"
#include "TimeManager.h"
#include <cmath>

enum class RaizState
{
	MOVE_LEFT,
	MOVE_RIGHT,
	MOVE_UP,
	MOVE_DOWN,
};

enum class RaizPatron
{
	ARRIBA,
	ABAJO,
};

class  RaizEnemy : public Enemy
{
private:
	RaizPatron patron;
	RaizState state = (RaizState::MOVE_RIGHT);
	float stateTime = 0.f;
	float verticalDir = 0.f;
	int steps = 0;

public:
	RaizEnemy(Vector2 startPos, RaizPatron _patron, Score* sharedScore, HordeTracker* tracker)
		: Enemy("resources/raiz.png", startPos, sharedScore, tracker), patron(_patron)
	{
		life = 3;
		scoreValue = 150;
		verticalDir = (patron == RaizPatron::ARRIBA) ? 1.f : -1.f;
	}

	void Update() override
	{
		float dt = TIME.GetDeltaTime();
		stateTime += dt;

		switch (state)
		{
		case RaizState::MOVE_LEFT:UpdateMoveLeft(); break;
		case RaizState::MOVE_RIGHT:UpdateMoveRight(); break;
		case RaizState::MOVE_UP:UpdateMoveUp(); break;
		case RaizState::MOVE_DOWN:UpdateMoveDown(); break;
		}

		Enemy::Update();
	}

	void ChangeState(RaizState newState)
	{
		state = newState;
		stateTime = 0.f;
	}
	void UpdateMoveRight()
	{
		_physics->SetVelocity({200,0});

		if(stateTime >= 5.8f && steps == 0)
			ChangeState(RaizState::MOVE_DOWN);
		if (stateTime >= 0.6f && steps == 1)
			ChangeState(RaizState::MOVE_UP);
		if (stateTime >= 0.6f && steps == 2)
			ChangeState(RaizState::MOVE_DOWN);
		if (stateTime >= 3.4f && steps == 3)
			ChangeState(RaizState::MOVE_DOWN);
	}
	void UpdateMoveLeft()
	{
		_physics->SetVelocity({-200,0});

		if(stateTime >= 4.6f && steps == 0)
		{
			ChangeState(RaizState::MOVE_DOWN);
			steps++;
		}
		if (stateTime >= 8.f && steps == 3)
		{
			tracker->OnEnemyRemoved();
			Destroy();
		}
	}
	void UpdateMoveUp()
	{
		_physics->SetVelocity({0,-200 * verticalDir});

		if(stateTime >= 6.2f && steps == 0)
			ChangeState(RaizState::MOVE_DOWN);
		if (stateTime >= 0.6f && steps == 1)
		{
			ChangeState(RaizState::MOVE_RIGHT);
			steps++;
		}
	}
	void UpdateMoveDown()
	{
		_physics->SetVelocity({0,+200 * verticalDir});

		if(stateTime >= 1.f && steps == 0)
			ChangeState(RaizState::MOVE_LEFT);
		if (stateTime >= 0.6 && steps == 1)
			ChangeState(RaizState::MOVE_RIGHT);
		if (stateTime >= 0.6f && steps == 2)
		{
			ChangeState(RaizState::MOVE_RIGHT);
			steps++;
		}
		if (stateTime >= 1.2f && steps == 3)
			ChangeState(RaizState::MOVE_LEFT);
	}
};