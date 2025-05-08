#pragma once

#include "HUDObject.h"

class TitleText : public HUDObject
{
public:
	using HUDObject::HUDObject;

	void OnClick();
};