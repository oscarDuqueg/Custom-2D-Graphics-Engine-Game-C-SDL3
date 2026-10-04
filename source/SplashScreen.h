#pragma once
#include "Scene.h"
#include "Button.h"
#include "SceneManager.h"
#include "ImageUI.h"

class SplashScreen : public Scene
{
private:
    float elapsedTime = 0.f;      
    const float timeToWait = 5.f; 

public:
    SplashScreen() = default;

    void OnEnter() override
    {
        ImageUI* screen = new ImageUI(Vector2(-RM->WINDOW_WIDTH / 2, 384.f), Vector2(0.f, 0.f), Vector2(RM->WINDOW_WIDTH, RM->WINDOW_HEIGHT));
        SPAWNER.SpawnObject(screen);

        TextObject* textScore = new TextObject("MENACE X CLASH OF CLANS");
        textScore->GetTransform()->position = { 425.f, 800.f };
        textScore->GetTransform()->scale = { 2.f, 2.f };
        textScore->SetParticularColor({ 255, 0, 125, 0xFF });
        _ui.push_back(textScore);

        elapsedTime = 0.f;
    }

    void OnExit() override
    {
        Scene::OnExit(); 
    }

    void Update() override
    {
        float dt = TIME.GetDeltaTime();
        elapsedTime += dt;              

        if (elapsedTime >= timeToWait)
        {
            SM.SetNextScene("MainMenu");
            
            elapsedTime = -100.f;
        }

        

        Scene::Update();  
    }

    void Render() override
    {
        Scene::Render();  
    }
};