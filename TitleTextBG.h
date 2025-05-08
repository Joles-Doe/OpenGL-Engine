#pragma once

#include "HUDObject.h"

class TitleTextBG : public HUDObject
{
public:
	using HUDObject::HUDObject;

	void Start();

	void Update();

	void OnClick();
};

