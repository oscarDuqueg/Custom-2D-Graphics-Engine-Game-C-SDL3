#pragma once
#include "Enemy.h"
#include "TimeManager.h"
#include <vector>

struct Step {
    float duration;
    Vector2 velocity;
};

enum class lavaPatron {
    ARRIBA, ABAJO, DERECHA, IZQUIERDA,
    ARRIBAIZQUIERDA, ARRIBADERECHA, ABAJOIZQUIERDA, ABAJODERECHA,
};

class LavaEnemy : public Enemy
{
private:
    lavaPatron patron;
    std::vector<Step> steps;
    float stepTime = 0.f;
    int currentStep = 0;
    float totalTime = 0.f;
public:
    LavaEnemy(Vector2 startPos, lavaPatron _patron, Score* sharedScore, HordeTracker* tracker)
        : Enemy("resources/lava.png", startPos, sharedScore, tracker), patron(_patron)
    {
        life = 4;
        scoreValue = 150;

        switch (patron)
        {
        case lavaPatron::ABAJO: steps = {{8.f, {80,0}}, {2.f, {0,80}}, {2.f, {0,0}}, {2.f, {0,-80}}, {2.f, {80,0}}}; break;
        case lavaPatron::ARRIBA: steps = {{8.f, {80,0}}, {2.f, {0,-80}}, {2.f, {0,0}}, {2.f, {0,80}}, {2.f, {80,0}}}; break;
        case lavaPatron::DERECHA: steps = {{8.f, {80,0}}, {2.f, {80,0}}, {2.f, {0,0}}, {2.f, {-80,0}}, {2.f, {80,0}}}; break;
        case lavaPatron::IZQUIERDA: steps = {{8.f, {80,0}}, {2.f, {-80,0}}, {2.f, {0,0}}, { 2.f, {80,0}}, {2.f, {80,0}}}; break;
        case lavaPatron::ABAJODERECHA:steps = {{8.f, {80,0}}, {2.f, {80,80}}, {2.f, {0,0}}, {2.f, {-80,-80}}, {2.f, {80,0}}}; break;
        case lavaPatron::ARRIBADERECHA: steps = {{8.f, {80,0}}, {2.f, {80,-80}}, {2.f, {0,0}}, {2.f, {-80,80}}, {2.f, {80,0}}}; break;
        case lavaPatron::ABAJOIZQUIERDA: steps = {{8.f, {80,0}}, {2.f, {-80,80}}, {2.f, {0,0}}, {2.f, {80,-80}}, {2.f, {80,0}}}; break;
        case lavaPatron::ARRIBAIZQUIERDA: steps = {{8.f, {80,0}}, {2.f, {-80,-80}}, {2.f, {0,0}}, {2.f, {80,80}}, {2.f, {80,0}}}; break;
        default: break;
        }
    }

    void Update() override
    {
        float dt = TIME.GetDeltaTime();
        totalTime += dt;

        if (currentStep < steps.size())
        {
            stepTime += dt;
            _physics->SetVelocity(steps[currentStep].velocity);

            if (stepTime >= steps[currentStep].duration)
            {
                stepTime = 0.f;
                currentStep++;
            }
        }
        if (totalTime >= 23.f)
        {
            tracker->OnEnemyRemoved();
            Destroy();
        }
        
        Enemy::Update();
    }
};
