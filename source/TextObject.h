#pragma once
#include "Object.h"
#include "TextRenderer.h"

class TextObject : public Object
{
private:
	TypeObject _type;

public:
	TextObject(std::string text)
		:Object()
	{
		_renderer = new TextRenderer(_transform.get(), text);
		_renderer->SetColor({ 0, 255, 0, 0xFF });

		_type = TypeObject::UI;
	}

	void SetText(std::string text)
	{
		dynamic_cast<TextRenderer*>(_renderer)->SetText(text);
	}

	void SetParticularColor(SDL_Color color) 
	{
		_renderer->SetColor(color);
	}
};