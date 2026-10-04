#pragma once
#include "ImageObject.h"
#include "RenderManager.h"
#include "TimeManager.h"
#include <string>

class elsDecoratius : public ImageObject 
{
private:
	float totalTime = 0.f;
	bool isUp;
	
public:
	elsDecoratius(Vector2 direction) : ImageObject(ChooseSprite(), Vector2(0.f, 0.f), Vector2(306.f, 562.f)) 
	{

		isUp = (rand() % 2 == 0);
		float upCoords = 35.f;
		float downCoords = RM->WINDOW_HEIGHT - 35.f;

		//Elige la posicion según si va arriba o abajo
		_transform->position = Vector2(static_cast<float>(RM->WINDOW_WIDTH), isUp ? (upCoords) : (downCoords));
		_transform->scale = Vector2(2.f, 2.f);
		_transform->rotation = 0.f;

		direction.Normalize();
		_physics->SetVelocity(direction * 120.f);

		_transform->rotation = isUp ? 180.0f : 0.0f;

		_physics->SetLinearDrag(0.f);
		_physics->SetAngularDrag(0.f);
		_type = TypeObject::BASE;
	}

	~elsDecoratius() {
	}

	void Update() override 
	{
		totalTime += TIME.GetDeltaTime();

		if (totalTime >= 12.f)
		{
			Object::Destroy();
			totalTime = 0;
		}
		Object::Update();
	}
	
private:
	static std::string ChooseSprite() 
	{
		static std::string sprites[] =
		{
			"resources/lochoza.png",
			"resources/loasedio.png",
			"resources/loth13.png",
			"resources/loth15.png",
			"resources/th16.png"
		};
		return sprites[rand() % (sizeof(sprites) / sizeof(sprites[0]))];
	}
};





