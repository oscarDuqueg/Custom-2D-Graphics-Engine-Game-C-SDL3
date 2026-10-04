#pragma once
#include "Scene.h"
#include "Button.h"
#include "SceneManager.h"
#include "Player.h"

class MainMenu : public Scene
{
public:
	MainMenu() = default;

	void OnEnter() override
	{
		_ui.push_back(new Button(
			[]() 
			{ 
				SM.SetNextScene("Gameplay"); 
			},
			Vector2(225, 250.f),
			"resources/level1.png"
		));

		_ui.push_back(new Button(
			[]() 
			{ 
				SM.SetNextScene("Level2"); 
			},
			Vector2(225, 500.f),
			"resources/level2.png"
		));

		_ui.push_back(new Button(
			[]()
			{
				SM.SetNextScene("HighScoreTableScene");
			},
			Vector2(700, 250.f),
			"resources/TableScore.png"
		));
	}

	void StartGame()
	{
		GamePersistence::Reset();
		SM.SetNextScene("Gameplay");
	}

	void OnExit() override
	{
		Scene::OnExit();
	}

	void Update() override
	{
		Scene::Update();
	}

	void Render() override
	{
		Scene::Render();
	}

};
