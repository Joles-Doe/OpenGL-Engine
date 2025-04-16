#include "Ball.h"

#include <iostream>

void Ball::OnCollisionEnter(std::shared_ptr<Rigidbody> _other)
{
	if (mTransform->Position().y < -8.7f)
	{
		mKILL = true;
	}
}
