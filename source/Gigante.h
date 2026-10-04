#pragma once
#include "Enemy.h"
#include <cmath>
#include "TimeManager.h"

enum class GiganteState
{
	MOVE_HORIZONTAL,
	MOVE_DIAGONAL,
};
enum class GigantePatron
{
	ARRIBA,
	ABAJO
};

class GiganteEnemy : public Enemy
{
private:
	GiganteState state = GiganteState::MOVE_HORIZONTAL;
	GigantePatron patron;
	float stateTime = 0.f;
	float verticalDir = 1.f;
	float totalTime = 0.f;
public:
	GiganteEnemy(Vector2 startPos, GigantePatron _patron, Score* sharedScore, HordeTracker* tracker)
		: Enemy("resources/gigante.png",startPos, sharedScore,tracker), patron(_patron)
	{
		life = 7;
		scoreValue = 750;
		verticalDir = (patron == GigantePatron::ARRIBA) ? 1.f : -1.f;
	}

	void Update() override
	{
		float dt = TIME.GetDeltaTime();
		stateTime += dt;
		totalTime += dt;

		switch (state)
		{
		case GiganteState::MOVE_HORIZONTAL:UpdateHorizontal(); break;
		case GiganteState::MOVE_DIAGONAL:UpdateDiagonal(); break;
		}

		if (totalTime >= 12.f)
		{
			tracker->OnEnemyRemoved();
			Destroy();
		}

		Enemy::Update();
	}
	void ChangeState(GiganteState newState)
	{
		state = newState;
		stateTime = 0.f;
	}
	void UpdateHorizontal()
	{
		_physics->SetVelocity({ -117.5f, 0.f });

		if (stateTime >= 3.f)
			ChangeState(GiganteState::MOVE_DIAGONAL);
	}
	void UpdateDiagonal()
	{
		_physics->SetVelocity({ -117.5f, 100.f * verticalDir });

		if (stateTime >= 6.f)
			ChangeState(GiganteState::MOVE_HORIZONTAL);
	}
};