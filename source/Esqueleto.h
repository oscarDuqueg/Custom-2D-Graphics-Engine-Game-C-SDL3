#pragma once
#include "Enemy.h"
#include "TimeManager.h"
#include <cmath>

enum class EsqueletoState
{
    ENTRANDO,
    ESPIRAL,
    SALIENDO
};

class EsqueletoEnemy : public Enemy
{
private:
    EsqueletoState state = EsqueletoState::ENTRANDO;
    float stateTime = 0.f;

    float angulo = -3.14159f / 2.f;
    float velocidadAngular = 1.f;

    float radioInicial = 350.f;
    float radioActual = radioInicial;
    float velocidadEspiral = 10.f;

    float anguloTotal = 0.f;
    int maxVueltas = 5;

    Vector2 centro;

    float velocidadEntrada = 120.f;
    float velocidadSalida = 150.f;

public:
    EsqueletoEnemy(Vector2 startPos, Score* sharedScore, HordeTracker* tracker)
        : Enemy("resources/esqueleto.png", startPos, sharedScore, tracker)
    {
        centro = startPos;
        life = 2000;
        scoreValue = 0;
    }

    void Update() override
    {
        float dt = TIME.GetDeltaTime();
        stateTime += dt;

        switch (state)
        {
        case EsqueletoState::ENTRANDO:UpdateEntrando(dt); break;
        case EsqueletoState::ESPIRAL:UpdateEspiral(dt); break;
        case EsqueletoState::SALIENDO:UpdateSaliendo(dt); break;
        }

        Enemy::Update();
    }

    void ChangeState(EsqueletoState newState)
    {
        state = newState;

        if (newState == EsqueletoState::ESPIRAL)
        {
            centro.x = _transform->position.x;
            centro.y = _transform->position.y + radioInicial;

            radioActual = radioInicial;
            anguloTotal = 0.f;
            angulo = -3.14159f / 2.f;
        }
    }

    void Death()
    {
        life = 0;
        Destroy();
    }

private:
    void UpdateEntrando(float dt)
    {
        _transform->position.y += velocidadEntrada * dt;

        if (_transform->position.y >= 150.f)
            ChangeState(EsqueletoState::ESPIRAL);
    }

    void UpdateEspiral(float dt)
    {
        angulo += velocidadAngular * dt;
        anguloTotal += std::abs(velocidadAngular * dt);
        radioActual -= velocidadEspiral * dt;
        if (radioActual < 0) radioActual = 0;

        _transform->position.x = centro.x + cos(angulo) * radioActual;
        _transform->position.y = centro.y + sin(angulo) * radioActual;

        if (anguloTotal >= maxVueltas * 2.f * 3.14159f || radioActual <= 0)
            ChangeState(EsqueletoState::SALIENDO);
    }

    void UpdateSaliendo(float dt)
    {
        _transform->position.y -= velocidadSalida * dt;

        if (_transform->position.y < -100.f)
            Destroy();
    }
};
