#pragma once
#include "Enemy.h"
#include <cmath>

enum class BarbaroPatron
{
	ARRIBA,
	ABAJO,
};
enum class BarbaroState
{
	ENTER,
	IDLE,
	ATTACK,
	EXIT
};

class BarbaroEnemy : public Enemy
{
private:
	BarbaroPatron patron;
	BarbaroState state = BarbaroState::ENTER;
	float stateTime = 0.f;
	float verticalDir = 1.f;

public:
	BarbaroEnemy(Vector2 startPos, BarbaroPatron _patron, Player* _player, Score* sharedScore, HordeTracker* tracker)
		: Enemy("resources/barbaro.png", startPos, sharedScore, tracker), patron(_patron)
	{
		player = _player;
		life = 3;
		scoreValue = 150;
		verticalDir = (patron == BarbaroPatron::ARRIBA) ? 1.f : -1.f;
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
		case BarbaroState::ENTER:UpdateEnter(); break;
		case BarbaroState::IDLE:UpdateIdle(); break;
		case BarbaroState::ATTACK:UpdateAttack(); break;
		case BarbaroState::EXIT:UpdateExit(); break;
		}

		Enemy::Update();
	}
	void ChangeState(BarbaroState newState)
	{
		state = newState;
		stateTime = 0.f;
	}
	void UpdateEnter()
	{
		_physics->SetVelocity({ 0.f, 70.f * verticalDir });

		if (stateTime >= 1.5f)
			ChangeState(BarbaroState::IDLE);
	}
	void UpdateIdle()
	{
		_physics->SetVelocity({ 0.f, 0.f });

		if (stateTime >= 1.5f)
			ChangeState(BarbaroState::ATTACK);
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
			ChangeState(BarbaroState::EXIT);
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