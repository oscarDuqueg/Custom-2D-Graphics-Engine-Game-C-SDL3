#pragma once
#include "Object.h"
#include <SDL3/SDL.h>
#include "InputManager.h"
#include "RenderManager.h"

class Game
{
public:
	Game() = default;

	void Init();
	void HandleEvents();
	void Update();
	void Render();
	void Release() {
		RM->Release();
	}

	bool IsRunning() const { return _isRunning; }

private:
	bool _isRunning;
	SDL_Window* _window;
	SDL_Renderer* _renderer;
};