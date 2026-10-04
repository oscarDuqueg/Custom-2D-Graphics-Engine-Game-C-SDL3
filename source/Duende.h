#pragma once
#include "Enemy.h"
#include "TimeManager.h"
#include <cmath>

enum class DuendeState
{
	HORIZONTAL,
	CIRCLE
};
enum class DuendePatron
{
	IZQUIERDA,
	DERECHA
};

class DuendeEnemy : public Enemy
{
private:
	float anguloDerecha = 360.f;
	float anguloIzquierda = -360.f;
	float totalTime = 0.f;
	float radio = 4.f;
	float velocidadAngular = 1.5f;
	float verticalDir = 1.f;
	float stateTime = 0.f;
	bool circulo = false;
	DuendePatron patron;
	DuendeState state = DuendeState::HORIZONTAL;
	Vector2 centro;

public:
	DuendeEnemy(Vector2 startPos, DuendePatron _patron, Score* sharedScore, HordeTracker* tracker)
		: Enemy("resources/duende.png", startPos, sharedScore,tracker), patron(_patron)
	{
		centro = startPos;
		life = 4;
		scoreValue = 150;
		verticalDir = (patron == DuendePatron::DERECHA) ? 1.f : -1.f;
	}

	void Update() override
	{
		float dt = TIME.GetDeltaTime();
		stateTime += dt;
		totalTime += dt;

		switch (state)
		{
		case DuendeState::HORIZONTAL:UpdateHorizontal(); break;
		case DuendeState::CIRCLE:UpdateCircle(dt); break;
		}

		if (totalTime >= 24.f)
		{
			tracker->OnEnemyRemoved();
			Destroy();
		}

		Enemy::Update();
	}

	void ChangeState(DuendeState newState)
	{
		state = newState;
		stateTime = 0.f;
	}
	void UpdateHorizontal()
	{
		_physics->SetVelocity({ -100.f * verticalDir, 0.f });

		if (stateTime >= 6.f && !circulo)
		{
			ChangeState(DuendeState::CIRCLE);
			circulo = true;
		}
	}
	void UpdateCircle(float dt)
	{
		_physics->SetVelocity({ 0.f, 0.f });

		float& anguloActual = (patron == DuendePatron::DERECHA) ? anguloDerecha : anguloIzquierda;

		centro = _transform->position;

		anguloActual += velocidadAngular * dt;

		_transform->position.x = centro.x + cos(anguloActual) * radio;
		_transform->position.y = centro.y + sin(anguloActual) * radio;

		if (stateTime >= 8.4f)
			ChangeState(DuendeState::HORIZONTAL);
	}
};
