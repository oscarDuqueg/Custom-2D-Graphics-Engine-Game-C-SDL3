#pragma once
#include "AABB.h"
#include "Transform.h"
#include <vector>

class RigidBody
{
private:
	std::vector<AABB*> _colliders;
	Transform* _transform;

	Vector2 _velocity;
	float _angularVelocity;

	Vector2 _acceleration;
	float _angularAceeleration;

	float _linearDrag;
	float _angularDrag;

public:
	RigidBody(Transform* transfrom)
		: _transform(transfrom), _velocity(Vector2()), _angularVelocity(0.0f),
		_acceleration(Vector2()), _angularAceeleration(0.0f),
		_linearDrag(0.0f), _angularDrag(0.0f) {
	}

	~RigidBody()
	{
		for (AABB* collider : _colliders)
			delete collider;

		_colliders.clear();
	}

	void AddCollider(AABB* collider) { _colliders.push_back(collider); }

	void AddForce(Vector2 force) { _acceleration = _acceleration + force; }

	void AddTorque(float amount) { _angularAceeleration += amount; }

	Vector2 const GetVelocity() { return _velocity; }
	void SetVelocity(Vector2 velocity) { _velocity = velocity; }
	void SetLinearDrag(float linearDrag) { _linearDrag = linearDrag; }
	void SetAngularDrag(float angularDrag) { _angularDrag = angularDrag; }

	bool CheckCollision(const RigidBody* other);
	bool CheckOverlappingPoint(Vector2 point);

	void Update(float dt);

	std::vector<AABB*>& GetColliders() { return _colliders; }
};