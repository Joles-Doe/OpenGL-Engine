#include "Collider.h"

#include <iostream>

Collider::Collider(SHAPE _type, std::vector<Model::Face>* _faces, std::shared_ptr<Transform> _transform) :
	mCenter(0), mHeight(0), mRadius(0), mWidth(0), mDepth(0)
{
	mType = _type;

	glm::vec3 mBottomLeft(FLT_MAX);
	glm::vec3 mTopRight(-FLT_MAX);
	
	if (!_faces->empty())
	{
		switch (_type)
		{
		case CUBE:
			// Calculate bounds by grabbing the minimum and maximum of all points
			for (int x = 0; x < _faces->size(); x++)
			{
				mBottomLeft = glm::min(mBottomLeft, _faces->at(x).a.mPosition);
				mBottomLeft = glm::min(mBottomLeft, _faces->at(x).b.mPosition);
				mBottomLeft = glm::min(mBottomLeft, _faces->at(x).c.mPosition);

				mTopRight = glm::max(mTopRight, _faces->at(x).a.mPosition);
				mTopRight = glm::max(mTopRight, _faces->at(x).b.mPosition);
				mTopRight = glm::max(mTopRight, _faces->at(x).c.mPosition);
			}

			mCenter = (mTopRight + mBottomLeft) * 0.5f;
			mWidth = mTopRight.x - mBottomLeft.x;
			mHeight = mTopRight.y - mBottomLeft.y;
			mDepth = mTopRight.z - mBottomLeft.z;
			break;
		case SPHERE:
			// Calculate center by averaging the position of all points
			int vertexCount = 0;
			for (int x = 0; x < _faces->size(); x++)
			{
				mCenter += _faces->at(x).a.mPosition;
				mCenter += _faces->at(x).b.mPosition;
				mCenter += _faces->at(x).c.mPosition;
				vertexCount += 3;
			}
			mCenter /= (float)vertexCount;

			// Calculate radius by checking the maxiumum distance of each point
			for (int x = 0; x < _faces->size(); x++)
			{
				mRadius = glm::max(mRadius, glm::distance(mCenter, _faces->at(x).a.mPosition));
				mRadius = glm::max(mRadius, glm::distance(mCenter, _faces->at(x).b.mPosition));
				mRadius = glm::max(mRadius, glm::distance(mCenter, _faces->at(x).c.mPosition));
			}
			break;
		}
	}
	else
	{
		std::cout << "MODEL VECTOR IS EMPTY!!" << std::endl;
	}
	
	mTransform = _transform;
	mCenterOffset = mCenter;
}

void Collider::Update()
{
	mCenter = mTransform->Position() + mCenterOffset;
}

SHAPE Collider::GetShape()
{
	return mType;
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
			collided = CubeToCube(_other);
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

// Check if every axis overlaps
bool Collider::CubeToCube(std::shared_ptr<Collider> _other)
{
	return (glm::abs(mCenter.x - _other->mCenter.x) <= (mWidth / 2 + _other->mWidth / 2)) &&
		(glm::abs(mCenter.y - _other->mCenter.y) <= (mHeight / 2 + _other->mHeight / 2)) &&
		(glm::abs(mCenter.z - _other->mCenter.z) <= (mDepth / 2 + _other->mDepth / 2));
}

// Calculate the cube's closest point to the sphere and check if the distance is less or equal to the sphere radius
bool Collider::CubeToSphere(std::shared_ptr<Collider> _cube, std::shared_ptr<Collider> _sphere)
{
	float closeX = glm::max(_cube->mCenter.x - _cube->mWidth / 2, glm::min(_sphere->mCenter.x, _cube->mCenter.x + _cube->mWidth / 2));
	float closeY = glm::max(_cube->mCenter.y - _cube->mHeight / 2, glm::min(_sphere->mCenter.y, _cube->mCenter.y + _cube->mHeight / 2));
	float closeZ = glm::max(_cube->mCenter.z - _cube->mDepth / 2, glm::min(_sphere->mCenter.z, _cube->mCenter.z + _cube->mDepth / 2));

	float dx = _sphere->mCenter.x - closeX;
	float dy = _sphere->mCenter.y - closeY;
	float dz = _sphere->mCenter.z - closeZ;

	float distanceSquared = (dx * dx) + (dy * dy) + (dz * dz);

	return distanceSquared <= (_sphere->mRadius * _sphere->mRadius);
}

// Check if the distance between both spheres is less or equal to the sum of their radiuses	
bool Collider::SphereToSphere(std::shared_ptr<Collider> _other)
{
	float dx = mCenter.x - _other->mCenter.x;
	float dy = mCenter.y - _other->mCenter.y;
	float dz = mCenter.z - _other->mCenter.z;

	float distanceSquared = (dx * dx) + (dy * dy) + (dz * dz);
	float radiusSum = mRadius + _other->mRadius;

	return distanceSquared <= (mRadius * mRadius);
}