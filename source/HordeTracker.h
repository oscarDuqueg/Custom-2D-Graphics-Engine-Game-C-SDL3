#pragma once
#include <iostream>
#include "PowerUp.h"
#include "Player.h"

class HordeTracker
{
private:
    int enemiesAlive = 0;
    bool hordeCleared = false;
    Vector2 lastKnownEnemyPosition = Vector2(400.f, 300.f);

public:
    void ReportLastKnownPosition(const Vector2& pos)
    {
        lastKnownEnemyPosition = pos;
    }

    void Reset()
    {
        enemiesAlive = 0;
        hordeCleared = false;
    }

    void OnEnemySpawned(int enemies)
    {
        enemiesAlive = enemies;
    }
    void OnEnemyRemoved()
    {
        enemiesAlive--;
        if (enemiesAlive <= 0 && !hordeCleared)
            hordeCleared = true;
    }

    void OnEnemyKilled()
    {
        enemiesAlive--;

        if (enemiesAlive <= 0 && !hordeCleared)
        {
            hordeCleared = true;
            OnHordeCleared();
        }
    }

    void OnHordeCleared()
    {
        SpawnPowerUp();
    }

    void SpawnPowerUp()
    {
        PowerUp* pow = new PowerUp(Vector2(lastKnownEnemyPosition));
        SPAWNER.SpawnObject(pow);
    }

    bool IsHordeCleared() const { return hordeCleared; }

};
