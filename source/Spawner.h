#pragma once
#include <queue>
#include "Object.h"

#define SPAWNER Spawner::Instance()

class Spawner
{
public:
	static Spawner& Instance()
	{
		static Spawner spawner;
		return spawner;
	}

	void SpawnObject(Object* obj) { spawnedObjects.push(obj); }
	bool AreObjectsPendingSpawn() { return !spawnedObjects.empty(); }

	Object* GetSpawnedObject()
	{
		if (!AreObjectsPendingSpawn())
			return nullptr;

		Object* temp = spawnedObjects.front();
		spawnedObjects.pop();
		return temp;
	}

	void ClearSpawner() {
		while (AreObjectsPendingSpawn()) {
			delete spawnedObjects.front();
			spawnedObjects.pop();
		}
	}

private:
	Spawner() = default;
	Spawner(Spawner&) = delete;
	Spawner& operator = (const Spawner&) = delete;

	std::queue<Object*> spawnedObjects;
};