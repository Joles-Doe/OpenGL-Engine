#include "PhysicsManager.h"

#include <iostream>

PhysicsManager::PhysicsManager(std::shared_ptr<TimeManager> _time)
{
	mTimeManager = _time;
}

void PhysicsManager::Update()
{
	CullDeletedRigidbodies();
	//implement spatial partitioning, eventually

	for (int i = 0; i < mRigidbodies.size(); i++)
	{
		mRigidbodies[i]->Update(mTimeManager->DeltaTime());
	}

	//Iterate through every pair to check for collision
	for (int i = 0; i < mRigidbodies.size() - 1; i++)
	{
		for (int x = i + 1; x < mRigidbodies.size(); x++)
		{
			// If pair is colliding
			if (mRigidbodies[i]->GetCollider()->IsColliding(mRigidbodies[x]->GetCollider()))
			{
				// Call the appropriate collision response dependent on collider shape
				switch (mRigidbodies[i]->GetCollider()->GetShape())
				{
				case CUBE:
					switch (mRigidbodies[x]->GetCollider()->GetShape())
					{
					case CUBE:
						ResponseCubeToCube(mRigidbodies[i], mRigidbodies[x]);
						break;
					case SPHERE:
						ResponseCubeToSphere(mRigidbodies[i], mRigidbodies[x]);
						break;
					}
					break;
				case SPHERE:
					switch (mRigidbodies[x]->GetCollider()->GetShape())
					{
					case CUBE:
						ResponseCubeToSphere(mRigidbodies[x], mRigidbodies[i]);
						break;
					case SPHERE:
						ResponseSphereToSphere(mRigidbodies[i], mRigidbodies[x]);
						break;
					}
					break;
				}

				// For each rigidbody, check if they've already collided, and call the appropriate Gameobject Collision function if they have
				if (mRigidbodies[i]->RigidbodyAlreadyCollided(mRigidbodies[x]))
				{
					mRigidbodies[i]->GetParent().lock()->OnCollisionStay(mRigidbodies[x]);
				}
				else
				{
					mRigidbodies[i]->AddCollidedRigidbody(mRigidbodies[x]);
					mRigidbodies[i]->GetParent().lock()->OnCollisionEnter(mRigidbodies[x]);
				}

				if (mRigidbodies[x]->RigidbodyAlreadyCollided(mRigidbodies[i]))
				{
					mRigidbodies[x]->GetParent().lock()->OnCollisionStay(mRigidbodies[i]);
				}
				else
				{
					mRigidbodies[x]->AddCollidedRigidbody(mRigidbodies[i]);
					mRigidbodies[x]->GetParent().lock()->OnCollisionEnter(mRigidbodies[i]);
				}
			}
			// If there's been no collision detected, check if the rigidbodies had collided last frame and call the appropritae Gameobject collision function
			else
			{
				if (mRigidbodies[i]->RigidbodyAlreadyCollided(mRigidbodies[x]))
				{
					mRigidbodies[i]->RemoveCollidedRigidbody(mRigidbodies[x]);
					mRigidbodies[i]->GetParent().lock()->OnCollisionExit(mRigidbodies[x]);
				}

				if (mRigidbodies[x]->RigidbodyAlreadyCollided(mRigidbodies[i]))
				{
					mRigidbodies[x]->RemoveCollidedRigidbody(mRigidbodies[i]);
					mRigidbodies[x]->GetParent().lock()->OnCollisionExit(mRigidbodies[i]);
				}
			}
		}
	}
}

void PhysicsManager::Add(std::shared_ptr<Rigidbody> _rb)
{
	mRigidbodies.push_back(_rb);
}

void PhysicsManager::CullDeletedRigidbodies()
{
	mRigidbodies.erase(
		std::remove_if(mRigidbodies.begin(), mRigidbodies.end(),
			[](const std::shared_ptr<Rigidbody>& rb) 
			{
				return rb->GetParent().expired();
			}),
		mRigidbodies.end());
}

