#pragma once
#include "Scene.h"
#include "Player.h"
#include "TextObject.h"
#include "Wall.h"
#include "WallY.h"
#include "Fondo.h"
#include "TimeManager.h"
#include "Golem.h"
#include "PowerUp.h"
#include "LifeBar.h"
#include "CanonBar.h"
#include "LaserBar.h"
#include "Score.h"
#include "Decoracion.h"
#include "Horde.h"
#include "ScoreManager.h"
#include "HighScoreEntryScene.h"
#include "HighScoreTableScene.h"

class Gameplay : public Scene
{
private:
	Horde* horde = nullptr;
	Score* score = nullptr;
	Decoracion* decoracion = nullptr;
	Player* player = nullptr;

	bool levelCleared = false;
	bool isScrolling = true;
	bool isSpawning = true;

	bool bossSpawned = false;
	bool bossAlive = false;
	bool bossDead = false;

	enum class State { GAMEPLAY, PAUSED, FINISH_STAGE, DEATH };
	State currentState = State::GAMEPLAY;
	float stateTimer = 0.0f;
	bool showBlackScreen = false;
	Button* resumeButton = nullptr;
	ImageObject* victoriaImage = nullptr;

public:
	Gameplay() = default;

	void Update() override
	{
		float dt = TIME.GetDeltaTime();

		switch (currentState)
		{
		case State::GAMEPLAY:UpdateGameplay(); break;
		case State::PAUSED:UpdatePause(); break;
		case State::FINISH_STAGE:UpdateFinishStage();break;
		case State::DEATH:UpdateDeath();break;
		}
	}

	void OnEnter() override
	{
		// Reset de estados al entrar
		currentState = State::GAMEPLAY;
		showBlackScreen = false;
		stateTimer = 0.0f;
		bossSpawned = false;
		bossDead = false;
		isScrolling = true;
		isSpawning = true;

		resumeButton = new Button(
			[this]()
			{
				this->currentState = State::GAMEPLAY;
			},
			Vector2(RM->WINDOW_WIDTH - 950, RM->WINDOW_HEIGHT - 450),
			"resources/resume.png"
		);

		Fondo* bg1 = new Fondo(Vector2(RM->WINDOW_WIDTH - 2100.f, RM->WINDOW_HEIGHT - 384.f), Vector2(0.f, 0.f), Vector2(RM->WINDOW_WIDTH, RM->WINDOW_HEIGHT), &isScrolling);
		Fondo* bg2 = new Fondo(Vector2(RM->WINDOW_WIDTH - 740.f, RM->WINDOW_HEIGHT - 384.f), Vector2(0.f, 0.f), Vector2(RM->WINDOW_WIDTH, RM->WINDOW_HEIGHT), &isScrolling);
		Fondo* bg3 = new Fondo(Vector2(RM->WINDOW_WIDTH + 610.f, RM->WINDOW_HEIGHT - 384.f), Vector2(0.f, 0.f), Vector2(RM->WINDOW_WIDTH, RM->WINDOW_HEIGHT), &isScrolling);

		bg1->SetNextFondo(bg2);
		bg2->SetNextFondo(bg3);
		bg3->SetNextFondo(bg1);

		SPAWNER.SpawnObject(bg1);
		SPAWNER.SpawnObject(bg2);
		SPAWNER.SpawnObject(bg3);

		float scrollSpeed = RM->WINDOW_WIDTH * 0.10f;
		bg1->SetScrollSpeed(scrollSpeed);
		bg2->SetScrollSpeed(scrollSpeed);
		bg3->SetScrollSpeed(scrollSpeed);

		Wall* wallTop = new Wall(Vector2(-RM->WINDOW_WIDTH * 0.45f, -10.f), Vector2(RM->WINDOW_WIDTH, 20.f));
		Wall* wallBottom = new Wall(Vector2(-RM->WINDOW_WIDTH * 0.45f, RM->WINDOW_HEIGHT + 15), Vector2(RM->WINDOW_WIDTH, 20.f));
		WallY* wallLeft = new WallY(Vector2(-30.f, RM->WINDOW_HEIGHT * 0.5f), Vector2(20.f, RM->WINDOW_HEIGHT));
		WallY* wallRight = new WallY(Vector2(RM->WINDOW_WIDTH, RM->WINDOW_HEIGHT * 0.5), Vector2(20.f, RM->WINDOW_HEIGHT));
		SPAWNER.SpawnObject(wallTop);
		SPAWNER.SpawnObject(wallBottom);
		SPAWNER.SpawnObject(wallLeft);
		SPAWNER.SpawnObject(wallRight);

		decoracion = new Decoracion(1.5f, Vector2(-1.f, 0.f), &isSpawning);
		player = new Player();
		SPAWNER.SpawnObject(player);

		//UI
		TextObject* textScore = new TextObject("SC:");
		textScore->GetTransform()->position = { 125.f, 800.f };
		textScore->GetTransform()->scale = { 2.f, 2.f };
		_ui.push_back(textScore);

		score = new Score();
		_ui.push_back(score);
		horde = new Horde(score, player);

		TextObject* textVida = new TextObject("EN:");
		textVida->GetTransform()->position = { 500.f, 800.f };
		textVida->GetTransform()->scale = { 2.f, 2.f };
		_ui.push_back(textVida);

		_ui.push_back(new LifeBar(player));
		_ui.push_back(new CanonBar(player));
		_ui.push_back(new LaserBar(player));

		TextObject* textDoble = new TextObject("CA:");
		textDoble->GetTransform()->position = { 800.f, 800.f };
		textDoble->GetTransform()->scale = { 2.f, 2.f };
		_ui.push_back(textDoble);

		TextObject* textLaser = new TextObject("LA:");
		textLaser->GetTransform()->position = { 1150.f, 800.f };
		textLaser->GetTransform()->scale = { 2.f, 2.f };
		_ui.push_back(textLaser);

	}

