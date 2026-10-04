#pragma once
#include "Enemy.h"
#include "TimeManager.h"
#include "Esqueleto.h"
#include <cmath>
#include <vector>

std::vector<EsqueletoEnemy*> esqueletos;

enum class BrujaState
{
    ENTRANDO,
    ESPIRAL,
    SALIENDO
};

class BrujaEnemy : public Enemy
{
private:
    BrujaState state = BrujaState::ENTRANDO;

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
    BrujaEnemy(Vector2 startPos, Score* sharedScore, HordeTracker* tracker)
        : Enemy("resources/bruja.png", startPos, sharedScore, tracker)
    {
        centro = { startPos.x, 300.f };
        life = 15;
        scoreValue = 150;
    }

    void Update() override
    {
        float dt = TIME.GetDeltaTime();

        switch (state)
        {
        case BrujaState::ENTRANDO:UpdateEntrando(dt);break;
        case BrujaState::ESPIRAL:UpdateEspiral(dt);break;
        case BrujaState::SALIENDO:UpdateSaliendo(dt);break;
        }

        if (life <= 0)
            OnDeath();

        Enemy::Update();
    }
    void ChangeState(BrujaState newState)
    {
        state = newState;

        if (newState == BrujaState::ESPIRAL)
        {
            centro.x = _transform->position.x;
            centro.y = _transform->position.y + radioInicial;

            radioActual = radioInicial;
            anguloTotal = 0.f;
            angulo = -3.14159f / 2.f;
        }
    }

    void KillMinions()
    {
        for (auto& esqueleto : esqueletos)
            esqueleto->Death();
    }

    void OnDeath()
    {
        KillMinions();
        Destroy();
    }

    void UpdateEntrando(float dt)
    {
        _transform->position.y += velocidadEntrada * dt;

        if (_transform->position.y >= 150.f)
            ChangeState(BrujaState::ESPIRAL);
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
            ChangeState(BrujaState::SALIENDO);
    }

    void UpdateSaliendo(float dt)
    {
        _transform->position.y -= velocidadSalida * dt;

        if (_transform->position.y < -100.f)
        {
            tracker->OnEnemyRemoved();
            Destroy();
        }
    }
};
