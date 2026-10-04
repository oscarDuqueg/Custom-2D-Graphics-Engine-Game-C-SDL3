#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <map>
#include <string>
#include <iostream>

#define RM RenderManager::GetInstance()

class RenderManager {
	//singleton
public:
	static RenderManager* GetInstance() {
		static RenderManager instance;
		return &instance;
	}

	const int WINDOW_WIDTH = 1360;
	const int WINDOW_HEIGHT = 768;

	//singleton

	void Init();
	void Release();
	void ClearScreen();
	void RenderScreen();

	SDL_Renderer* GetRenderer() { return _renderer; }
	void LoadTexture(std::string path);
	SDL_Texture* GetTexture(std::string path);

	void LoadFont(std::string path);
	
	TTF_Font* GetFont(std::string path);

private:
	//Singleton
	RenderManager() = default;
	RenderManager(RenderManager&) = delete;
	RenderManager& operator=(const RenderManager&) = delete;
	~RenderManager(); //Singleton

	SDL_Window* _window;
	SDL_Renderer* _renderer;
	std::map<std::string, SDL_Texture*> _textures;
	std::map<std::string, TTF_Font*> _fonts;

	void InitSDL();
	void CreateWindowAndRederer();
};


	