#pragma once
#include "Object.h"
#include <vector>
#include "Spawner.h"
#include "SceneManager.h"

class Scene
{
protected:
	std::vector<Object*> _objects;
	std::vector<Object*> _ui;
public:

	Scene() = default;
	virtual void OnEnter() = 0;

	virtual void OnExit()
	{
		SPAWNER.ClearSpawner();

		for (Object* o : _objects)
			delete o;

		_objects.clear();

		for (Object* u : _ui)
			delete u;

		_ui.clear();
	}
	virtual void Update()
	{
		// 1) Destruir
		for (int i = _objects.size() - 1; i >= 0; i--)
		{
			if (_objects[i]->IsPendingDestroy())
			{
				delete _objects[i];
				_objects.erase(_objects.begin() + i);
			}
		}

		for (int i = _ui.size() - 1; i >= 0; i--)
		{
			if (_ui[i]->IsPendingDestroy())
			{
				delete _ui[i];
				_ui.erase(_ui.begin() + i);
			}
		}

		// 2) Spawning

		while (SPAWNER.AreObjectsPendingSpawn()) {
			Object* obj = SPAWNER.GetSpawnedObject();
			_objects.push_back(obj);
			//std::cout << "Spawneado objeto: " << obj << " tamaño _objects: " << _objects.size() << "\n";
			//_objects.push_back(SPAWNER.GetSpawnedObject());
		}

		// 3) Actualitzar
		for (Object* o : _objects)
			o->Update();

		for (Object* u : _ui)
			u->Update();

		// 4) Comprovar col·lisions
		int size = _objects.size();
		for (int i = 0; i < size; i++)
		{
			for (int j = i + 1; j < _objects.size(); j++)
			{
				if (_objects[i]->GetRigidBody()->CheckCollision(_objects[j]->GetRigidBody()))
				{
					_objects[i]->OnCollision(_objects[j]);
					_objects[j]->OnCollision(_objects[i]);
				}
			}
		}

		size = _ui.size();
		for (int i = 0; i < size; i++)
		{
			for (int j = i + 1; j < _ui.size(); j++)
			{
				if (_ui[i]->GetRigidBody()->CheckCollision(_ui[j]->GetRigidBody()))
				{
					_ui[i]->OnCollision(_ui[j]);
					_ui[j]->OnCollision(_ui[i]);
				}
			}
		}
	}

	virtual void Render()
	{
		for (Object* o : _objects)
			o->Render();
		for (Object* u : _ui)
			u->Render();
	}

	virtual std::string GetName() { return "Father, Unknown"; }
};