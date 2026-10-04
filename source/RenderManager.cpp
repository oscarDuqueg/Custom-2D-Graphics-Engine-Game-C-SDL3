#include "RenderManager.h"
#include <cassert>
#include <SDL3_image/SDL_image.h>

void RenderManager::InitSDL()
{
	if (!SDL_Init(SDL_INIT_VIDEO))
		throw SDL_GetError();

	if (!TTF_Init())
		throw SDL_GetError();
}

void RenderManager::CreateWindowAndRederer()
{
	if (!SDL_CreateWindowAndRenderer("Test main", WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE, &_window, &_renderer))
		throw SDL_GetError();
}

void RenderManager::Init()
{
	try
	{
		InitSDL();
		CreateWindowAndRederer();
	}
	catch (std::exception& exception)
	{
		std::cout << " Error : " << exception.what();
		Release();
		return;
	}

	SDL_SetRenderDrawColor(_renderer, 180, 230, 200, 0xFF);


}

void RenderManager::Release()
{
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
}

void RenderManager::ClearScreen()
{
	SDL_RenderClear(_renderer);
}

void RenderManager::RenderScreen()
{
	SDL_RenderPresent(_renderer);
}

void RenderManager::LoadTexture(std::string path)
{
	if (_textures.find(path) != _textures.end())
		return;

	_textures[path] = IMG_LoadTexture(_renderer, path.c_str());
	assert(_textures[path]);

}

SDL_Texture* RenderManager::GetTexture(std::string path)
{
	if (_textures.find(path) != _textures.end())
		return _textures[path];

	return nullptr;
}

void RenderManager::LoadFont(std::string path)
{
	if (_fonts.find(path) != _fonts.end())
		return;

	_fonts[path] = TTF_OpenFont(path.c_str(), 24);
}

TTF_Font* RenderManager::GetFont(std::string path)
{
	if (_fonts.find(path) != _fonts.end())
		return _fonts[path];

	return nullptr;
}

RenderManager::~RenderManager()
{
	for (std::map<std::string, SDL_Texture* >::iterator it = _textures.begin(); it != _textures.end(); it++)
	{
		SDL_DestroyTexture(it->second);
		it->second = nullptr;
	}

	for (std::map < std::string, TTF_Font* >::iterator it = _fonts.begin(); it != _fonts.end(); it++)
	{
		TTF_CloseFont(it->second);
		it->second = nullptr;
	}
}
