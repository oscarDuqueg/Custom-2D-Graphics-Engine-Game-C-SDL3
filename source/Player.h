#pragma once
#include "ImageObject.h"
#include "RenderManager.h"
#include "Spawner.h"
#include "PlayerBullet.h"
#include "AudioManager.h"
#include "InputManager.h"
#include "PowerUp.h"
#include "UpTurret.h"
#include "DownTurret.h"
#include "darkBoll.h"
#include "GamePersistence.h"

enum class MovementPlayer
{
	UP,
	DOWN,
	RIGHT,
	LEFT,
	UPRIGHT,
	UPLEFT,
	DOWNRIGHT,
	DOWNLEFT,
};

class Player : public ImageObject
{
private:
	bool _isDead = false;
	int maxLife;
	float moveSpeed = 20000.f;

	MovementPlayer movement = MovementPlayer::RIGHT;

	float shootCooldown = 0.2f;
	float lastShootTime = 0.0f;

public:
	bool hasTwoCanon = false;
	int secondCannonFuel = 0;
	bool hasTurrets = false;
	bool hasLaser = false;
	int laserFuel = 0;
	Vector2 _lastPosition;
	Player()
		: ImageObject("resources/babyDragon.png", Vector2(0.f, 0.f), Vector2(306.f, 562.f))
	{
		Vector2 randomPosition = Vector2(RM->WINDOW_WIDTH -1200,RM->WINDOW_HEIGHT/2);
		_transform->position = randomPosition;
		_transform->scale = Vector2(0.8f, 0.8f);
		_transform->rotation = 0.f;

		_physics->SetLinearDrag(100.f);
		_physics->SetAngularDrag(100.f);
		_type = TypeObject::PLAYER;

		_physics->AddCollider(new AABB(_transform->position, _transform->size));
		maxLife = 500;
		life = maxLife;
	}

	int GetLife() { return life; }
	int GetMaxLife() { return maxLife; }
	bool GetHasTwoCanon() { return hasTwoCanon; }
	int GetSecondCannonFuel() { return secondCannonFuel; }
	bool GetHasLaser() { return hasLaser; }
	int GetLaserFuel() { return laserFuel; }
	bool GetHasTurrets() { return hasTurrets; }
	float GetMoveSpeed() { return moveSpeed; }

	// La funcion para cargar los datos en el Nivel 2
	void LoadFromPersistence() {
		this->life = GamePersistence::lastLife;
		this->hasTwoCanon = GamePersistence::hasTwoCanon;
		this->secondCannonFuel = GamePersistence::secondCannonFuel;
		this->hasLaser = GamePersistence::hasLaser;
		this->laserFuel = GamePersistence::laserFuel;
		this->hasTurrets = GamePersistence::hasTurrets;
		this->moveSpeed = GamePersistence::moveSpeed;

		if (this->hasTurrets)
			ApplyBat();
	}


	void Shoot();

