#include "BackGround.hpp"
#include "DxLib.h"
#include "InputKey.hpp"
#include "BlurScreen.hpp"



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
BackGround::BackGround()
{
	mD_backGround = LoadGraph("media\\background.png");

	BlurScreen::Init(200, -6, -2, 0, 0);
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
BackGround::~BackGround()
{
	if (mD_backGround != -1) DeleteGraph(mD_backGround);

	BlurScreen::Release();
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void BackGround::Draw()
{
	if (KeyData::Get(KEY_INPUT_Z) > 1)
	{
		BlurScreen::PreRenderBlurScreen();
		DrawGraph(0, 0, mD_backGround, false);
		BlurScreen::PostRenderBlurScreen();
	}
	else if (KeyData::Get(KEY_INPUT_Z) == 1)
	{
		BlurScreen::ReplayInit();
		BlurScreen::PreRenderBlurScreen();
		DrawGraph(0, 0, mD_backGround, false);
		BlurScreen::PostRenderBlurScreen();
	}
	else
	{
		DrawGraph(0, 0, mD_backGround, false);
	}


	if (KeyData::Get(KEY_INPUT_G) == 1)
	{
		BlurScreen::Release();
		BlurScreen::Init(200, -6, -2, 0, 0);
	}
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void BackGround::Process()
{
}
