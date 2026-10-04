#pragma once
#include "Enemy.h"
#include "TimeManager.h"
#include <cmath>

enum class BatPatron
{
	ARRIBA,
	ABAJO,
};

enum class BatState
{
	MOVE_LEFT,
	MOVE_CIRCLE,
	MOVE_RIGHT,
};

class BatEnemy : public Enemy
{
private:
	BatPatron patron;
	BatState state = BatState::MOVE_LEFT;
	float stateTime = 0.f;
	float verticalDir = 1.f;

public:
	BatEnemy(Vector2 startPos, BatPatron _patron, Score* sharedScore, HordeTracker* tracker)
		: Enemy("resources/bat.png", startPos, sharedScore, tracker), patron(_patron)
	{ 
		life = 2;
		scoreValue = 150;
		verticalDir = (patron == BatPatron::ARRIBA) ? 1.f : -1.f;
	}

	void Update() override
	{
		float dt = TIME.GetDeltaTime();
		stateTime += dt;

		switch (state)
		{
		case BatState::MOVE_LEFT:UpdateLeft(); break;
		case BatState::MOVE_CIRCLE:UpdateCircle(); break;
		case BatState::MOVE_RIGHT:UpdateRight(); break;
		}
		Enemy::Update();
	}
	void ChangeState(BatState newState)
	{
		state = newState;
		stateTime = 0.f;
	}
	void UpdateLeft()
	{
		_physics->SetVelocity({ -200.f, 0.f });

		if (stateTime >= 4.8f)
			ChangeState(BatState::MOVE_CIRCLE);
	}
	void UpdateCircle()
	{
		if (stateTime >= 0.f)
			_physics->SetVelocity({ 200.f, 200.f });
		if (stateTime >= 0.4f)
			_physics->SetVelocity({ -200.f, 200.f });
		if (stateTime >= 0.8f)
			_physics->SetVelocity({ -200.f, -200.f });
		if (stateTime >= 1.2f)
			_physics->SetVelocity({ 200.f, -200.f });
		if (stateTime >= 1.6f)
			_physics->SetVelocity({ 200.f, 200.f * verticalDir });

		if (stateTime >= 3.2f)
			ChangeState(BatState::MOVE_RIGHT);
	}
	void UpdateRight()
	{
		_physics->SetVelocity({ 200.f, 0.f });

		if (stateTime >= 3.2f)
		{
			tracker->OnEnemyRemoved();
			Destroy();
		}
	}
};