	void Render() override {
		Scene::Render();

		if (showBlackScreen) {
			DrawBlackOverlay();
		}

		if (currentState == State::PAUSED) {

			if (resumeButton) {
				resumeButton->Render();
			}
		}
	}

	void SavePlayerData() {
		GamePersistence::lastLife = player->GetLife();
		GamePersistence::lastScore = score->GetScore();
		GamePersistence::hasTwoCanon = player->hasTwoCanon;
		GamePersistence::secondCannonFuel = player->secondCannonFuel;
		GamePersistence::hasLaser = player->hasLaser;
		GamePersistence::laserFuel = player->laserFuel;
		GamePersistence::hasTurrets = player->GetHasTurrets();
		GamePersistence::moveSpeed = player->GetMoveSpeed();
		GamePersistence::SaveToFile("savegame.txt");
	}

	void CheckBossState() {
		bool bossFound = false;
		for (Object* o : _objects) {
			if (o->GetObjectType() == Object::TypeObject::BOSS) {
				bossFound = true;
				bossSpawned = true;
				isScrolling = false;
				isSpawning = false;
				break;
			}
		}
		if (bossSpawned && !bossFound) bossDead = true;
	}
	void DrawBlackOverlay()
	{
		Uint8 r, g, b, a;
		SDL_GetRenderDrawColor(RM->GetRenderer(), &r, &g, &b, &a);
		SDL_SetRenderDrawColor(RM->GetRenderer(), 0, 0, 0, 255);
		SDL_FRect screenRect = { 0.0f, 0.0f, (float)RM->WINDOW_WIDTH, (float)RM->WINDOW_HEIGHT };
		SDL_RenderFillRect(RM->GetRenderer(), &screenRect);
		SDL_SetRenderDrawColor(RM->GetRenderer(), r, g, b, a);
	}

	void OnExit() override {

		bossSpawned = false; bossAlive = false; bossDead = false;

		if (score) {
			int finalScore = score->GetScore();
			if (SC->IsHighScore(finalScore)) {
				HighScoreEntryScene* entryScene = dynamic_cast<HighScoreEntryScene*>(SM.GetScene("HighScoreEntryScene"));
				if (entryScene) entryScene->SetCurrentScore(finalScore);
				SM.SetNextScene("HighScoreEntryScene");
			}
			else {
				SM.SetNextScene("HighScoreTableScene");
			}
		}
		if (resumeButton) { delete resumeButton; resumeButton = nullptr; }

		Scene::OnExit();
	}

	void UpdateGameplay()
	{
		Scene::Update();
		Scene::Update();
		if (horde) horde->Update();
		if (decoracion) decoracion->Update();

		CheckBossState();

		if (bossDead) {
			if (currentState != State::FINISH_STAGE) {
				victoriaImage = new ImageObject("resources/win.png", { 0, 0 }, { 1920, 1080 });

				float w = (float)RM->WINDOW_WIDTH;
				float h = (float)RM->WINDOW_HEIGHT;
				victoriaImage->GetTransform()->size = { w, h };
				victoriaImage->GetTransform()->position = { -(w / 2.0f), (h / 2.0f) };

				victoriaImage->GetTransform()->scale = { 1.f, 1.f };

				SPAWNER.SpawnObject(victoriaImage);
				currentState = State::FINISH_STAGE;
			}
		}

		if (player && player->IsDead()) {
			player->GetRigidBody()->SetVelocity({ 0,0 });
			currentState = State::DEATH;
			stateTimer = 0.0f;
		}

		if (IM->GetEvent(SDLK_ESCAPE, DOWN)) {
			currentState = State::PAUSED;
		}
	}
	void UpdatePause()
	{
		if (resumeButton)
			resumeButton->Update();
		if (IM->GetEvent(SDLK_ESCAPE, DOWN))
			currentState = State::GAMEPLAY;
	}
	void UpdateFinishStage()
	{
		Scene::Update();
		if (IM->GetEvent(SDLK_RETURN, DOWN)) {
			SavePlayerData();
			GamePersistence::comingFromLevel1 = true;
			SM.SetNextScene("Level2");
		}
	}
	void UpdateDeath()
	{
		float dt = TIME.GetDeltaTime();
		stateTimer += dt;

		if (stateTimer <= 1.5f) {
			player->GetTransform()->rotation += (800.0f * stateTimer) * dt;
		}
		else if (stateTimer <= 4.0f) {
			showBlackScreen = true;
			player->GetTransform()->position = { -2000.0f, -2000.0f };
		}
		else {
			OnExit();
		}
	}
};