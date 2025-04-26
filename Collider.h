#pragma once

#include <glm/glm.hpp>
#include <float.h>

#include "SharedStructs&Enums.h"

#include "Model.h"
#include "Transform.h"

/// <summary>
/// Collider - Is comprised of a shape, used as a medium to detect collision
/// <para> 
/// Holds Collider bounds, and holds methods to detect collision between collider shapes.
/// </para>
/// </summary>
class Collider : public std::enable_shared_from_this<Collider>
{
public:
	Collider(SHAPE _type, const std::vector<Model::Face>& _faces, std::shared_ptr<Transform> _transform);

	/// <summary>
	/// Takes a Model's faces and calculates new collider bounds.
	/// </summary>
	/// <param name="_faces"> Model face vector to copy from </param>
	void CalculateBounds(const std::vector<Model::Face>& _faces);

	/// <summary>
	/// Update function called by the Rigidbody once per frame.
	/// </summary>
	void Update();

	/// <summary>
	/// Returns the current collider shape.
	/// </summary>
	/// <returns> SHAPE enum </returns>
	SHAPE GetShape() const noexcept { return mType; }

	/// <summary>
	/// Returns the position of the collider's center.
	/// </summary>
	/// <returns> GLM Vec3 </returns>
	glm::vec3 GetCenter() const noexcept { return mCenter; }

	/// <summary>
	/// Returns the collider width, only applicable with cube shaped Colliders.
	/// </summary>
	/// <returns> float mWidth, returns 0 if Collider is a sphere </returns>
	float GetWidth() const noexcept { return mWidth; }

	/// <summary>
	/// Returns the collider height, only applicable with cube shaped Colliders.
	/// </summary>
	/// <returns> float mHeight, returns 0 if Collider is a sphere </returns>
	float GetHeight() const noexcept { return mHeight; }

	/// <summary>
	/// Returns the collider depth, only applicable with cube shaped Colliders.
	/// </summary>
	/// <returns> float mDepth, returns 0 if Collider is a sphere </returns>
	float GetDepth() const noexcept { return mDepth; }

	/// <summary>
	/// Returns the collider radius, only applicable with sphere shaped Colliders.
	/// </summary>
	/// <returns> float mRadius, returns 0 if Collider is a cube </returns>
	float GetRadius() const noexcept { return mRadius; }

	/// <summary>
	/// Takes a second Collider, checks it's shape, and calls the appropriate collision function.
	/// </summary>
	/// <param name="_other"> Collider to check collision against </param>
	/// <returns> True or False dependent on if the Colliders have collided </returns>
	bool IsColliding(std::shared_ptr<Collider> _other);

	/// <summary>
	/// Returns a value depndent on if the Collider bounds have changed since last frame.
	/// </summary>
	/// <returns> True or False dependent on if Collider bounds change </returns>
	bool BoundsChanged() const noexcept { return mBoundsChanged; }

	/// <summary>
	/// Resets the mBoundsChanged variable.
	/// </summary>
	void BoundsChangedReset() noexcept { mBoundsChanged = false; }
private:
	std::shared_ptr<Transform> mTransform;

	/// <summary>
	/// Cube to Cube collision detection. Uses the AABB algorithm.
	/// </summary>
	/// <param name="_other"> Cube collider to check </param>
	/// <returns> True or False dependent on if the Colliders are colliding </returns>
	bool AABBCubeToCube(std::shared_ptr<Collider> _other);

	/// <summary>
	/// Cube to Cube collision detection. Uses the OBB algorithm.
	/// </summary>
	/// <param name="_other"> Cube collider to check </param>
	/// <returns> True or False dependent on if the Colliders are colliding </returns>
	bool OBBCubeToCube(std::shared_ptr<Collider> _other);
	bool OBBTestAxis(glm::vec3 axis, glm::vec3 t, glm::mat3 rotA, glm::mat3 rotB, glm::vec3 extentsA, glm::vec3 extentsB);
	
	/// <summary>
	/// Cube to Sphere collision detection.
	/// </summary>
	/// <param name="_cube"> Cube collider </param>
	/// <param name="_sphere"> Sphere collider </param>
	/// <returns> True or False dependent on if the Colliders are colliding </returns>
	bool CubeToSphere(std::shared_ptr<Collider> _cube, std::shared_ptr<Collider> _sphere);
	
	/// <summary>
	/// Sphere to Sphere collision detection.
	/// </summary>
	/// <param name="_other"> Sphere coolider to check </param>
	/// <returns> True or False dependent on if the Colliders are colliding </returns>
	bool SphereToSphere(std::shared_ptr<Collider> _other);

	SHAPE mType;

	glm::vec3 mCenter;
	glm::vec3 mCenterOffset;

	float mWidth;
	float mHeight;
	float mDepth;

	float mRadius;

	bool mBoundsChanged;
};

