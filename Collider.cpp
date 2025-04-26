#include "Collider.h"

#include <iostream>

Collider::Collider(SHAPE _type, const std::vector<Model::Face>& _faces, std::shared_ptr<Transform> _transform) :
	mCenter(0), mHeight(0), mRadius(0), mWidth(0), mDepth(0), mBoundsChanged(true)
{
	mType = _type;
	mTransform = _transform;
	CalculateBounds(_faces);
}

void Collider::CalculateBounds(const std::vector<Model::Face>& _faces)
{
	glm::vec3 mBottomLeft(FLT_MAX);
	glm::vec3 mTopRight(-FLT_MAX);

	if (!_faces.empty())
	{
		switch (mType)
		{
		case CUBE:
			// Calculate bounds by grabbing the minimum and maximum of all points
			for (int x = 0; x < _faces.size(); x++)
			{
				glm::vec3 a = _faces.at(x).a.mPosition * mTransform->Scale();
				glm::vec3 b = _faces.at(x).b.mPosition * mTransform->Scale();
				glm::vec3 c = _faces.at(x).c.mPosition * mTransform->Scale();

				mBottomLeft = glm::min(mBottomLeft, a);
				mBottomLeft = glm::min(mBottomLeft, b);
				mBottomLeft = glm::min(mBottomLeft, c);

				mTopRight = glm::max(mTopRight, a);
				mTopRight = glm::max(mTopRight, b);
				mTopRight = glm::max(mTopRight, c);
			}

			mCenter = (mTopRight + mBottomLeft) * 0.5f;
			mWidth = mTopRight.x - mBottomLeft.x;
			mHeight = mTopRight.y - mBottomLeft.y;
			mDepth = mTopRight.z - mBottomLeft.z;
			break;
		case SPHERE:
			// Calculate center by averaging the position of all points
			int vertexCount = 0;
			for (int x = 0; x < _faces.size(); x++)
			{
				glm::vec3 a = _faces.at(x).a.mPosition * mTransform->Scale();
				glm::vec3 b = _faces.at(x).b.mPosition * mTransform->Scale();
				glm::vec3 c = _faces.at(x).c.mPosition * mTransform->Scale();

				mCenter += a;
				mCenter += b;
				mCenter += c;
				vertexCount += 3;
			}
			mCenter /= (float)vertexCount;

			// Calculate radius by checking the maxiumum distance of each point
			for (int x = 0; x < _faces.size(); x++)
			{
				glm::vec3 a = _faces.at(x).a.mPosition * mTransform->Scale();
				glm::vec3 b = _faces.at(x).b.mPosition * mTransform->Scale();
				glm::vec3 c = _faces.at(x).c.mPosition * mTransform->Scale();

				mRadius = glm::max(mRadius, glm::distance(mCenter, a));
				mRadius = glm::max(mRadius, glm::distance(mCenter, b));
				mRadius = glm::max(mRadius, glm::distance(mCenter, c));
			}
			break;
		}
	}
	mCenterOffset = mCenter;
	mBoundsChanged = true;
}

void Collider::Update()
{
	mCenter = mTransform->Position() + mCenterOffset;

	/*std::cout << "==================" << std::endl;
	std::cout << "POSITION: " << mTransform->Position().x << ", " << mTransform->Position().y << ", " << mTransform->Position().z << std::endl;
	std::cout << "COLLIDER CENTER: " << mCenter.x << ", " << mCenter.y << ", " << mCenter.z << std::endl;*/
}

bool Collider::IsColliding(std::shared_ptr<Collider> _other)
{
	bool collided = false;
	switch (mType)
	{
	case CUBE:
		switch (_other->GetShape())
		{
		case CUBE:
			collided = OBBCubeToCube(_other);
			break;
		case SPHERE:
			collided = CubeToSphere(shared_from_this(), _other);
			break;
		}
		break;
	case SPHERE:
		switch (_other->GetShape())
		{
		case CUBE:
			collided = CubeToSphere(_other, shared_from_this());
			break;
		case SPHERE:
			collided = SphereToSphere(_other);
			break;
		}
		break;
	}
	return collided;
}

bool Collider::AABBCubeToCube(std::shared_ptr<Collider> _other)
{
	// Check if every axis overlaps
	return (glm::abs(mCenter.x - _other->mCenter.x) <= (mWidth / 2 + _other->mWidth / 2)) &&
		(glm::abs(mCenter.y - _other->mCenter.y) <= (mHeight / 2 + _other->mHeight / 2)) &&
		(glm::abs(mCenter.z - _other->mCenter.z) <= (mDepth / 2 + _other->mDepth / 2));
}

