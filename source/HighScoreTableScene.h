#pragma once
#include "Scene.h"
#include "TextObject.h"
#include "ScoreManager.h"
#include "SceneManager.h"
#include "Button.h"

class HighScoreTableScene : public Scene {
private:
    std::vector<TextObject*> scoreTexts;

public:
    HighScoreTableScene() = default;

    void OnEnter() override {

        std::string fontPath = "resources/fonts/hyperspace.ttf";
        if (!RM->GetFont(fontPath))
        {
            std::cout << "[HighScoreTable] Fuente no cargada, abortando textos" << std::endl;
            return;
        }

        TextObject* title = new TextObject("High Scores");
        title->GetTransform()->position = { 400.f, 100.f };
        title->GetTransform()->scale = { 2.f, 2.f };
        _ui.push_back(title);

        const auto& scores = SC->GetHighScores();
        int index = 1;
        float yPos = 150.f;
        for (const auto& entry : scores) {
            std::ostringstream ss;
            ss << index << ". " << entry.second << " - " << entry.first;
            TextObject* text = new TextObject(ss.str());
            text->GetTransform()->position = { 400.f, yPos };
            text->GetTransform()->scale = { 1.5f, 1.5f };
            _ui.push_back(text);
            scoreTexts.push_back(text);
            yPos += 50.f;
            index++;
        }

        Button* backButton = new Button([]() { SM.SetNextScene("MainMenu"); }, { 700.f, yPos + 50.f }, "resources/backToMenu.png");
        _ui.push_back(backButton);
    }

    void Update() override {
        Scene::Update();
    }

    void OnExit() override {
        Scene::OnExit();
        scoreTexts.clear();
    }
};