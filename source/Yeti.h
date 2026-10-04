#pragma once
#include "Enemy.h"
#include <cmath>
enum class YetiState
{
	MOVE_LEFT,
	MOVE_LEFT_CIRCLES
};

class YetiEnemy : public Enemy
{
private:
	float angulo = 0.f;
	float radio = 3.f;
	float velocidadAngular = 2.f;
	float totalTime = 0.f;
	float stateTime = 0.f;
	Vector2 centro;
	YetiState state = YetiState::MOVE_LEFT;

public:
	YetiEnemy(Vector2 startPos,  Score* sharedScore, HordeTracker* tracker)
		: Enemy("resources/yeti.png", startPos, sharedScore,tracker)
	{
		centro = startPos;
		life = 2;
		scoreValue = 150;
	}

	void Update() override
	{
		float dt = TIME.GetDeltaTime();
		stateTime += dt;
		totalTime += dt;

		switch (state)
		{
		case YetiState::MOVE_LEFT:UpdateMoveLeft(); break;
		case YetiState::MOVE_LEFT_CIRCLES:UpdateMoveLeftCircles(dt); break;
		}

		Enemy::Update();
	}

	void ChangeState(YetiState newState)
	{
		state = newState;
		stateTime = 0.f;
	}
	void UpdateMoveLeft()
	{
		_physics->SetVelocity({ -30.f,0.f });

		if (stateTime >= 5.5f)
			ChangeState(YetiState::MOVE_LEFT_CIRCLES);
	}
	void UpdateMoveLeftCircles(float dt)
	{
		_physics->SetVelocity({ -30.f,0.f });

		centro = _transform->position;

		angulo += velocidadAngular * dt;

		_transform->position.x = centro.x + cos(angulo) * radio;
		_transform->position.y = centro.y + sin(angulo) * radio;

		if (stateTime >= 40.f)
		{
			tracker->OnEnemyRemoved();
			Destroy();
		}
	}
};
