#include "Collider.h"

Collider::Collider(SHAPE _type, std::vector<Model::Face>* _faces)
{
	mType = _type;

	mBottomLeft = glm::vec3(0.0f);
	mTopRight = glm::vec3(0.0f);

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

		mWidth = mTopRight.x - mBottomLeft.x;
		mHeight = mTopRight.y - mBottomLeft.y;
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