#pragma once

#include <vector>
#include <functional>
#include "Vector2.h"
#include "TimeManager.h"
#include "Spawner.h"
#include "HordeTracker.h"
#include "Score.h"
#include "Barbaro.h"
#include "Bat.h"
#include "Bruja.h"
#include "EsbirroH.h"
#include "EsbirroV.h"
#include "Gigante.h"
#include "Lava.h"
#include "Yeti.h"
#include "Roca.h"
#include "Golem.h"

struct SpawnEvent
{
    float time;
    std::function<void()> action;
};

class Gameplay;

class Horde
{
private:
    bool waitingNextHorde = false;
    float waitTimer = 0.f;
    float waitBetweenHordes = 2.0f;
    int currentHorde = 0;
    Player* Target = nullptr;

public:
    Horde(Score* score, Player* playerPointer) 
        : score(score), Target(playerPointer)
    {
        currentHorde = 0;
        AdvanceToNextHorde();
    }

    void Update()
    {
        if (tracker.IsHordeCleared())
        {
            waitTimer += TIME.GetDeltaTime();

            if (waitTimer >= waitBetweenHordes)
            {
                AdvanceToNextHorde();
                waitTimer = 0.f;
            }
            return;
        }

        currentTime += TIME.GetDeltaTime();

        while (currentEvent < events.size() && events[currentEvent].time <= currentTime)
        {
            events[currentEvent].action();
            currentEvent++;
        }
    }
    void Reset()
    {
        currentTime = 0.f;
        currentEvent = 0;
    }
protected:

    void StartHorde(int enemyCount)
    {
        tracker.Reset();
        tracker.OnEnemySpawned(enemyCount);

        currentTime = 0.f;
        currentEvent = 0;
        waitingNextHorde = false;
    }
    void AdvanceToNextHorde()
    {
        currentHorde++;

        events.clear();

        switch (currentHorde)
        {
        case 1:BuildHorde1(); StartHorde(8); break;
        case 2:BuildHorde2(); StartHorde(2); break;
        case 3:BuildHorde3(); StartHorde(7); break;
        case 4:BuildHorde4(); StartHorde(1); break;
        case 5:BuildHorde5(); StartHorde(8); break;
        case 6:BuildHorde6(Target); StartHorde(8); break;
        case 7:BuildHorde7(); StartHorde(2); break;
        case 8:BuildHorde8(); StartHorde(8); break;
        case 9:BuildHorde9(); StartHorde(8); break;
        case 10:BuildHorde10(); StartHorde(8); break;
        case 11:BuildHorde11(); StartHorde(2); break;
        case 12:BuildHorde12(); StartHorde(7); break;
        case 13:BuildHorde13(); StartHorde(2); break;
        }
    }
    void AddEvent(float time, std::function<void()> action)
    {
        events.push_back({ time, action });
    }
    void AddBat(float time, Vector2 pos, BatPatron patron)
    {
        AddEvent(time, [this, pos, patron]()
            {
                SPAWNER.SpawnObject(new BatEnemy(pos,patron,score,&tracker));
            });
    }
    void AddGigante(float time, Vector2 pos, GigantePatron patron )
    {
        AddEvent(time, [this, pos, patron ]()
            {
                SPAWNER.SpawnObject(new GiganteEnemy(pos, patron,score,&tracker));
            });
    }
    void AddEsbirroH(float time, Vector2 pos)
    {
        AddEvent(time, [this, pos]()
            {
                SPAWNER.SpawnObject(new EsbirroHEnemy(pos,score, &tracker));
            });
    }
    void AddEsbirroV(float time, Vector2 pos)
    {
        AddEvent(time, [this, pos]()
            {
                SPAWNER.SpawnObject(new EsbirroVEnemy(pos,score,&tracker));
            });
    }
    void AddBruja(float time, Vector2 pos)
    {
        AddEvent(time, [this, pos]()
            {
                SPAWNER.SpawnObject(new BrujaEnemy(pos, score, &tracker));
            });
    }
    void AddEsqueleto(float time, Vector2 pos)
    {
        AddEvent(time, [this, pos]()
            {
                EsqueletoEnemy* nuevo =new EsqueletoEnemy(pos,score, &tracker);

                SPAWNER.SpawnObject(nuevo);esqueletos.push_back(nuevo);
            });
    }
    void AddBarbaro(float time, Vector2 pos, BarbaroPatron patron, Player* playerPointer)
    {
        AddEvent(time, [this, pos, patron, playerPointer]()
            {
               SPAWNER.SpawnObject(new BarbaroEnemy(pos,patron, playerPointer, score, &tracker));
            });
    }
    void AddYeti(float time, Vector2 pos)
    {
        AddEvent(time, [this, pos]()
            {
                SPAWNER.SpawnObject(new YetiEnemy(pos,score, &tracker));
            });
    }
    void AddLava(float time, Vector2 pos, lavaPatron patron)
    {
        AddEvent(time, [this, pos, patron]()
            {
                SPAWNER.SpawnObject(new LavaEnemy(pos,patron, score, &tracker));
            });
    }

