#pragma once
#include "Scene.h"
#include "TextObject.h"
#include "InputManager.h"
#include "ScoreManager.h"
#include "SceneManager.h"
#include <string>

class HighScoreEntryScene : public Scene
{
private:
    TextObject* promptText = nullptr;
    int currentScore = 0;
    std::string playerName = "";

public:
    HighScoreEntryScene() = default;
    void SetCurrentScore(int score) { currentScore = score; }

    void OnEnter() override
    {
        promptText = new TextObject("Enter your name (press Enter to save):");
        promptText->GetTransform()->position = { 300.f, 300.f };
        promptText->GetTransform()->scale = { 2.f, 2.f };
        _ui.push_back(promptText);

        // Mensaje inicial vacío o con placeholder
        TextObject* nameDisplay = new TextObject("Nombre: _");
        nameDisplay->GetTransform()->position = { 300.f, 400.f };
        nameDisplay->GetTransform()->scale = { 2.f, 2.f };
        _ui.push_back(nameDisplay);

        playerName.clear();
    }

    void Update() override
    {
        Scene::Update();

        for (Sint32 key = SDLK_A; key <= SDLK_Z; ++key)
        {
            if (IM->GetEvent(key, DOWN))
            {
                char c = static_cast<char>(key);
                if (IM->GetEvent(SDLK_LSHIFT, HOLD) || IM->GetEvent(SDLK_RSHIFT, HOLD))
                    c = toupper(c);
                playerName += c;
            }
        }

        if (IM->GetEvent(SDLK_BACKSPACE, DOWN))
        {
            if (!playerName.empty())
            {
                playerName.pop_back();
                std::cout << "[Entrada] Borrado -> " << playerName << std::endl;
            }
        }

        if (IM->GetEvent(SDLK_RETURN, DOWN) || IM->GetEvent(SDLK_KP_ENTER, DOWN))
        {
            if (!playerName.empty())
            {
                std::cout << "[HighScoreEntry] Guardando: " << playerName << " - " << currentScore << std::endl;
                SC->AddHighScore(currentScore, playerName);
                SM.SetNextScene("HighScoreTableScene");
            }
            else
            {
                std::cout << "[HighScoreEntry] Nombre vacío, no se guarda" << std::endl;
            }
        }
    }

    void OnExit() override
    {
        Scene::OnExit();
    }
};