void PhysicsManager::ResponseCubeToCube(std::shared_ptr<Rigidbody> _c1, std::shared_ptr<Rigidbody> _c2)
{
	// Check if either object is dynamic
	bool c1Dynamic = _c1->IsDynamic();
	bool c2Dynamic = _c2->IsDynamic();

	glm::vec3 delta = _c1->GetCollider()->GetCenter() - _c2->GetCollider()->GetCenter();

	// Get overlap in each axis
	float overlapX = (_c1->GetCollider()->GetWidth() / 2.0f + _c2->GetCollider()->GetWidth() / 2.0f) - glm::abs(delta.x);
	float overlapY = (_c1->GetCollider()->GetHeight() / 2.0f + _c2->GetCollider()->GetHeight() / 2.0f) - glm::abs(delta.y);
	float overlapZ = (_c1->GetCollider()->GetDepth() / 2.0f + _c2->GetCollider()->GetDepth() / 2.0f) - glm::abs(delta.z);

	// Find the normal based on the smallest overlap
	glm::vec3 normal(0.0f);
	float minOverlap;
	if (overlapX < overlapY && overlapX < overlapZ)
	{
		normal.x = (delta.x < 0) ? -1.0f : 1.0f;
		minOverlap = overlapX;
	}
	else if (overlapY < overlapZ)
	{
		normal.y = (delta.y < 0) ? -1.0f : 1.0f;
		minOverlap = overlapY;
	}
	else
	{
		normal.z = (delta.z < 0) ? -1.0f : 1.0f;
		minOverlap = overlapZ;
	}

	// Calculate inverse mass
	float invMass1 = c1Dynamic ? 1.0f / _c1->Mass() : 0.0f;
	float invMass2 = c2Dynamic ? 1.0f / _c2->Mass() : 0.0f;
	float totalInvMass = invMass1 + invMass2;

	// Positional correction variables
	const float slop = 0.01f;
	const float percent = 0.8f;
	
	// Calculate the amount of movement needed to move the cubes out of each other
	float correctionMagnitude = glm::max(minOverlap - slop, 0.0f);
	glm::vec3 correction = normal * correctionMagnitude * percent;

	if (c1Dynamic && c2Dynamic)
	{
		_c1->GetTransform()->Move(correction * 0.5f);
		_c2->GetTransform()->Move(-correction * 0.5f);
	}
	else if (c1Dynamic)
	{
		_c1->GetTransform()->Move(correction);
	}
	else if (c2Dynamic)
	{
		_c2->GetTransform()->Move(-correction);
	}

	// Relative velocity
	glm::vec3 r1 = _c1->GetCollider()->GetCenter() - _c1->GetTransform()->Position();
	glm::vec3 r2 = _c2->GetCollider()->GetCenter() - _c2->GetTransform()->Position();

	glm::vec3 v1 = _c1->Velocity() + glm::cross(_c1->AngularVelocity(), r1);
	glm::vec3 v2 = _c2->Velocity() + glm::cross(_c2->AngularVelocity(), r2);

	glm::vec3 relativeVel = v1 - v2;

	// Calculate velocity along the normal
	float velAlongNormal = glm::dot(relativeVel, normal);

	if (velAlongNormal < 0.0f)
	{
		// Use the minimum restitution (elasticity)
		float e = glm::min(_c1->Elasticity(), _c2->Elasticity());

		// ============================================================
		// Compute cross products
		glm::vec3 crossR1 = glm::cross(r1, normal);
		glm::vec3 crossR2 = glm::cross(r2, normal);

		// Compute inverse tensors
		glm::mat3 invInertia1 = glm::inverse(_c1->InertiaTensorWorld());
		glm::mat3 invInertia2 = glm::inverse(_c2->InertiaTensorWorld());

		// Compute the terms involving the inverse inertia tensors and cross products
		glm::vec3 temp1 = invInertia1 * crossR1;
		glm::vec3 temp2 = invInertia2 * crossR2;

		// Compute the final dot products
		float dot1 = glm::dot(normal, temp1);
		float dot2 = glm::dot(normal, temp2);

		float denominator = totalInvMass + dot1 + dot2;

		float j = (-(1.0f + e) * velAlongNormal) / denominator;
		// ============================================================
		
		glm::vec3 impulse = j * normal;

		if (c1Dynamic)
		{
			_c1->Velocity(_c1->Velocity() + (impulse * invMass1));
			_c1->AngularVelocity(_c1->AngularVelocity() - glm::inverse(_c1->InertiaTensorWorld()) * glm::cross(r1, impulse));
		}
		if (c2Dynamic)
		{
			_c2->Velocity(_c2->Velocity() - (impulse * invMass2));
			_c2->AngularVelocity(_c2->AngularVelocity() + glm::inverse(_c2->InertiaTensorWorld()) * glm::cross(r2, impulse));
		}
	}
}

