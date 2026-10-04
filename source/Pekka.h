#pragma once
#include "Enemy.h"
#include "Player.h"
#include <cmath>

enum class PekkaPatron
{
	ARRIBA,
	ABAJO,
};
enum class PekkaState
{
	ENTER,
	IDLE,
	ATTACK,
	EXIT
};

class PekkaEnemy : public Enemy
{
private:
	PekkaPatron patron;
	PekkaState state = PekkaState::ENTER;
	float stateTime = 0.f;
	float verticalDir = 1.f;
public:
	PekkaEnemy(Vector2 startPos,  PekkaPatron _patron, Player* _player, Score* sharedScore, HordeTracker* tracker)
		: Enemy("resources/pekka.png", startPos, sharedScore, tracker), patron(_patron)
	{
		player = _player;
		life = 4;
		scoreValue = 150;
		verticalDir = (patron == PekkaPatron::ARRIBA) ? 1.f : -1.f;
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
		case PekkaState::ENTER:UpdateEnter(); break;
		case PekkaState::IDLE:UpdateIdle(); break;
		case PekkaState::ATTACK:UpdateAttack(); break;
		case PekkaState::EXIT:UpdateExit(); break;
		}

		Enemy::Update();
	}
	void ChangeState(PekkaState newState)
	{
		state = newState;
		stateTime = 0.f;
	}
	void UpdateEnter()
	{
		_physics->SetVelocity({ 0.f, 70.f * verticalDir });

		if (stateTime >= 1.5f)
			ChangeState(PekkaState::IDLE);
	}
	void UpdateIdle()
	{
		_physics->SetVelocity({ 0.f, 0.f });

		if (stateTime >= 1.5f)
			ChangeState(PekkaState::ATTACK);
	}
	void UpdateAttack()
	{
		float cycle = fmod(stateTime, 2.f);

		if (cycle < 1.f)
		{
			Vector2 dir = GetDirectionToPlayer();
			_physics->SetVelocity(dir * 120.f);
		}
		else
		{
			_physics->SetVelocity({ 0.f, 0.f });
		}

		if (stateTime >= 9.f)
			ChangeState(PekkaState::EXIT);
	}
	void UpdateExit()
	{
		_physics->SetVelocity({ 200.f * verticalDir, 0.f });

		if (stateTime >= 5.f)
		{
			tracker->OnEnemyRemoved();
			Destroy();
		}
	}
};
