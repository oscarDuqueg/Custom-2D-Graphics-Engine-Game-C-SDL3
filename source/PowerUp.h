#pragma once
#include "ImageObject.h"
#include "RenderManager.h"
#include <string>
#include "TimeManager.h"
#include "Player.h"

enum PowerUpState 
{
	TIER_1 = 0,
	TIER_2 = 1,
	TIER_3 = 2,
	TIER_4 = 3,
	TIER_5 = 4,
	TIER_6 = 5
};

class PowerUp : public ImageObject
{
private:
    PowerUpState state;
    float loTime = 0.0f;

public:
    PowerUp(Vector2 position)
        : ImageObject(ChooseSprite(0), Vector2(0.f, 0.f), Vector2(600.f, 562.f))
    {
        _transform->position = position;
        _transform->scale = Vector2(0.8f, 0.8f);
        _transform->rotation = 0.f;

        _type = TypeObject::POWERUP;
        state = TIER_1;
        life = 1024;

        _physics->AddCollider(new AABB(_transform->position, _transform->size));
        _physics->SetVelocity(Vector2(-1.f, 0.f) * 150.f);
    }

    void Update() override
    {
        loTime += TIME.GetDeltaTime();
        if (loTime >= 25.f) Destroy();

        PowerUpState newTier;

        if (life > 1020) newTier = TIER_1;
        else if (life > 1018) newTier = TIER_2;
        else if (life > 1016) newTier = TIER_3;
        else if (life > 1014) newTier = TIER_4;
        else if (life > 1012) newTier = TIER_5;
        else newTier = TIER_6;

        if (newTier != state)
        {
            state = newTier;
            UpdateAppearanceBasedOnTier();
        }
        
        Object::Update();
    }

    PowerUpState GetState() { return state; }

private:
    void UpdateAppearanceBasedOnTier()
    {
        SetTexture(ChooseSprite(static_cast<int>(state)));
    }

    static std::string ChooseSprite(int index)
    {
        static std::string sprites[] =
        {
            "resources/rageSpell.png",
            "resources/cloneSpell.png",
            "resources/poisonSpell.png",
            "resources/speedSpell.png",
            "resources/batSpell.png",
            "resources/cureSpell.png",
        };
        return sprites[index];
    }
};
