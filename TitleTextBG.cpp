#include "TitleTextBG.h"

void TitleTextBG::Start()
{
	mShaderStore->AddUniform("uMousePos");
}

void TitleTextBG::Update()
{
	float mouseNDC_X = ((float)mEventManager->GetMousePos().x / 960);
	float mouseNDC_Y = (float)mEventManager->GetMousePos().y / 540;

	std::cout << mouseNDC_X << " " << mouseNDC_Y << std::endl;

	mShaderStore->ChangeUniform("uMousePos", glm::vec2(mouseNDC_X, mouseNDC_Y));
}

void TitleTextBG::OnClick()
{
	mKILL = true;
}