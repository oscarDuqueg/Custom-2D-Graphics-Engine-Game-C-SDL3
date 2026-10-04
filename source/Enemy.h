#pragma once
#include "ImageObject.h"
#include "RenderManager.h"
#include "Explosion.h"
#include "Player.h"
#include "Score.h"
#include "HordeTracker.h"

class Enemy : public ImageObject
{
private:
	Score* score;
protected:
	HordeTracker* tracker = nullptr;
	int contactDamage = 1;
	int scoreValue = 0;
	int powerUpCount = 0;
	Player* player;
public:
	Enemy(std::string texturePath, Vector2 startPos, Score* sharedScore, HordeTracker* tracker)
		: ImageObject(texturePath, Vector2(0.f, 0.f), Vector2(306.f, 562.f)), score(sharedScore), tracker(tracker)
	{
		_transform->position = startPos;
		_transform->scale = Vector2(1.f, 1.f);
		_transform->rotation = 0.f;

		_physics->SetLinearDrag(0.f);
		_physics->SetAngularDrag(0.f);

		_type = TypeObject::ENEMY;

		_physics->AddCollider(new AABB(_transform->position, _transform->size));

		if (!tracker) 
		{
			std::cout << "[WARNING] Enemy creado sin HordeTracker!\n";
		}
	}

	virtual void Update() override
	{
		if (this->life <= 0)
		{
   			CreateEffect();
			score->Add(scoreValue);

			if (tracker) {
				tracker->ReportLastKnownPosition(_transform->position);
				tracker->OnEnemyKilled();
			}
		}
		Object::Update();
		
	}
	void OnCollision(Object* other) override {
		if (other->GetObjectType() == TypeObject::PLAYER)
		{
			other->LoseLife(contactDamage);
			// esto me peta de una manera el PC, es el audio de cuando recibes daño
			//AM->PlaySound("resources/audio/hit.wav"); 
		}
	}

	void CreateEffect() {
		Vector2 explosionPos = this->_transform->position;
		Vector2 basePos = this->_transform->position;
 		Explosion* loboom = new Explosion(_transform.get());
  		SPAWNER.SpawnObject(loboom);

		if (_type == TypeObject::BOSS) {
			Vector2 bossPos = { static_cast<float>(RM->WINDOW_WIDTH) - 500,
								static_cast<float>(RM->WINDOW_HEIGHT) / 2 };

			for (int i = 0; i < 30; ++i) {
				float offsetX = static_cast<float>(rand() % 200 - 100);
				float offsetY = static_cast<float>(rand() % 200 - 100);

				Vector2 explosionPos = { bossPos.x + offsetX, bossPos.y + offsetY };

				Transform* tempTransform = new Transform();
				tempTransform->position = explosionPos;

				Explosion* bigBoom = new Explosion(tempTransform);
				SPAWNER.SpawnObject(bigBoom);
			}
		}
	}
};
