#pragma once
#include "Enemy.h"
#include <cmath>

enum class GloboPatron
{
	DERECHA,
	IZQUIERDA,
};
enum class GloboState
{
	MOVE_RIGHT,
	MOVE_LEFT,
	ATTACK,
	EXIT,
};

class GloboEnemy : public Enemy
{
private:
	float totalTime = 0.f;
	GloboPatron patron;
	GloboState state = GloboState::MOVE_RIGHT;
	float verticalDir = 1.f;
	float stateTime = 0.f;

public:
	GloboEnemy(Vector2 startPos, GloboPatron _patron, Player* _player, Score* sharedScore, HordeTracker* tracker)
		: Enemy("resources/globo.png", startPos, sharedScore,tracker), patron(_patron)
	{
		player = _player;
		life = 4;
		scoreValue = 150;
		verticalDir = (patron == GloboPatron::DERECHA) ? 1.f : -1.f;
	}

	Vector2 GetDirectionToPlayer()
	{
		Vector2 dir = player->GetTransform()->position - _transform->position;
		dir.Normalize();
		return dir;
	}
	void Update() override
	{
		float dt = TIME.GetDeltaTime();
		stateTime += dt;

		switch (state)
		{
		case GloboState::MOVE_RIGHT:UpdateMoveRight(); break;
		case GloboState::MOVE_LEFT:UpdateMoveLeft(); break;
		case GloboState::ATTACK:UpdateAttack(); break;
		case GloboState::EXIT:UpdateExit(); break;
		}

		Enemy::Update();
	}
	void ChangeState(GloboState newState)
	{
		state = newState;
		stateTime = 0.f;
	}
	void UpdateMoveRight()
	{
		_physics->SetVelocity({ 150 * verticalDir,0 });

		if (stateTime >= 5.5f)
			ChangeState(GloboState::MOVE_LEFT);
	}
	void UpdateMoveLeft()
	{
		_physics->SetVelocity({ 130 * -verticalDir,0 });

		if (stateTime >= 2.5f)
			ChangeState(GloboState::ATTACK);
	}
	void UpdateAttack()
	{
		Vector2 dir = GetDirectionToPlayer();
		_physics->SetVelocity(dir * 120.f);

		if (stateTime >= 10.f)
			ChangeState(GloboState::EXIT);
	}
	void UpdateExit()
	{
		_physics->SetVelocity({0, 200 * verticalDir});

		if (stateTime >= 3.f)
		{
			tracker->OnEnemyRemoved();
			Destroy();
		}
	}
};