bool Collider::OBBCubeToCube(std::shared_ptr<Collider> _other)
{
	glm::mat4 modelMatrix(1.0f);
	modelMatrix = glm::rotate(modelMatrix, glm::radians(mTransform->Rotation().x), glm::vec3(1, 0, 0));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(mTransform->Rotation().y), glm::vec3(0, 1, 0));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(mTransform->Rotation().z), glm::vec3(0, 0, 1));

	glm::mat3 rotA = glm::mat3(modelMatrix);
	rotA[0] *= mTransform->Scale().x;
	rotA[1] *= mTransform->Scale().y;
	rotA[2] *= mTransform->Scale().z;

	modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::rotate(modelMatrix, glm::radians(_other->mTransform->Rotation().x), glm::vec3(1, 0, 0));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(_other->mTransform->Rotation().y), glm::vec3(0, 1, 0));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(_other->mTransform->Rotation().z), glm::vec3(0, 0, 1));

	glm::mat3 rotB = glm::mat3(modelMatrix);
	rotB[0] *= _other->mTransform->Scale().x;
	rotB[1] *= _other->mTransform->Scale().y;
	rotB[2] *= _other->mTransform->Scale().z;

	// Get half-extents
	glm::vec3 extentsA = glm::vec3(mWidth, mHeight, mDepth) * 0.5f;
	glm::vec3 extentsB = glm::vec3(_other->mWidth, _other->mHeight, _other->mDepth) * 0.5f;

	// Axes of A and B
	glm::vec3 axesA[3] = { rotA[0], rotA[1], rotA[2] };
	glm::vec3 axesB[3] = { rotB[0], rotB[1], rotB[2] };

	// Vector between centers
	glm::vec3 t = _other->mCenter - mCenter;

	// Loop through 15 axes
	for (int i = 0; i < 3; ++i)
	{
		if (!OBBTestAxis(axesA[i], t, rotA, rotB, extentsA, extentsB))
		{
			return false;
		}
	}

	for (int i = 0; i < 3; ++i)
	{
		if (!OBBTestAxis(axesB[i], t, rotA, rotB, extentsA, extentsB))
		{
			return false;
		}
	}

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			glm::vec3 axis = glm::cross(axesA[i], axesB[j]);
			if (glm::dot(axis, axis) < 1e-6f) continue; // skip degenerate axis

			if (!OBBTestAxis(glm::normalize(axis), t, rotA, rotB, extentsA, extentsB))
			{
				return false;
			}
		}
	}

	// No separating axis found — they are colliding
	return true;
}

bool Collider::OBBTestAxis(glm::vec3 axis, glm::vec3 t, glm::mat3 rotA, glm::mat3 rotB, glm::vec3 extentsA, glm::vec3 extentsB)
{
	axis = glm::normalize(axis);

	float projA =
		glm::abs(glm::dot(axis, rotA[0])) * extentsA.x +
		glm::abs(glm::dot(axis, rotA[1])) * extentsA.y +
		glm::abs(glm::dot(axis, rotA[2])) * extentsA.z;

	float projB =
		glm::abs(glm::dot(axis, rotB[0])) * extentsB.x +
		glm::abs(glm::dot(axis, rotB[1])) * extentsB.y +
		glm::abs(glm::dot(axis, rotB[2])) * extentsB.z;

	float dist = glm::abs(glm::dot(t, axis));

	return dist <= projA + projB;
}

bool Collider::CubeToSphere(std::shared_ptr<Collider> _cube, std::shared_ptr<Collider> _sphere)
{
	// Calculate the cube's closest point to the sphere and check if the distance is less or equal to the sphere radius
	float closeX = glm::max(_cube->mCenter.x - _cube->mWidth / 2, glm::min(_sphere->mCenter.x, _cube->mCenter.x + _cube->mWidth / 2));
	float closeY = glm::max(_cube->mCenter.y - _cube->mHeight / 2, glm::min(_sphere->mCenter.y, _cube->mCenter.y + _cube->mHeight / 2));
	float closeZ = glm::max(_cube->mCenter.z - _cube->mDepth / 2, glm::min(_sphere->mCenter.z, _cube->mCenter.z + _cube->mDepth / 2));

	float dx = _sphere->mCenter.x - closeX;
	float dy = _sphere->mCenter.y - closeY;
	float dz = _sphere->mCenter.z - closeZ;

	float distanceSquared = (dx * dx) + (dy * dy) + (dz * dz);

	return distanceSquared <= (_sphere->mRadius * _sphere->mRadius);
}

bool Collider::SphereToSphere(std::shared_ptr<Collider> _other)
{
	// Check if the distance between both spheres is less or equal to the sum of their radii
	float dx = mCenter.x - _other->mCenter.x;
	float dy = mCenter.y - _other->mCenter.y;
	float dz = mCenter.z - _other->mCenter.z;

	float distanceSquared = (dx * dx) + (dy * dy) + (dz * dz);
	float radiusSum = mRadius + _other->mRadius;

	return distanceSquared <= (radiusSum * radiusSum);
}