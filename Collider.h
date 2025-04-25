#pragma once

#include <glm/glm.hpp>
#include <float.h>

#include "SharedStructs&Enums.h"

#include "Model.h"
#include "Transform.h"

class Collider : public std::enable_shared_from_this<Collider>
{
public:
	Collider(SHAPE _type, const std::vector<Model::Face>& _faces, std::shared_ptr<Transform> _transform);
	void CalculateBounds(const std::vector<Model::Face>& _faces);

	void Update();

	SHAPE GetShape();

	glm::vec3 GetCenter();
	float GetWidth();
	float GetHeight();
	float GetDepth();
	float GetRadius();

	bool IsColliding(std::shared_ptr<Collider> _other);

	bool BoundsChanged();
	void BoundsChangedReset();
private:
	std::shared_ptr<Transform> mTransform;
	std::shared_ptr<Transform> GetTransform();

	bool AABBCubeToCube(std::shared_ptr<Collider> _other);

	bool OBBCubeToCube(std::shared_ptr<Collider> _other);
	bool OBBTestAxis(glm::vec3 axis, glm::vec3 t, glm::mat3 rotA, glm::mat3 rotB, glm::vec3 extentsA, glm::vec3 extentsB);
	
	bool CubeToSphere(std::shared_ptr<Collider> _cube, std::shared_ptr<Collider> _sphere);
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

