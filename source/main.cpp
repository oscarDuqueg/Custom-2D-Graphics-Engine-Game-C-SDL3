#include "Game.h"
#include "RenderManager.h"
#include <SDL3/SDL.h>
#include <exception>
#include <iostream>
#include "TimeManager.h"

int main()
{
	srand(time(NULL));

	//mirarse esto que es audio y no se si esta bien
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS) < 0)
	{
		std::cout << "SDL Init error: " << SDL_GetError() << std::endl;
		return -1;
	}

	Game game;

	try
	{
		game.Init();
	}
	catch (std::exception& e)
	{
		std::cout << "Error: " << e.what();
		game.Release();
		return -1;
	}

	while (game.IsRunning())
	{
		TIME.Update();
		if (TIME.ShouldUpdateGame())
		{
			game.HandleEvents();
			game.Update();
			game.Render();
			TIME.ResetDeltaTime();
		}
	}

	game.Release();

	return 0;
}