void PhysicsManager::ResponseCubeToSphere(std::shared_ptr<Rigidbody> _c1, std::shared_ptr<Rigidbody> _s1)
{
	// Check objects are dynamic
	bool c1Dynamic = _c1->IsDynamic();
	bool s1Dynamic = _s1->IsDynamic();

	// Get centers and half extents
	glm::vec3 cubeCenter = _c1->GetCollider()->GetCenter();
	glm::vec3 sphereCenter = _s1->GetCollider()->GetCenter();
	glm::vec3 halfExtents(
		_c1->GetCollider()->GetWidth() / 2.0f,
		_c1->GetCollider()->GetHeight() / 2.0f,
		_c1->GetCollider()->GetDepth() / 2.0f
	);

	// Find the closest point on the cube to the sphere center
	glm::vec3 closestPoint = glm::clamp(
		sphereCenter,
		cubeCenter - halfExtents,
		cubeCenter + halfExtents
	);

	// Vector from closest point to sphere center
	glm::vec3 delta = sphereCenter - closestPoint;
	float dist = glm::length(delta);
	if (dist == 0.0f) dist = 0.0001f; // avoid divide-by-zero

	// Calculate normal, and penetration between the two shapes
	glm::vec3 normal = delta / dist;
	float penetration = _s1->GetCollider()->GetRadius() - dist;

	// Calculate inverse mass
	float invMass1 = c1Dynamic ? 1.0f / _c1->Mass() : 0.0f;
	float invMass2 = s1Dynamic ? 1.0f / _s1->Mass() : 0.0f;
	float totalInvMass = invMass1 + invMass2;

	// Positional correction variables
	float percent = 0.8f;
	float slop = 0.001f;

	if (penetration >= 0.0f)
	{
		glm::vec3 separation = normal * ((penetration - slop) / totalInvMass) * percent;

		if (c1Dynamic && s1Dynamic)
		{
			_c1->GetTransform()->Move(-separation * 0.5f);
			_s1->GetTransform()->Move(separation * 0.5f);
		}
		else if (c1Dynamic)
		{
			_c1->GetTransform()->Move(-separation);
		}
		else if (s1Dynamic)
		{
			_s1->GetTransform()->Move(separation);
		}

		// Relative velocity
		glm::vec3 relativeVel = _s1->Velocity() - _c1->Velocity();
		float velAlongNormal = glm::dot(relativeVel, normal);

		if (velAlongNormal < 0)
		{
			// Use the minimum restitution (elasticity)
			float e = glm::min(_c1->Elasticity(), _s1->Elasticity());
			float j = glm::max((-(1.0f + e) * velAlongNormal) / totalInvMass, 0.001f);
			glm::vec3 impulse = j * normal;

			if (c1Dynamic)
				_c1->Velocity(_c1->Velocity() - impulse * invMass1);
			if (s1Dynamic)
				_s1->Velocity(_s1->Velocity() + impulse * invMass2);
		}
	}
}

void PhysicsManager::ResponseSphereToSphere(std::shared_ptr<Rigidbody> _s1, std::shared_ptr<Rigidbody> _s2)
{
	// Check if spheres are dynamic
	bool s1Dynamic = _s1->IsDynamic();
	bool s2Dynamic = _s2->IsDynamic();

	// Find the distance between the sphere's radii
	glm::vec3 delta = _s1->GetCollider()->GetCenter() - _s2->GetCollider()->GetCenter();
	float dist = glm::length(delta);
	if (dist == 0.0f) dist = 0.0001f; // avoid divide-by-zero

	// Calculate normal, and penetration between the two spheres
	glm::vec3 normal = delta / dist;
	float radiusSum = _s1->GetCollider()->GetRadius() + _s2->GetCollider()->GetRadius();
	float penetration = radiusSum - dist;

	// Calculate inverse mass
	float invMass1 = s1Dynamic ? 1.0f / _s1->Mass() : 0.0f;
	float invMass2 = s2Dynamic ? 1.0f / _s2->Mass() : 0.0f;
	float totalInvMass = invMass1 + invMass2;

	// Positional correction variables
	const float slop = 0.001f;
	const float percent = 0.8f; // push out 80% to reduce jitter

	if (penetration >= 0.0f)
	{
		// Calculate the amount of movement needed to move the spheres out of each other
		glm::vec3 correction = normal * (penetration - slop) * percent;

		// Only move the spheres if they're dynamic
		if (s1Dynamic && s2Dynamic)
		{
			_s1->GetTransform()->Move(correction * 0.5f);
			_s2->GetTransform()->Move(-correction * 0.5f);
		}
		else if (s1Dynamic)
		{
			_s1->GetTransform()->Move(correction);
		}
		else if (s2Dynamic)
		{
			_s2->GetTransform()->Move(-correction);
		}	
	}

	// Relative velocity
	glm::vec3 relativeVel = _s1->Velocity() - _s2->Velocity();
	float velAlongNormal = glm::dot(relativeVel, normal);

	if (velAlongNormal < 0)
	{
		// Use the minimum restitution (elasticity)
		float e = glm::min(_s1->Elasticity(), _s2->Elasticity());
		float j = glm::max((-(1.0f + e) * velAlongNormal) / totalInvMass, 0.001f);
		glm::vec3 impulse = j * normal;

		if (s1Dynamic)
			_s1->Velocity(_s1->Velocity() + (impulse * invMass1));
		if (s2Dynamic)
			_s2->Velocity(_s2->Velocity() - (impulse * invMass2));
	}
}
