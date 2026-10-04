#pragma once
#include "TimeManager.h"
#include "elsDecoratius.h"

class Decoracion {
private:
    float intervaloSpawn;
    float timer = 0.0f;

    Vector2 directionDefault;
    bool* _isSpawning;

public:
    Decoracion(float intervalo, Vector2 dir, bool* isSpawning)
        : intervaloSpawn(intervalo),
        directionDefault(dir),
        _isSpawning(isSpawning)
    {
    }

    void Update() {
        if (!_isSpawning || !(*_isSpawning)) return;

        timer += TIME.GetDeltaTime();
        if (timer < intervaloSpawn) return;

        timer = 0.0f;

        if (rand() % 2 == 0) return;

        elsDecoratius* deco = new elsDecoratius(Vector2(-1.f, 0.f));
        SPAWNER.SpawnObject(deco);
    }
};

