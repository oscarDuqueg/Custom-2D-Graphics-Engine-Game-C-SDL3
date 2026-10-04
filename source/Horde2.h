#pragma once

#include <vector>
#include <functional>
#include "Vector2.h"
#include "TimeManager.h"
#include "Spawner.h"
#include "HordeTracker.h"
#include "Score.h"
#include "Duende.h"
#include "Electrico.h"
#include "Globo.h"
#include "Monta.h"
#include "Pekka.h"
#include "Pekka.h"
#include "Raiz.h"
#include "Rompemuro.h"
#include "Sanadora.h"
#include "Valquiria.h"
#include "Helicoptero.h"
#include "Bomba.h"

struct SpawnEvent2
{
    float time;
    std::function<void()> action;
};

class Level2;

class Horde2
{
private:
    bool waitingNextHorde = false;
    float waitTimer = 0.f;
    float waitBetweenHordes = 2.0f;
    int currentHorde = 0;
    Player* Target = nullptr;

public:
    Horde2(Score* score, Player* playerPointer)
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
        case 2:BuildHorde2(); StartHorde(8); break;
        case 3:BuildHorde3(Target); StartHorde(8); break;
        case 4:BuildHorde4(); StartHorde(4); break;
        case 5:BuildHorde5(); StartHorde(8); break;
        case 6:BuildHorde6(); StartHorde(8); break;
        case 7:BuildHorde7(); StartHorde(5); break;
        case 8:BuildHorde8(Target); StartHorde(8); break;
        case 9:BuildHorde9(); StartHorde(8); break;
        case 10:BuildHorde10(); StartHorde(4); break;
        case 11:BuildHorde11(); StartHorde(8); break;
        case 12:BuildHorde12(); StartHorde(8); break;
        case 13:BuildHorde13(Target); StartHorde(8); break;
        case 14:BuildHorde14(); StartHorde(2); break;
        }
    }
    void AddEvent(float time, std::function<void()> action)
    {
        events.push_back({ time, action });
    }
    void AddMonta(float time, Vector2 pos)
    {
        AddEvent(time, [this, pos]()
            {
                SPAWNER.SpawnObject(new MontaEnemy(pos,score, &tracker));
            });
    }
    void AddDuende(float time, Vector2 pos, DuendePatron patron)
    {
        AddEvent(time, [this, pos, patron]()
            {
                SPAWNER.SpawnObject(new DuendeEnemy(pos,patron, score, &tracker));
            });
    }
    void AddGlobo(float time, Vector2 pos, GloboPatron patron, Player* playerPointer)
    {
        AddEvent(time, [this, pos, patron, playerPointer]()
            {
                SPAWNER.SpawnObject(new GloboEnemy(pos,patron, playerPointer, score, &tracker));
            });
    }
    void AddSanadora(float time, Vector2 pos)
    {
        AddEvent(time, [this, pos]()
            {
                SPAWNER.SpawnObject(new SanadoraEnemy(pos,score, &tracker));
            });

    }
    void AddRompemuro(float time, Vector2 pos)
    {
        AddEvent(time, [this, pos]()
            {
                SPAWNER.SpawnObject(new RompemuroEnemy(pos, score, &tracker));
            });

    }
    void AddRaiz(float time, Vector2 pos, RaizPatron patron)
    {
        AddEvent(time, [this, pos, patron]()
            {
                SPAWNER.SpawnObject(new RaizEnemy(pos,patron, score, &tracker));
            });
    }
    void AddValquiria(float time, Vector2 pos)
    {
        AddEvent(time, [this, pos]()
            {
                SPAWNER.SpawnObject(new ValquiriaEnemy(pos,score, &tracker));
            });

    }
    void AddPekka(float time, Vector2 pos, PekkaPatron patron, Player* playerPointer)
    {
        AddEvent(time, [this, pos, patron, playerPointer]()
            {
                SPAWNER.SpawnObject(new PekkaEnemy(pos,patron, playerPointer, score, &tracker));
            });
    }
    void AddElectrico(float time, Vector2 pos)
    {
        AddEvent(time, [this, pos]()
            {
                SPAWNER.SpawnObject(new ElectricoEnemy(pos, score, &tracker));
            });
    }

    HelicopteroEnemy* bossHelicoptero = nullptr;

    void AddHelicoptero(float time, Vector2 pos)
    {
        AddEvent(time, [this, pos]()
            {
                bossHelicoptero = new HelicopteroEnemy(pos, score, &tracker);
                SPAWNER.SpawnObject(bossHelicoptero);
            });
    }

    void BuildHorde1()
    {
        AddMonta(1.f, { static_cast<float>(RM->WINDOW_WIDTH) + 100, static_cast<float>(RM->WINDOW_HEIGHT) - 650.f });
        AddMonta(1.2f, { static_cast<float>(RM->WINDOW_WIDTH) + 100, static_cast<float>(RM->WINDOW_HEIGHT) - 125.f });
        AddMonta(1.5f, { static_cast<float>(RM->WINDOW_WIDTH) + 100, static_cast<float>(RM->WINDOW_HEIGHT) - 250.f });
        AddMonta(1.9f, { static_cast<float>(RM->WINDOW_WIDTH) + 100, static_cast<float>(RM->WINDOW_HEIGHT) - 225.f });
        AddMonta(2.1f, { static_cast<float>(RM->WINDOW_WIDTH) + 100, static_cast<float>(RM->WINDOW_HEIGHT) - 600.f });
        AddMonta(2.2f, { static_cast<float>(RM->WINDOW_WIDTH) + 100, static_cast<float>(RM->WINDOW_HEIGHT) - 475.f });
        AddMonta(2.5f, { static_cast<float>(RM->WINDOW_WIDTH) + 100, static_cast<float>(RM->WINDOW_HEIGHT) - 333.f });
        AddMonta(2.8f, { static_cast<float>(RM->WINDOW_WIDTH) + 100, static_cast<float>(RM->WINDOW_HEIGHT) - 333.f });
    }
    void BuildHorde2()
    {
        AddDuende(2.f, { static_cast<float>(RM->WINDOW_WIDTH) - 1500.f,static_cast<float>(RM->WINDOW_HEIGHT) / 2 }, DuendePatron::IZQUIERDA);
        AddDuende(2.f, { static_cast<float>(RM->WINDOW_WIDTH) + 200.f,static_cast<float>(RM->WINDOW_HEIGHT) / 2 }, DuendePatron::DERECHA);
        AddDuende(2.2f, { static_cast<float>(RM->WINDOW_WIDTH) - 1500.f,static_cast<float>(RM->WINDOW_HEIGHT) / 2 }, DuendePatron::IZQUIERDA);
        AddDuende(2.2f, { static_cast<float>(RM->WINDOW_WIDTH) + 200.f,static_cast<float>(RM->WINDOW_HEIGHT) / 2 }, DuendePatron::DERECHA);
        AddDuende(2.4f, { static_cast<float>(RM->WINDOW_WIDTH) - 1500.f,static_cast<float>(RM->WINDOW_HEIGHT) / 2 }, DuendePatron::IZQUIERDA);
        AddDuende(2.4f, { static_cast<float>(RM->WINDOW_WIDTH) + 200.f,static_cast<float>(RM->WINDOW_HEIGHT) / 2 }, DuendePatron::DERECHA);
        AddDuende(2.6f, { static_cast<float>(RM->WINDOW_WIDTH) - 1500.f,static_cast<float>(RM->WINDOW_HEIGHT) / 2 }, DuendePatron::IZQUIERDA);
        AddDuende(2.6f, { static_cast<float>(RM->WINDOW_WIDTH) + 200.f,static_cast<float>(RM->WINDOW_HEIGHT) / 2 }, DuendePatron::DERECHA);
    }
    void BuildHorde3(Player* playerPointer)
    {
        AddGlobo(2.f, { static_cast<float>(RM->WINDOW_WIDTH) - 1500.f, 50.f }, GloboPatron::DERECHA, playerPointer);
        AddGlobo(2.f, { static_cast<float>(RM->WINDOW_WIDTH) - 1400.f, 50.f }, GloboPatron::DERECHA, playerPointer);
        AddGlobo(2.f, { static_cast<float>(RM->WINDOW_WIDTH), 50.f }, GloboPatron::IZQUIERDA, playerPointer);
        AddGlobo(2.f, { static_cast<float>(RM->WINDOW_WIDTH) + 100.f, 50.f }, GloboPatron::IZQUIERDA, playerPointer);
        AddGlobo(2.f, { static_cast<float>(RM->WINDOW_WIDTH) - 1500.f, static_cast<float>(RM->WINDOW_HEIGHT) - 50, }, GloboPatron::DERECHA, playerPointer);
        AddGlobo(2.f, { static_cast<float>(RM->WINDOW_WIDTH) - 1400.f, static_cast<float>(RM->WINDOW_HEIGHT) - 50, }, GloboPatron::DERECHA, playerPointer);
        AddGlobo(2.f, { static_cast<float>(RM->WINDOW_WIDTH) + 100.f, static_cast<float>(RM->WINDOW_HEIGHT) - 50, }, GloboPatron::IZQUIERDA, playerPointer);
        AddGlobo(2.f, { static_cast<float>(RM->WINDOW_WIDTH), static_cast<float>(RM->WINDOW_HEIGHT) - 50, }, GloboPatron::IZQUIERDA, playerPointer);
    }
    void BuildHorde4()
    {
        AddSanadora(2.f, { static_cast<float>(RM->WINDOW_WIDTH) - 500.f, static_cast<float>(RM->WINDOW_HEIGHT) + 50 });
        AddSanadora(2.f, { static_cast<float>(RM->WINDOW_WIDTH) - 800, static_cast<float>(RM->WINDOW_HEIGHT) + 50.f });
        AddSanadora(2.f, { static_cast<float>(RM->WINDOW_WIDTH) - 600, static_cast<float>(RM->WINDOW_HEIGHT) + 50.f });
        AddSanadora(2.f, { static_cast<float>(RM->WINDOW_WIDTH) - 700, static_cast<float>(RM->WINDOW_HEIGHT) + 50.f });
    }
    void BuildHorde5()
    {
        AddRompemuro(2.f, { static_cast<float>(RM->WINDOW_WIDTH), static_cast<float>(RM->WINDOW_HEIGHT) - 250.f });
        AddRompemuro(2.3f, { static_cast<float>(RM->WINDOW_WIDTH), static_cast<float>(RM->WINDOW_HEIGHT) - 700.f });
        AddRompemuro(2.4f, { static_cast<float>(RM->WINDOW_WIDTH), static_cast<float>(RM->WINDOW_HEIGHT) - 400.f });
        AddRompemuro(2.8f, { static_cast<float>(RM->WINDOW_WIDTH), static_cast<float>(RM->WINDOW_HEIGHT) - 500.f });
        AddRompemuro(3.f, { static_cast<float>(RM->WINDOW_WIDTH), static_cast<float>(RM->WINDOW_HEIGHT) - 175.f });
        AddRompemuro(3.1f, { static_cast<float>(RM->WINDOW_WIDTH),static_cast<float>(RM->WINDOW_HEIGHT) - 600.f });
        AddRompemuro(3.1f, { static_cast<float>(RM->WINDOW_WIDTH), static_cast<float>(RM->WINDOW_HEIGHT) - 300.f });
        AddRompemuro(3.4f, { static_cast<float>(RM->WINDOW_WIDTH), static_cast<float>(RM->WINDOW_HEIGHT) - 50.f });
    }
    void BuildHorde6()
    {
        AddRaiz(2.f, { static_cast<float>(RM->WINDOW_WIDTH) - 1500, static_cast<float>(RM->WINDOW_HEIGHT) - 700 }, RaizPatron::ARRIBA);
        AddRaiz(2.2f, { static_cast<float>(RM->WINDOW_WIDTH) - 1500, static_cast<float>(RM->WINDOW_HEIGHT) - 50, }, RaizPatron::ABAJO);
        AddRaiz(2.2f, { static_cast<float>(RM->WINDOW_WIDTH) - 1500, static_cast<float>(RM->WINDOW_HEIGHT) - 700 }, RaizPatron::ARRIBA);
        AddRaiz(2.4f, { static_cast<float>(RM->WINDOW_WIDTH) - 1500, static_cast<float>(RM->WINDOW_HEIGHT) - 50, }, RaizPatron::ABAJO);
        AddRaiz(2.4f, { static_cast<float>(RM->WINDOW_WIDTH) - 1500, static_cast<float>(RM->WINDOW_HEIGHT) - 700 }, RaizPatron::ARRIBA);
        AddRaiz(2.6f, { static_cast<float>(RM->WINDOW_WIDTH) - 1500, static_cast<float>(RM->WINDOW_HEIGHT) - 50, }, RaizPatron::ABAJO);
        AddRaiz(2.6f, { static_cast<float>(RM->WINDOW_WIDTH) - 1500, static_cast<float>(RM->WINDOW_HEIGHT) - 700 }, RaizPatron::ARRIBA);
        AddRaiz(2.8f, { static_cast<float>(RM->WINDOW_WIDTH) - 1500, static_cast<float>(RM->WINDOW_HEIGHT) - 50, }, RaizPatron::ABAJO);
    }
    void BuildHorde7()
    {
        AddValquiria(2.f, { static_cast<float>(RM->WINDOW_WIDTH) + 100, static_cast<float>(RM->WINDOW_HEIGHT) - 400, });
        AddValquiria(2.1f, { static_cast<float>(RM->WINDOW_WIDTH) + 100, static_cast<float>(RM->WINDOW_HEIGHT) - 650, });
        AddValquiria(2.2f, { static_cast<float>(RM->WINDOW_WIDTH) + 100, static_cast<float>(RM->WINDOW_HEIGHT) - 100, });
        AddValquiria(2.3f, { static_cast<float>(RM->WINDOW_WIDTH) + 100, static_cast<float>(RM->WINDOW_HEIGHT) - 500, });
        AddValquiria(2.4f, { static_cast<float>(RM->WINDOW_WIDTH) + 100, static_cast<float>(RM->WINDOW_HEIGHT) - 250, });
    }
    void BuildHorde8(Player* playerPointer)
    {
        AddPekka(2.f, { static_cast<float>(RM->WINDOW_WIDTH) - 1200, 0.f, }, PekkaPatron::ARRIBA, playerPointer);
        AddPekka(2.f, { static_cast<float>(RM->WINDOW_WIDTH) - 1100, 0.f, }, PekkaPatron::ARRIBA, playerPointer);
        AddPekka(2.f, { static_cast<float>(RM->WINDOW_WIDTH) - 300, 0.f, }, PekkaPatron::ARRIBA, playerPointer);
        AddPekka(2.f, { static_cast<float>(RM->WINDOW_WIDTH) - 200, 0.f, }, PekkaPatron::ARRIBA, playerPointer);
        AddPekka(2.f, { static_cast<float>(RM->WINDOW_WIDTH) - 1200, static_cast<float>(RM->WINDOW_HEIGHT) }, PekkaPatron::ABAJO, playerPointer);
        AddPekka(2.f, { static_cast<float>(RM->WINDOW_WIDTH) - 1100, static_cast<float>(RM->WINDOW_HEIGHT) }, PekkaPatron::ABAJO, playerPointer);
        AddPekka(2.f, { static_cast<float>(RM->WINDOW_WIDTH) - 300, static_cast<float>(RM->WINDOW_HEIGHT) }, PekkaPatron::ABAJO, playerPointer);
        AddPekka(2.f, { static_cast<float>(RM->WINDOW_WIDTH) - 200, static_cast<float>(RM->WINDOW_HEIGHT) }, PekkaPatron::ABAJO, playerPointer);
    }
    void BuildHorde9()
    {
        AddElectrico(2.f, { static_cast<float>(RM->WINDOW_WIDTH) - 1500, 60.f });
        AddElectrico(2.2f, { static_cast<float>(RM->WINDOW_WIDTH) - 1500, 60.f });
        AddElectrico(2.4f, { static_cast<float>(RM->WINDOW_WIDTH) - 1500, 60.f });
        AddElectrico(2.6f, { static_cast<float>(RM->WINDOW_WIDTH) - 1500, 60.f });
        AddElectrico(2.8f, { static_cast<float>(RM->WINDOW_WIDTH) - 1500, 60.f });
        AddElectrico(2.f, { static_cast<float>(RM->WINDOW_WIDTH) - 1500, 60.f });
        AddElectrico(2.2f, { static_cast<float>(RM->WINDOW_WIDTH) - 1500, 60.f });
        AddElectrico(2.4f, { static_cast<float>(RM->WINDOW_WIDTH) - 1500, 60.f });
    }
    void BuildHorde10()
    {
        AddSanadora(2.5f, { static_cast<float>(RM->WINDOW_WIDTH) - 500.f, static_cast<float>(RM->WINDOW_HEIGHT) + 50 });
        AddSanadora(2.5f, { static_cast<float>(RM->WINDOW_WIDTH) - 800, static_cast<float>(RM->WINDOW_HEIGHT) + 50.f });
        AddSanadora(2.5f, { static_cast<float>(RM->WINDOW_WIDTH) - 600, static_cast<float>(RM->WINDOW_HEIGHT) + 50.f });
        AddSanadora(2.5f, { static_cast<float>(RM->WINDOW_WIDTH) - 700, static_cast<float>(RM->WINDOW_HEIGHT) + 50.f });
    }
    void BuildHorde11()
    {
        AddMonta(2.f, { static_cast<float>(RM->WINDOW_WIDTH) + 100, static_cast<float>(RM->WINDOW_HEIGHT) - 650.f });
        AddMonta(2.2f, { static_cast<float>(RM->WINDOW_WIDTH) + 100, static_cast<float>(RM->WINDOW_HEIGHT) - 125.f });
        AddMonta(2.5f, { static_cast<float>(RM->WINDOW_WIDTH) + 100, static_cast<float>(RM->WINDOW_HEIGHT) - 250.f });
        AddMonta(2.9f, { static_cast<float>(RM->WINDOW_WIDTH) + 100, static_cast<float>(RM->WINDOW_HEIGHT) - 225.f });
        AddMonta(3.1f, { static_cast<float>(RM->WINDOW_WIDTH) + 100, static_cast<float>(RM->WINDOW_HEIGHT) - 600.f });
        AddMonta(3.2f, { static_cast<float>(RM->WINDOW_WIDTH) + 100, static_cast<float>(RM->WINDOW_HEIGHT) - 475.f });
        AddMonta(3.5f, { static_cast<float>(RM->WINDOW_WIDTH) + 100, static_cast<float>(RM->WINDOW_HEIGHT) - 333.f });
        AddMonta(3.8f, { static_cast<float>(RM->WINDOW_WIDTH) + 100, static_cast<float>(RM->WINDOW_HEIGHT) - 333.f });
    }
    void BuildHorde12()
    {
        AddDuende(2.f, { static_cast<float>(RM->WINDOW_WIDTH) - 1500.f,static_cast<float>(RM->WINDOW_HEIGHT) / 2 }, DuendePatron::IZQUIERDA);
        AddDuende(2.f, { static_cast<float>(RM->WINDOW_WIDTH) + 200.f,static_cast<float>(RM->WINDOW_HEIGHT) / 2 }, DuendePatron::DERECHA);
        AddDuende(2.2f, { static_cast<float>(RM->WINDOW_WIDTH) - 1500.f,static_cast<float>(RM->WINDOW_HEIGHT) / 2 }, DuendePatron::IZQUIERDA);
        AddDuende(2.2f, { static_cast<float>(RM->WINDOW_WIDTH) + 200.f,static_cast<float>(RM->WINDOW_HEIGHT) / 2 }, DuendePatron::DERECHA);
        AddDuende(2.4f, { static_cast<float>(RM->WINDOW_WIDTH) - 1500.f,static_cast<float>(RM->WINDOW_HEIGHT) / 2 }, DuendePatron::IZQUIERDA);
        AddDuende(2.4f, { static_cast<float>(RM->WINDOW_WIDTH) + 200.f,static_cast<float>(RM->WINDOW_HEIGHT) / 2 }, DuendePatron::DERECHA);
        AddDuende(2.6f, { static_cast<float>(RM->WINDOW_WIDTH) - 1500.f,static_cast<float>(RM->WINDOW_HEIGHT) / 2 }, DuendePatron::IZQUIERDA);
        AddDuende(2.6f, { static_cast<float>(RM->WINDOW_WIDTH) + 200.f,static_cast<float>(RM->WINDOW_HEIGHT) / 2 }, DuendePatron::DERECHA);
    }
    void BuildHorde13(Player* playerPointer)
    {
        AddGlobo(2.0f, { static_cast<float>(RM->WINDOW_WIDTH) - 1500.f, 50.f }, GloboPatron::DERECHA, playerPointer);
        AddGlobo(2.0f, { static_cast<float>(RM->WINDOW_WIDTH) - 1400.f, 50.f }, GloboPatron::DERECHA, playerPointer);
        AddGlobo(2.0f, { static_cast<float>(RM->WINDOW_WIDTH), 50.f }, GloboPatron::IZQUIERDA, playerPointer);
        AddGlobo(2.0f, { static_cast<float>(RM->WINDOW_WIDTH) + 100.f, 50.f }, GloboPatron::IZQUIERDA, playerPointer);
        AddGlobo(2.0f, { static_cast<float>(RM->WINDOW_WIDTH) - 1500.f, static_cast<float>(RM->WINDOW_HEIGHT) - 50, }, GloboPatron::DERECHA, playerPointer);
        AddGlobo(2.0f, { static_cast<float>(RM->WINDOW_WIDTH) - 1400.f, static_cast<float>(RM->WINDOW_HEIGHT) - 50, }, GloboPatron::DERECHA, playerPointer);
        AddGlobo(2.0f, { static_cast<float>(RM->WINDOW_WIDTH) + 100.f, static_cast<float>(RM->WINDOW_HEIGHT) - 50, }, GloboPatron::IZQUIERDA, playerPointer);
        AddGlobo(2.0f, { static_cast<float>(RM->WINDOW_WIDTH) , static_cast<float>(RM->WINDOW_HEIGHT) - 50, }, GloboPatron::IZQUIERDA, playerPointer);
    }
    void BuildHorde14()
    {
        static bool firstTime = true;
        if (firstTime)
        {
            std::srand(static_cast<unsigned int>(std::time(nullptr)));
            firstTime = false;
        }

        AddHelicoptero(5.f, { static_cast<float>(RM->WINDOW_WIDTH) - 500, static_cast<float>(RM->WINDOW_HEIGHT) / 2 });

        float posicionesY[7] = { 200.f, 270.f, 340.f, 410.f, 480.f, 550.f, 600.f };
        float posicionesX[7] = { 1120.f, 1200.f, 1160.f, 1200.f, 1100.f, 1180.f, 1140.f };
        float spawnInterval = 1.0f;
        float startTime = 6.f;
        float endTime = 6000.f;

        for (float t = startTime; t < endTime; t += spawnInterval)
        {
            AddEvent(t, [this, posicionesY, posicionesX]()
                {
                    if (bossHelicoptero && bossHelicoptero->GetLife() > 0)
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

                            SPAWNER.SpawnObject(new BombaEnemy({ x, y }, score, &tracker));

                        }
                    }
                });
        }
    }

    std::vector<SpawnEvent2> events;
    size_t currentEvent = 0;
    float currentTime = 0.f;

    HordeTracker tracker;
    Score* score = nullptr;
};