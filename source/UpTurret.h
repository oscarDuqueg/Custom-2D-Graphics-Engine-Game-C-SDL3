#pragma once
#include "ImageObject.h"
#include "RenderManager.h"
#include "Player.h"
#include "InputManager.h"
#include "PlayerBullet.h"

class UpTurret : public ImageObject
{
private:
    Transform* playerTransform;
    Vector2    offset;
    float shootCooldown = 0.2f;
    float lastShootTime = 0.0f;
public:
    UpTurret(Transform* playerTr, Vector2 initialOffset)
        : ImageObject("resources/sneezy.png", Vector2(0.f, 0.f), Vector2(306.f, 562.f)), playerTransform(playerTr), offset(initialOffset)
    {
        _transform->position = playerTransform->position + offset;
        _transform->scale = Vector2(1.f, 1.f);
        _transform->rotation = 0.f;

        _physics->SetLinearDrag(100.f);
        _physics->SetAngularDrag(100.f);
        _type = TypeObject::BASE;
        _physics->AddCollider(new AABB(_transform->position, _transform->size));
    }

    void Update() override
    {
        if (playerTransform == nullptr)
        {
            Destroy();
            return;
        }
        _transform->position = playerTransform->position + offset;

        if (IM->GetEvent(SDLK_SPACE, DOWN))
        {
            Shoot();
        }

        Object::Update();
    }

    void Shoot()
    {
        float currentTime = TIME.GetElapsedTime();

        if (currentTime - lastShootTime < shootCooldown)
            return;

        lastShootTime = currentTime;
        Vector2 direction(1.f, 0.f);
        PlayerBullet* bullet = new PlayerBullet(_transform.get(), direction, Vector2(0.f, 0.f));

        SPAWNER.SpawnObject(bullet);
    }
};