	void Update() override
	{
		if (_isDead)
			return;

		_lastPosition = _transform->position;

		if (IM->GetEvent(SDLK_W, HOLD))
			movement = MovementPlayer::UP;
		else if (IM->GetEvent(SDLK_S, HOLD))
			movement = MovementPlayer::DOWN;
		else if (IM->GetEvent(SDLK_A, HOLD))
			movement = MovementPlayer::LEFT;
		else if (IM->GetEvent(SDLK_D, HOLD))
			movement = MovementPlayer::RIGHT;
		if (IM->GetEvent(SDLK_W, HOLD) && IM->GetEvent(SDLK_D, HOLD))
			movement = MovementPlayer::UPRIGHT;
		if (IM->GetEvent(SDLK_W, HOLD) && IM->GetEvent(SDLK_A, HOLD))
			movement = MovementPlayer::UPLEFT;
		if (IM->GetEvent(SDLK_S, HOLD) && IM->GetEvent(SDLK_D, HOLD))
			movement = MovementPlayer::DOWNRIGHT;
		if (IM->GetEvent(SDLK_S, HOLD) && IM->GetEvent(SDLK_A, HOLD))
			movement = MovementPlayer::DOWNLEFT;

		switch (movement)
		{
			case MovementPlayer::UP:UpdateUp(); break;
			case MovementPlayer::DOWN:UpdateDown(); break;
			case MovementPlayer::LEFT:UpdateLeft(); break;
			case MovementPlayer::RIGHT:UpdateRight(); break;
			case MovementPlayer::UPRIGHT:UpdateUpRight(); break;
			case MovementPlayer::UPLEFT:UpdateUpLeft(); break;
			case MovementPlayer::DOWNRIGHT:UpdateDownRight(); break;
			case MovementPlayer::DOWNLEFT:UpdateDownLeft(); break;
		}

		if (IM->GetEvent(SDLK_SPACE, DOWN))
			Shoot();

		//Funcion de testeo, la hemos hecho para no tener que esperar todo el nivel cada vez
		if (IM->GetEvent(SDLK_U, HOLD))
			TIME.IrAlFuturo();

		if (laserFuel <= 0)
			hasLaser = false;
		if (secondCannonFuel <= 0)
			hasTwoCanon = false;

		Object::Update();
	}
	void UpdateUp()
	{
		if (IM->GetEvent(SDLK_W, HOLD))
			_physics->AddForce(Vector2(-0.f, -moveSpeed));
	}
	void UpdateDown()
	{
		if (IM->GetEvent(SDLK_S, HOLD))
			_physics->AddForce(Vector2(0.f, moveSpeed));
	}
	void UpdateLeft()
	{
		if (IM->GetEvent(SDLK_A, HOLD))
			_physics->AddForce(Vector2(-moveSpeed, 0.f));
	}
	void UpdateRight()
	{
		if (IM->GetEvent(SDLK_D, HOLD))
			_physics->AddForce(Vector2(moveSpeed, 0.f));
	}
	void UpdateUpRight()
	{
		if (IM->GetEvent(SDLK_W, HOLD) && IM->GetEvent(SDLK_D, HOLD))
			_physics->AddForce(Vector2(moveSpeed, -moveSpeed));
	}
	void UpdateUpLeft()
	{
		if (IM->GetEvent(SDLK_W, HOLD) && IM->GetEvent(SDLK_A, HOLD))
			_physics->AddForce(Vector2(-moveSpeed, -moveSpeed));
	}
	void UpdateDownLeft()
	{
		if (IM->GetEvent(SDLK_S, HOLD) && IM->GetEvent(SDLK_A, HOLD))
			_physics->AddForce(Vector2(-moveSpeed, moveSpeed));
	}
	void UpdateDownRight()
	{
		if (IM->GetEvent(SDLK_S, HOLD) && IM->GetEvent(SDLK_D, HOLD))
			_physics->AddForce(Vector2(moveSpeed, moveSpeed));
	}


	void OnCollision(Object* other) override {
		if (other->GetObjectType() == TypeObject::WALL) 
		{	
			Vector2 currentPos = _transform->position;
			Vector2 wallPos = other->GetTransform()->position;

			Vector2 movement = currentPos - _lastPosition;

			if (movement.x != 0)
			{
				_transform->position.x = _lastPosition.x;
				_physics->SetVelocity(Vector2(0.f, _physics->GetVelocity().y));
			}

			if (movement.y != 0)
			{
				_transform->position.y = _lastPosition.y;
				_physics->SetVelocity(Vector2(_physics->GetVelocity().x, 0.f));
			}
		}

		if (other->GetObjectType() == TypeObject::POWERUP) 
		{
			if (auto* power = dynamic_cast<PowerUp*>(other)) 
			{
				ApplyPowerUp(power->GetState());
				other->Destroy();
			}
		}
	}

	void ApplyPowerUp(PowerUpState state) 
	{
		switch (state) {
		case TIER_1: 
			ApplyRage();
			break;
		case TIER_2: 
			ApplyClone(); 
			break;
		case TIER_3: 
			ApplyPoison(); 
			break;
		case TIER_4: 
			ApplySpeed();
			break;
		case TIER_5: 
			ApplyBat();
			break;
		case TIER_6:
			ApplyCure(); 
			break;
		default: break;
		}
	}

	void ApplyRage();
	void ApplyClone();
	void ApplyPoison();
	void ApplySpeed();
	void ApplyBat();
	void ApplyCure();
};