#pragma once
#include "Transform.h"
#include "Renderer.h"
#include "RigidBody.h"
#include <memory>
#include <iostream>

class Object
{
private:
	bool _isPendingDestroy = false;
protected:
	Renderer* _renderer = nullptr;
	std::unique_ptr<Transform> _transform;
	std::unique_ptr<RigidBody> _physics;
	int life = 100;
	bool dead = false;

public:
	enum TypeObject {
		PLAYER = 10,
		ENEMY, WALL, ENEMYBULLET, PLAYERBULLET, UI, BASE, BOSS, POWERUP
	};
	bool IsDead() const { return dead; }
	TypeObject _type;

	Object()
	{
		_transform = std::make_unique<Transform>();
		_physics = std::make_unique<RigidBody>(_transform.get());
		_type = TypeObject::BASE;
	}

	virtual ~Object() = default;

	virtual void Update()
	{
		if (_physics != nullptr)
			_physics->Update(0.02);

		if (_renderer != nullptr)
			_renderer->Update(0.02f); //50 fps

		//Inicializar cada enemigo y Además el player con vida, pq sino no VA COSAAA, pa después del merge

		if (life <= 0) {
			if (_type == PLAYER)
				dead = true;
			else if(_type == ENEMY)
				Destroy();
		}
	}

	virtual void Render()
	{
		_renderer->Render();
	}

	Transform* GetTransform() { return _transform.get(); }

	bool IsPendingDestroy() const { return _isPendingDestroy; }
	virtual void Destroy() { _isPendingDestroy = true; }

	RigidBody* GetRigidBody() { return _physics.get(); }

	//Funcion para determinar colisiones; lo mismo que en unity basicamente Carlos
	virtual void OnCollision(Object* other) {}

	//Funcion para encontrar el tipo del objeto con el que chocas y para determinar lo que hacer más adelante en otra funcion
	//Es como el tag del Unity
	TypeObject GetObjectType() { return _type; }

	void LoseLife(int amount) {
		life -= amount;
	}
};