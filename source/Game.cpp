#include "Game.h"
#include "ImageObject.h"
#include "Player.h"
#include "SceneManager.h"
#include "Gameplay.h"
#include "MainMenu.h"
#include "Level2.h"
#include "AudioManager.h"
#include "HighScoreEntryScene.h"
#include "HighScoreTableScene.h"
#include "SplashScreen.h"

#include <cassert>


void Game::Init()
{
	RM->Init();

	// Aquí la càrrega de tots els recursos del joc
	//Textures
	RM->LoadTexture("resources/Fondo.png");
	RM->LoadTexture("resources/loFondo.png");
	RM->LoadTexture("resources/loloFondo.png");
	RM->LoadTexture("resources/babyDragon.png");
	RM->LoadTexture("resources/locavall.png");
	RM->LoadTexture("resources/lopeix.png");
	RM->LoadTexture("resources/esbirroV.png");
	RM->LoadTexture("resources/esbirroH.png");
	RM->LoadTexture("resources/rompemuro.png");
	RM->LoadTexture("resources/bolaDeFuego.png");
	RM->LoadTexture("resources/BlackRectangle.png");
	RM->LoadTexture("resources/Fondo.png");
	RM->LoadTexture("resources/loFondo.png");
	RM->LoadTexture("resources/loloFondo.png");
	RM->LoadTexture("resources/bat.png");
	RM->LoadTexture("resources/esqueleto.png");
	RM->LoadTexture("resources/bruja.png");
	RM->LoadTexture("resources/barbaro.png");
	RM->LoadTexture("resources/yeti.png");
	RM->LoadTexture("resources/lava.png");
	RM->LoadTexture("resources/golem.png");
	RM->LoadTexture("resources/roca.png");
	RM->LoadTexture("resources/monta.png");
	RM->LoadTexture("resources/gigante.png");
	RM->LoadTexture("resources/duende.png");
	RM->LoadTexture("resources/globo.png");
	RM->LoadTexture("resources/sanadora.png");
	RM->LoadTexture("resources/raiz.png");
	RM->LoadTexture("resources/valquiria.png");
	RM->LoadTexture("resources/pekka.png");
	RM->LoadTexture("resources/electrico.png");
	RM->LoadTexture("resources/helicoptero.png");
	RM->LoadTexture("resources/bomba.png");
	
	RM->LoadTexture("resources/WallX.png");
	RM->LoadTexture("resources/WallY.png");
	RM->LoadTexture("resources/level1.png");
	RM->LoadTexture("resources/level2.png");
	
	RM->LoadTexture("resources/loFondo2.png");
	RM->LoadTexture("resources/Fondo2.png");
	
	RM->LoadTexture("resources/boom.png");
	RM->LoadTexture("resources/loboom.png");

	RM->LoadTexture("resources/lochoza.png");
	RM->LoadTexture("resources/loasedio.png");
	RM->LoadTexture("resources/loth13.png");
	RM->LoadTexture("resources/loth15.png");

	RM->LoadTexture("resources/speedSpell.png");
	RM->LoadTexture("resources/poisonSpell.png");
	RM->LoadTexture("resources/rageSpell.png");
	RM->LoadTexture("resources/cloneSpell.png");
	RM->LoadTexture("resources/cureSpell.png");
	RM->LoadTexture("resources/batSpell.png");

	RM->LoadTexture("resources/sneezy.png");
	RM->LoadTexture("resources/ballBat.png");
	RM->LoadTexture("resources/darkBoll.png");
	RM->LoadTexture("resources/backToMenu.png");
	RM->LoadTexture("resources/TableScore.png");
	RM->LoadTexture("resources/splashimage.png");
	RM->LoadTexture("resources/resume.png");
	RM->LoadTexture("resources/pausa.png");
	RM->LoadTexture("resources/win.png");

	//Fonts

	RM->LoadFont("resources/fonts/hyperspace.ttf");
	TTF_Font* f = RM->GetFont("resources/fonts/hyperspace.ttf");
	if (!f) {
		std::cout << "[INIT] FUENTE NO CARGADA: " << SDL_GetError() << " / " << SDL_GetError() << std::endl;
	}

	//RM->LoadFont("resources/fonts/hyperspace.ttf");

	AM->Init();

	// Audio
	AM->LoadSoundData("resources/audio/fireball.wav");
	AM->LoadSoundData("resources/audio/hit.wav");
	AM->LoadSoundData("resources/audio/gameplay.wav");


	// Aquí la càrrega de totes les escenes
	assert(SM.AddScene("SplashScreen", new SplashScreen()));
	assert(SM.AddScene("MainMenu", new MainMenu()));
	assert(SM.AddScene("Gameplay", new Gameplay()));
	assert(SM.AddScene("Level2", new Level2()));

	assert(SM.AddScene("HighScoreEntryScene", new HighScoreEntryScene()));
	assert(SM.AddScene("HighScoreTableScene", new HighScoreTableScene()));

	assert(SM.InitFirstScene("SplashScreen"));

	_isRunning = true;
}

void Game::HandleEvents()
{
	_isRunning = !IM->Listen();
}

void Game::Update()
{
	SM.UpdateCurrentScene();
}

void Game::Render()
{
	RM->ClearScreen();
	SM.GetCurrentScene()->Render();
	RM->RenderScreen();
}

