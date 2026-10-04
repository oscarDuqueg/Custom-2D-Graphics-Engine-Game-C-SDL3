#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <cassert>
#include "Renderer.h"
#include "RenderManager.h"

#define FONT_PATH "resources/fonts/hyperspace.ttf"


class TextRenderer : public Renderer
{
protected:
	std::string _text;
	SDL_Texture* _textTexture;
	bool _autoSize = true;

public:
	TextRenderer(Transform* transform, std::string text)
		: Renderer(transform, FONT_PATH)
	{
		SetText(text);
	}
	~TextRenderer()
	{
		SDL_DestroyTexture(_textTexture);
		_textTexture = nullptr;

	}

	virtual void Update(float dt) override
	{
		Vector2 offset = (Vector2(-_transform->size.x, -_transform->size.y) / 2.0f) * _transform->scale;

		_destinationRect.x = _transform->position.x + offset.x;
		_destinationRect.y = _transform->position.y + offset.y;

		if (_autoSize)
		{
			_destinationRect.w = _sourceRect.w * _transform->scale.x;
			_destinationRect.h = _sourceRect.h * _transform->scale.y;
		}
		else
		{
			_destinationRect.w = _transform->size.x * _transform->scale.x;
			_destinationRect.h = _transform->size.y * _transform->scale.y;
		}
	}

	virtual void Render() override
	{
		SDL_RenderTextureRotated(
			RM->GetRenderer(),
			_textTexture,
			&_sourceRect,
			&_destinationRect,
			_transform->rotation,
			NULL,
			SDL_FLIP_NONE
		);
	}


	//void SetText(std::string text)
	//{
	//	// 1) Destruir la textura (que té el text anterior )
	//	if (_textTexture != nullptr)
	//		SDL_DestroyTexture(_textTexture);

	//	// 2) Crear surface
	//	SDL_Surface* surf = TTF_RenderText_Solid(RM->GetFont(_resourcePath), text.c_str(), text.length(), _color);
	//	//SDL_Surface* surf = TTF_RenderText_Solid(font, text.c_str(), _color);
	//	assert(surf);

	//	// 3) Crear textura
	//	_textTexture = SDL_CreateTextureFromSurface(RM->GetRenderer(), surf);
	//	assert(_textTexture);

	//	// 4) Definir source rect
	//	_sourceRect = { 0.f, 0.f, (float)surf->w, (float)surf->h };

	//	// 5) Actualitzar string
	//	_text = text;
	//}


	void SetText(std::string text)
	{
		if (text.empty())
		{
			std::cout << "TextRenderer Ignorando texto vacío" << std::endl;
			return;
		}

		// Destruir textura anterior
		if (_textTexture != nullptr)
		{
			SDL_DestroyTexture(_textTexture);
			_textTexture = nullptr;
		}

		// Obtener fuente
		TTF_Font* font = RM->GetFont(_resourcePath);
		if (!font)
		{
			std::cout << "TextRenderer Fuente NULL para path: " << _resourcePath << std::endl;
			return;
		}

		// Renderizar (tu versión original de 4 params)
		SDL_Surface* surf = TTF_RenderText_Solid(font, text.c_str(), static_cast<int>(text.length()), _color);

		if (!surf)
		{
			std::cout << "TextRenderer Fallo renderizando '" << text << "' -> " << SDL_GetError() << std::endl;
			if (_textTexture) 
			{
				SDL_DestroyTexture(_textTexture);
				_textTexture = nullptr;
			}
			return;
		}

		// Crear textura
		_textTexture = SDL_CreateTextureFromSurface(RM->GetRenderer(), surf);
		if (!_textTexture)
		{
			std::cout << "TextRenderer, fallo creando textura: " << SDL_GetError() << std::endl;
			SDL_DestroySurface(surf); 
			return;
		}

		// Source rect
		_sourceRect = { 0.f, 0.f, static_cast<float>(surf->w), static_cast<float>(surf->h) };
		_text = text;
		SDL_DestroySurface(surf);
	}

	void SetColor(SDL_Color color) override {
		Renderer::SetColor(color);
		SetText(_text);
	}
};