    GolemEnemy* bossGolem = nullptr;

    void AddGolem(float time, Vector2 pos)
    {
        AddEvent(time, [this, pos]()
            {
                bossGolem = new GolemEnemy(pos, score, &tracker);
                SPAWNER.SpawnObject(bossGolem);
            });
    }

    void BuildHorde1()
    {
        AddBat(2.f, { static_cast<float>(RM->WINDOW_WIDTH), static_cast<float>(RM->WINDOW_HEIGHT) - 600 }, BatPatron::ARRIBA);
        AddBat(2.3f, { static_cast<float>(RM->WINDOW_WIDTH), static_cast<float>(RM->WINDOW_HEIGHT) - 600 }, BatPatron::ARRIBA);
        AddBat(2.6f, { static_cast<float>(RM->WINDOW_WIDTH), static_cast<float>(RM->WINDOW_HEIGHT) - 600 }, BatPatron::ARRIBA);
        AddBat(2.9f, { static_cast<float>(RM->WINDOW_WIDTH), static_cast<float>(RM->WINDOW_HEIGHT) - 600 }, BatPatron::ARRIBA);
        AddBat(2.9f, { static_cast<float>(RM->WINDOW_WIDTH), static_cast<float>(RM->WINDOW_HEIGHT) - 220 }, BatPatron::ABAJO);
        AddBat(3.2f, { static_cast<float>(RM->WINDOW_WIDTH), static_cast<float>(RM->WINDOW_HEIGHT) - 220 }, BatPatron::ABAJO);
        AddBat(3.5f, { static_cast<float>(RM->WINDOW_WIDTH), static_cast<float>(RM->WINDOW_HEIGHT) - 220 }, BatPatron::ABAJO);
        AddBat(3.8f, { static_cast<float>(RM->WINDOW_WIDTH), static_cast<float>(RM->WINDOW_HEIGHT) - 220 }, BatPatron::ABAJO);
    }
    void BuildHorde2()
    {
        AddGigante(2.f, { static_cast<float>(RM->WINDOW_WIDTH),50.f }, GigantePatron::ARRIBA);
        AddGigante(4.f, { static_cast<float>(RM->WINDOW_WIDTH),static_cast<float>(RM->WINDOW_HEIGHT) - 60.f }, GigantePatron::ABAJO);
    }
    void BuildHorde3()
    {
        AddEsbirroH(2.0f, { static_cast<float>(RM->WINDOW_WIDTH), static_cast<float>(RM->WINDOW_HEIGHT) - 650.f });
        AddEsbirroH(2.1f, { static_cast<float>(RM->WINDOW_WIDTH), static_cast<float>(RM->WINDOW_HEIGHT) - 150.f });
        AddEsbirroH(2.4f, { static_cast<float>(RM->WINDOW_WIDTH), static_cast<float>(RM->WINDOW_HEIGHT) - 500.f });
        AddEsbirroH(2.7f, { static_cast<float>(RM->WINDOW_WIDTH), static_cast<float>(RM->WINDOW_HEIGHT) - 550.f });
        AddEsbirroH(2.7f, { static_cast<float>(RM->WINDOW_WIDTH), static_cast<float>(RM->WINDOW_HEIGHT) - 450.f });
        AddEsbirroH(3.1f, { static_cast<float>(RM->WINDOW_WIDTH), static_cast<float>(RM->WINDOW_HEIGHT) - 475.f });
        AddEsbirroH(3.1f, { static_cast<float>(RM->WINDOW_WIDTH), static_cast<float>(RM->WINDOW_HEIGHT) - 300.f });
    }
    void BuildHorde4()
    {
        AddBruja(2.0f, { static_cast<float>(RM->WINDOW_WIDTH) - 800.f,50.f });
        AddEsqueleto(2.1f, { static_cast<float>(RM->WINDOW_WIDTH) - 800.f,50.f });
        AddEsqueleto(2.2f, { static_cast<float>(RM->WINDOW_WIDTH) - 800.f,50.f });
        AddEsqueleto(2.3f, { static_cast<float>(RM->WINDOW_WIDTH) - 800.f,50.f });
        AddEsqueleto(2.4f, { static_cast<float>(RM->WINDOW_WIDTH) - 800.f,50.f });
        AddEsqueleto(2.5f, { static_cast<float>(RM->WINDOW_WIDTH) - 800.f,50.f });
        AddEsqueleto(2.6f, { static_cast<float>(RM->WINDOW_WIDTH) - 800.f,50.f });
        AddEsqueleto(2.7f, { static_cast<float>(RM->WINDOW_WIDTH) - 800.f,50.f });
    }
    void BuildHorde5()
    {
        AddEsbirroV(2.0f, { static_cast<float>(RM->WINDOW_WIDTH) - 640.f, static_cast<float>(RM->WINDOW_HEIGHT) + 100.f });
        AddEsbirroV(2.3f, { static_cast<float>(RM->WINDOW_WIDTH) - 1160.f, static_cast<float>(RM->WINDOW_HEIGHT) + 100.f });
        AddEsbirroV(2.4f, { static_cast<float>(RM->WINDOW_WIDTH) - 1030.f, static_cast<float>(RM->WINDOW_HEIGHT) + 100.f });
        AddEsbirroV(2.6f, { static_cast<float>(RM->WINDOW_WIDTH) - 250.f, static_cast<float>(RM->WINDOW_HEIGHT) + 100.f });
        AddEsbirroV(2.8f, { static_cast<float>(RM->WINDOW_WIDTH) - 380.f, static_cast<float>(RM->WINDOW_HEIGHT) + 100.f });
        AddEsbirroV(2.1f, { static_cast<float>(RM->WINDOW_WIDTH) - 770.f, static_cast<float>(RM->WINDOW_HEIGHT) + 100.f });
        AddEsbirroV(2.3f, { static_cast<float>(RM->WINDOW_WIDTH) - 900.f, static_cast<float>(RM->WINDOW_HEIGHT) + 100.f });
        AddEsbirroV(2.5f, { static_cast<float>(RM->WINDOW_WIDTH) - 510.f, static_cast<float>(RM->WINDOW_HEIGHT) + 100.f });
    }
    void BuildHorde6(Player* playerPointer)
    {
        AddBarbaro(2.f, { static_cast<float>(RM->WINDOW_WIDTH) - 1200.f, 0.f }, BarbaroPatron::ARRIBA, playerPointer);
        AddBarbaro(2.f, { static_cast<float>(RM->WINDOW_WIDTH) - 1100.f, 0.f }, BarbaroPatron::ARRIBA, playerPointer);
        AddBarbaro(2.f, { static_cast<float>(RM->WINDOW_WIDTH) - 300.f, 0.f }, BarbaroPatron::ARRIBA, playerPointer);
        AddBarbaro(2.f, { static_cast<float>(RM->WINDOW_WIDTH) - 200.f, 0.f }, BarbaroPatron::ARRIBA, playerPointer);
        AddBarbaro(2.f, { static_cast<float>(RM->WINDOW_WIDTH) - 1200.f,  static_cast<float>(RM->WINDOW_HEIGHT) }, BarbaroPatron::ABAJO, playerPointer);
        AddBarbaro(2.f, { static_cast<float>(RM->WINDOW_WIDTH) - 1100.f,  static_cast<float>(RM->WINDOW_HEIGHT) }, BarbaroPatron::ABAJO, playerPointer);
        AddBarbaro(2.f, { static_cast<float>(RM->WINDOW_WIDTH) - 300.f,  static_cast<float>(RM->WINDOW_HEIGHT) }, BarbaroPatron::ABAJO, playerPointer);
        AddBarbaro(2.f, { static_cast<float>(RM->WINDOW_WIDTH) - 200.f, static_cast<float>(RM->WINDOW_HEIGHT) }, BarbaroPatron::ABAJO, playerPointer);
    }
    void BuildHorde7()
    {
        AddGigante(2.f, { static_cast<float>(RM->WINDOW_WIDTH),50.f }, GigantePatron::ARRIBA);
        AddGigante(4.f, { static_cast<float>(RM->WINDOW_WIDTH),static_cast<float>(RM->WINDOW_HEIGHT) - 60.f }, GigantePatron::ABAJO);
    }
    void BuildHorde8()
    {
        AddYeti(2.f, { static_cast<float>(RM->WINDOW_WIDTH) + 100, 300 });
        AddYeti(2.1f, { static_cast<float>(RM->WINDOW_WIDTH) + 100, 150 });
        AddYeti(2.2f, { static_cast<float>(RM->WINDOW_WIDTH) + 100, 450 });
        AddYeti(2.3f, { static_cast<float>(RM->WINDOW_WIDTH) + 100, 100 });
        AddYeti(2.4f, { static_cast<float>(RM->WINDOW_WIDTH) + 100, 350 });
        AddYeti(2.6f, { static_cast<float>(RM->WINDOW_WIDTH) + 100, 250 });
        AddYeti(2.7f, { static_cast<float>(RM->WINDOW_WIDTH) + 100, 200 });
        AddYeti(2.9f, { static_cast<float>(RM->WINDOW_WIDTH) + 100, 400 });
    }
    void BuildHorde9()
    {
        AddLava(2.f, { static_cast<float>(RM->WINDOW_WIDTH) - 1500, 350 }, lavaPatron::ABAJO);
        AddLava(2.f, { static_cast<float>(RM->WINDOW_WIDTH) - 1500, 350 }, lavaPatron::ARRIBA);
        AddLava(2.f, { static_cast<float>(RM->WINDOW_WIDTH) - 1500, 350 }, lavaPatron::DERECHA);
        AddLava(2.f, { static_cast<float>(RM->WINDOW_WIDTH) - 1500, 350 }, lavaPatron::IZQUIERDA);
        AddLava(2.f, { static_cast<float>(RM->WINDOW_WIDTH) - 1500, 350 }, lavaPatron::ARRIBADERECHA);
        AddLava(2.f, { static_cast<float>(RM->WINDOW_WIDTH) - 1500, 350 }, lavaPatron::ARRIBAIZQUIERDA);
        AddLava(2.f, { static_cast<float>(RM->WINDOW_WIDTH) - 1500, 350 }, lavaPatron::ABAJOIZQUIERDA);
        AddLava(2.f, { static_cast<float>(RM->WINDOW_WIDTH) - 1500, 350 }, lavaPatron::ABAJODERECHA);
    }
    void BuildHorde10()
    {
        AddBat(2.f, { static_cast<float>(RM->WINDOW_WIDTH), static_cast<float>(RM->WINDOW_HEIGHT) - 600 }, BatPatron::ARRIBA);
        AddBat(2.3f, { static_cast<float>(RM->WINDOW_WIDTH), static_cast<float>(RM->WINDOW_HEIGHT) - 600 }, BatPatron::ARRIBA);
        AddBat(2.6f, { static_cast<float>(RM->WINDOW_WIDTH), static_cast<float>(RM->WINDOW_HEIGHT) - 600 }, BatPatron::ARRIBA);
        AddBat(2.9f, { static_cast<float>(RM->WINDOW_WIDTH), static_cast<float>(RM->WINDOW_HEIGHT) - 600 }, BatPatron::ARRIBA);
        AddBat(2.9f, { static_cast<float>(RM->WINDOW_WIDTH), static_cast<float>(RM->WINDOW_HEIGHT) - 220 }, BatPatron::ABAJO);
        AddBat(3.2f, { static_cast<float>(RM->WINDOW_WIDTH), static_cast<float>(RM->WINDOW_HEIGHT) - 220 }, BatPatron::ABAJO);
        AddBat(3.5f, { static_cast<float>(RM->WINDOW_WIDTH), static_cast<float>(RM->WINDOW_HEIGHT) - 220 }, BatPatron::ABAJO);
        AddBat(3.8f, { static_cast<float>(RM->WINDOW_WIDTH), static_cast<float>(RM->WINDOW_HEIGHT) - 220 }, BatPatron::ABAJO);
    }
    void BuildHorde11()
    {
        AddGigante(2.f, { static_cast<float>(RM->WINDOW_WIDTH),50.f }, GigantePatron::ARRIBA);
        AddGigante(4.f, { static_cast<float>(RM->WINDOW_WIDTH),static_cast<float>(RM->WINDOW_HEIGHT) - 60.f }, GigantePatron::ABAJO);
    }
    void BuildHorde12()
    {
        AddEsbirroH(2.0f, { static_cast<float>(RM->WINDOW_WIDTH), static_cast<float>(RM->WINDOW_HEIGHT) - 650.f });
        AddEsbirroH(2.1f, { static_cast<float>(RM->WINDOW_WIDTH), static_cast<float>(RM->WINDOW_HEIGHT) - 150.f });
        AddEsbirroH(2.4f, { static_cast<float>(RM->WINDOW_WIDTH), static_cast<float>(RM->WINDOW_HEIGHT) - 500.f });
        AddEsbirroH(2.7f, { static_cast<float>(RM->WINDOW_WIDTH), static_cast<float>(RM->WINDOW_HEIGHT) - 550.f });
        AddEsbirroH(2.7f, { static_cast<float>(RM->WINDOW_WIDTH), static_cast<float>(RM->WINDOW_HEIGHT) - 450.f });
        AddEsbirroH(3.1f, { static_cast<float>(RM->WINDOW_WIDTH), static_cast<float>(RM->WINDOW_HEIGHT) - 475.f });
        AddEsbirroH(3.1f, { static_cast<float>(RM->WINDOW_WIDTH), static_cast<float>(RM->WINDOW_HEIGHT) - 300.f });
    }
    void BuildHorde13()
    {
        static bool firstTime = true;
        if (firstTime)
        {
            std::srand(static_cast<unsigned int>(std::time(nullptr)));
            firstTime = false;
        }

        AddGolem(5.f, { static_cast<float>(RM->WINDOW_WIDTH) - 500, static_cast<float>(RM->WINDOW_HEIGHT) / 2 });

        float posicionesY[7] = { 200.f, 270.f, 340.f, 410.f, 480.f, 550.f, 600.f };
        float posicionesX[7] = { 1120.f, 1200.f, 1160.f, 1200.f, 1100.f, 1180.f, 1140.f };
        float spawnInterval = 1.0f;
        float startTime = 6.f;
        float endTime = 6000.f;

        for (float t = startTime; t < endTime; t += spawnInterval)
        {
            AddEvent(t, [this, posicionesY, posicionesX]()
                {
                    if (bossGolem && bossGolem->GetLife() > 0)
                    {
                        int rocksCount = 3 + (std::rand() % 5);

                        float tempPosY[7];
                        float tempPosX[7];

                        for (int i = 0; i < 7; ++i) 
                            tempPosY[i] = posicionesY[i];

                        for (int i = 0; i < 7; ++i)
                            tempPosX[i] = posicionesX[i];

                        for (int i = 0; i < rocksCount; ++i)
                        {
                            int idx = std::rand() % (7 - i);
                            float y = tempPosY[idx];
                            float x = tempPosX[idx];

                            SPAWNER.SpawnObject(new RocaEnemy({ x, y }, score, &tracker));

                        }
                    }
                });
        }
    }

    std::vector<SpawnEvent> events;
    size_t currentEvent = 0;
    float currentTime = 0.f;

    HordeTracker tracker;
    Score* score = nullptr;
};