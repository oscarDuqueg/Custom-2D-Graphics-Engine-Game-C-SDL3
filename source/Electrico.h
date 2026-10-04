#pragma once
#include "Enemy.h"
#include "TimeManager.h"
#include <cmath>

enum class ElectricoState
{
	MOVE_UP,
	MOVE_DOWN,
	MOVE_RIGHT,
	MOVE_CIRCLE
};

class ElectricoEnemy : public Enemy
{
private:
	float angulo = -360.f;
	float radio = 4.f;
	float velocidadAngular = 1.5f;
	float totalTime = 0.f;
	float stateTime = 0.f;
	int steps = 0;
	Vector2 centro;
	ElectricoState state = ElectricoState::MOVE_RIGHT;

public:
	ElectricoEnemy(Vector2 startPos, Score* sharedScore, HordeTracker* tracker)
		: Enemy("resources/electrico.png", startPos, sharedScore, tracker)
	{
		centro = startPos;
		life = 3;
		scoreValue = 150;
	}

	void Update() override
	{
		float dt = TIME.GetDeltaTime();
		totalTime += dt;
		stateTime += dt;

		switch (state)
		{
		case ElectricoState::MOVE_RIGHT: UpdateRight(); break;
		case ElectricoState::MOVE_DOWN: UpdateDown(); break;
		case ElectricoState::MOVE_UP:UpdateUp(); break;
		case ElectricoState::MOVE_CIRCLE:UpdateCircle(dt); break;
		}

		if (totalTime >= 22.f)
		{
			tracker->OnEnemyRemoved();
			Destroy();
		}

		Enemy::Update();
	}

	void ChangeState(ElectricoState newState)
	{
		state = newState;
		stateTime = 0.f;
	}
	void UpdateRight()
	{
		_physics->SetVelocity({ 180.f, 0.f });

		if (stateTime >= 1.6 && steps == 0)
		{
			ChangeState(ElectricoState::MOVE_DOWN);
			steps++;
		}
		if (stateTime >= 1.3f && steps == 1)
		{
			ChangeState(ElectricoState::MOVE_UP);
			steps++;
		}
		if (stateTime >= 1.3f && steps == 2)
		{
			ChangeState(ElectricoState::MOVE_CIRCLE);
			steps++;
		}
		if (stateTime >= 0.5f && steps == 3)
		{
			ChangeState(ElectricoState::MOVE_CIRCLE);
			steps++;
		}
	}
	void UpdateDown()
	{
		_physics->SetVelocity({ 0.f, 180.f });

		if (stateTime >= 3.1f)
			ChangeState(ElectricoState::MOVE_RIGHT);
	}
	void UpdateUp()
	{
		_physics->SetVelocity({ 0.f, -180.f });

		if (stateTime >= 1.7f)
			ChangeState(ElectricoState::MOVE_RIGHT);
	}
	void UpdateCircle(float dt)
	{
		_physics->SetVelocity({ 0.f, 0.f });

		centro = _transform->position;

		angulo += velocidadAngular * dt;

		_transform->position.x = centro.x + cos(angulo) * radio;
		_transform->position.y = centro.y + sin(angulo) * radio;

		if (stateTime >= 4.2f)
			ChangeState(ElectricoState::MOVE_RIGHT);
	}
};


