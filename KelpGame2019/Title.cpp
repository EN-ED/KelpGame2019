#include "Title.hpp"



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Title::SceneOneDraw()
{
	// スタート文字
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_sceneOneStartBlendCount);
	DrawGraph(m_sceneSideDrawX + 960 - 256, 800 - 24, mD_sceneOneStart, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Title::SceneOneProcess()
{
	if (m_isBlendDownSwitch)
	{
		if (m_sceneOneStartBlendCount-- < 155)
		{
			m_isBlendDownSwitch = !m_isBlendDownSwitch;
		}
	}
	else
	{
		if (m_sceneOneStartBlendCount++ > 255)
		{
			m_isBlendDownSwitch = !m_isBlendDownSwitch;
		}
	}

	m_exRate += m_add;
	if (m_exRate < 0.2 || m_exRate > 0.65) m_add = -m_add;


	if (PadData::GetButton(XINPUT_BUTTON_A, 0) == 1 && m_sceneChangeCount >= m_sceneChangeMaxCount)
	{
		SoundProcess::Play(SoundProcess::E_SE::selectDo);
		m_sceneTwoFontBigCount = 1.0f;
		m_sceneChangeCount = 0;
		m_x = 960 + 480;
		m_y = -120;
		m_exRate = 0.45;
		m_add = 1;
		m_angle = 0;
		m_sceneChange = Scene::two;
	}
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Title::SceneTwoDraw()
{
	if (m_cursolArea == TwoCursolArea::start)
	{
		// スタート文字
		DrawRotaGraph((m_sceneSideDrawX + m_sceneTwoDefaultSideDrawX) + 560 - 200, 400 - 24, m_sceneTwoFontBigCount, -0.2, mD_sceneTwoStart, true);


		// 終了文字
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 175);
		DrawRotaGraph((m_sceneSideDrawX + m_sceneTwoDefaultSideDrawX) + 560 - 200, 600 - 24, 1.0, -0.2, mD_sceneTwoEnd, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


		if (m_omakeOneOpen)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 175);
			DrawRotaGraph((m_sceneSideDrawX + m_sceneTwoDefaultSideDrawX) + 560 + 600, 400 - 24, 1.0, -0.2, mD_omakeOne, true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}

		if (m_omakeTwoOpen)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 175);
			DrawRotaGraph((m_sceneSideDrawX + m_sceneTwoDefaultSideDrawX) + 560 + 600, 600 - 24, 1.0, -0.2, mD_omakeTwo, true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
	}
	else if (m_cursolArea == TwoCursolArea::end)
	{
		// スタート文字
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 175);
		DrawRotaGraph((m_sceneSideDrawX + m_sceneTwoDefaultSideDrawX) + 560 - 200, 400 - 24, 1.0, -0.2, mD_sceneTwoStart, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


		// 終了文字
		DrawRotaGraph((m_sceneSideDrawX + m_sceneTwoDefaultSideDrawX) + 560 - 200, 600 - 24, m_sceneTwoFontBigCount, -0.2, mD_sceneTwoEnd, true);


		if (m_omakeOneOpen)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 175);
			DrawRotaGraph((m_sceneSideDrawX + m_sceneTwoDefaultSideDrawX) + 560 + 600, 400 - 24, 1.0, -0.2, mD_omakeOne, true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}

		if (m_omakeTwoOpen)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 175);
			DrawRotaGraph((m_sceneSideDrawX + m_sceneTwoDefaultSideDrawX) + 560 + 600, 600 - 24, 1.0, -0.2, mD_omakeTwo, true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
	}
	else if (m_cursolArea == TwoCursolArea::omakeOne)
	{
		// スタート文字
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 175);
		DrawRotaGraph((m_sceneSideDrawX + m_sceneTwoDefaultSideDrawX) + 560 - 200, 400 - 24, 1.0, -0.2, mD_sceneTwoStart, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


		// 終了文字
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 175);
		DrawRotaGraph((m_sceneSideDrawX + m_sceneTwoDefaultSideDrawX) + 560 - 200, 600 - 24, 1.0, -0.2, mD_sceneTwoEnd, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


		DrawRotaGraph((m_sceneSideDrawX + m_sceneTwoDefaultSideDrawX) + 560 + 600, 400 - 24, m_sceneTwoFontBigCount, -0.2, mD_omakeOne, true);

		if (m_omakeTwoOpen)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 175);
			DrawRotaGraph((m_sceneSideDrawX + m_sceneTwoDefaultSideDrawX) + 560 + 600, 600 - 24, 1.0, -0.2, mD_omakeTwo, true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
	}
	else if (m_cursolArea == TwoCursolArea::omakeTwo)
	{
		// スタート文字
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 175);
		DrawRotaGraph((m_sceneSideDrawX + m_sceneTwoDefaultSideDrawX) + 560 - 200, 400 - 24, 1.0, -0.2, mD_sceneTwoStart, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


		// 終了文字
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 175);
		DrawRotaGraph((m_sceneSideDrawX + m_sceneTwoDefaultSideDrawX) + 560 - 200, 600 - 24, 1.0, -0.2, mD_sceneTwoEnd, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		if (m_omakeOneOpen)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 175);
			DrawRotaGraph((m_sceneSideDrawX + m_sceneTwoDefaultSideDrawX) + 560 + 600, 400 - 24, 1.0, -0.2, mD_omakeOne, true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}

		DrawRotaGraph((m_sceneSideDrawX + m_sceneTwoDefaultSideDrawX) + 560 + 600, 600 - 24, m_sceneTwoFontBigCount, -0.2, mD_omakeTwo, true);
	}
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Title::SceneTwoProcess()
{
	if (m_isFontBigDownSwitch)
	{
		if ((m_sceneTwoFontBigCount -= 0.003f) < 1.0f)
		{
			m_isFontBigDownSwitch = !m_isFontBigDownSwitch;
		}
	}
	else
	{
		if ((m_sceneTwoFontBigCount += 0.005f) > 1.15f)
		{
			m_isFontBigDownSwitch = !m_isFontBigDownSwitch;
		}
	}


	if (m_sceneChangeCount >= m_sceneChangeMaxCount)
	{
		if (m_selectCommandLeft)
		{
			if (PadData::GetStickCheck(PadStick::LEFT_STICK_Y, 0, false) == 1)
			{
				m_omakeOneLeft = true;
				m_omakeOneAbleFrame = 0;
				m_omakeOneCommandNumber = 0;
				m_omakeTwoLeft = true;
				m_omakeTwoAbleFrame = 0;
				m_omakeTwoCommandNumber = 0;

				m_cursolArea = TwoCursolArea::start;
				m_sceneTwoFontBigCount = 1.0f;
			}
			else if (PadData::GetStickCheck(PadStick::LEFT_STICK_Y, 0, true) == 1)
			{
				m_omakeOneLeft = true;
				m_omakeOneAbleFrame = 0;
				m_omakeOneCommandNumber = 0;
				m_omakeTwoLeft = true;
				m_omakeTwoAbleFrame = 0;
				m_omakeTwoCommandNumber = 0;

				m_cursolArea = TwoCursolArea::end;
				m_sceneTwoFontBigCount = 1.0f;
			}

			if (PadData::GetStickCheck(PadStick::LEFT_STICK_X, 0, false) == 1)
			{
				m_omakeOneLeft = true;
				m_omakeOneAbleFrame = 0;
				m_omakeOneCommandNumber = 0;
				m_omakeTwoLeft = true;
				m_omakeTwoAbleFrame = 0;
				m_omakeTwoCommandNumber = 0;

				if (m_cursolArea == TwoCursolArea::start)
				{
					if (m_omakeOneOpen)
					{
						m_cursolArea = TwoCursolArea::omakeOne;
					}
					else
					{
						if (m_omakeTwoOpen)
						{
							m_cursolArea = TwoCursolArea::omakeTwo;
						}
					}
				}
				else if (m_cursolArea == TwoCursolArea::end)
				{
					if (m_omakeTwoOpen)
					{
						m_cursolArea = TwoCursolArea::omakeTwo;
					}
					else
					{
						if (m_omakeOneOpen)
						{
							m_cursolArea = TwoCursolArea::omakeOne;
						}
					}
				}

				m_sceneTwoFontBigCount = 1.0f;
				m_selectCommandLeft = false;
			}
		}
		else
		{
			if (PadData::GetStickCheck(PadStick::LEFT_STICK_Y, 0, true) == 1 && m_omakeTwoOpen)
			{
				m_omakeOneLeft = true;
				m_omakeOneAbleFrame = 0;
				m_omakeOneCommandNumber = 0;
				m_omakeTwoLeft = true;
				m_omakeTwoAbleFrame = 0;
				m_omakeTwoCommandNumber = 0;

				m_cursolArea = TwoCursolArea::omakeTwo;
				m_sceneTwoFontBigCount = 1.0f;
			}

			if (PadData::GetStickCheck(PadStick::LEFT_STICK_Y, 0, false) == 1 && m_omakeOneOpen)
			{
				m_omakeOneLeft = true;
				m_omakeOneAbleFrame = 0;
				m_omakeOneCommandNumber = 0;
				m_omakeTwoLeft = true;
				m_omakeTwoAbleFrame = 0;
				m_omakeTwoCommandNumber = 0;

				m_cursolArea = TwoCursolArea::omakeOne;
				m_sceneTwoFontBigCount = 1.0f;
			}

			if (PadData::GetStickCheck(PadStick::LEFT_STICK_X, 0, true) == 1)
			{
				m_omakeOneLeft = true;
				m_omakeOneAbleFrame = 0;
				m_omakeOneCommandNumber = 0;
				m_omakeTwoLeft = true;
				m_omakeTwoAbleFrame = 0;
				m_omakeTwoCommandNumber = 0;

				if (m_cursolArea == TwoCursolArea::omakeOne)
				{
					m_cursolArea = TwoCursolArea::start;
				}
				else if (m_cursolArea == TwoCursolArea::omakeTwo)
				{
					m_cursolArea = TwoCursolArea::end;
				}

				m_sceneTwoFontBigCount = 1.0f;
				m_selectCommandLeft = true;
			}
		}
	}


	if (PadData::GetButton(XINPUT_BUTTON_A, 0) == 1 && m_sceneChangeCount >= m_sceneChangeMaxCount)
	{
		m_omakeOneLeft = true;
		m_omakeOneAbleFrame = 0;
		m_omakeOneCommandNumber = 0;
		m_omakeTwoLeft = true;
		m_omakeTwoAbleFrame = 0;
		m_omakeTwoCommandNumber = 0;

		SoundProcess::Play(SoundProcess::E_SE::selectDo);
		if (m_cursolArea == TwoCursolArea::start)
		{
			BASICPARAM::e_nowScene = ESceneNumber::TUTORIAL;
		}
		else if (m_cursolArea == TwoCursolArea::end)
		{
			m_endFlag = true;
		}
		else if (m_cursolArea == TwoCursolArea::omakeOne)
		{
			BASICPARAM::e_nowScene = ESceneNumber::OMAKEONE;
		}
		else if (m_cursolArea == TwoCursolArea::omakeTwo)
		{
			BASICPARAM::e_nowScene = ESceneNumber::OMAKETWO;
		}
	}


	if (PadData::GetButton(XINPUT_BUTTON_B, 0) == 1 && m_sceneChangeCount >= m_sceneChangeMaxCount)
	{
		m_omakeOneLeft = true;
		m_omakeOneAbleFrame = 0;
		m_omakeOneCommandNumber = 0;
		m_omakeTwoLeft = true;
		m_omakeTwoAbleFrame = 0;
		m_omakeTwoCommandNumber = 0;

		SoundProcess::Play(SoundProcess::E_SE::selectCancel);
		m_sceneOneStartBlendCount = 155;
		m_sceneChangeCount = 0;
		m_x = 960;
		m_y = -120;
		m_exRate = 0.65;
		m_add = -0.01;
		m_angle = 0.0;
		m_sceneChange = Scene::one;
	}


	if (PadData::GetButton(XINPUT_BUTTON_LEFT_SHOULDER, 0) == 1 && m_sceneChangeCount >= m_sceneChangeMaxCount && !m_omakeOneLeft)
	{
		m_omakeOneLeft = true;
		m_omakeOneAbleFrame = 0;

		m_omakeTwoLeft = true;
		m_omakeTwoAbleFrame = 0;
		m_omakeTwoCommandNumber = 0;

		if (++m_omakeOneCommandNumber >= 6)
		{
			m_omakeOneOpen = true;
		}
	}

	if (PadData::GetButton(XINPUT_BUTTON_RIGHT_SHOULDER, 0) == 1 && m_sceneChangeCount >= m_sceneChangeMaxCount && m_omakeOneLeft)
	{
		m_omakeOneLeft = false;
		m_omakeOneAbleFrame = 0;
		m_omakeOneCommandNumber++;

		m_omakeTwoLeft = true;
		m_omakeTwoAbleFrame = 0;
		m_omakeTwoCommandNumber = 0;
	}

	if (++m_omakeOneAbleFrame > 60)
	{
		m_omakeOneLeft = true;
		m_omakeOneAbleFrame = 0;
		m_omakeOneCommandNumber = 0;
	}


	if (PadData::GetTrigger(PadStick::LEFT_TRIGGER, 0) == 255 && m_sceneChangeCount >= m_sceneChangeMaxCount && !m_omakeTwoLeft)
	{
		m_omakeTwoLeft = true;
		m_omakeTwoAbleFrame = 0;

		m_omakeOneLeft = true;
		m_omakeOneAbleFrame = 0;
		m_omakeOneCommandNumber = 0;

		if (++m_omakeTwoCommandNumber >= 6)
		{
			m_omakeTwoOpen = true;
		}
	}

	if (PadData::GetTrigger(PadStick::RIGHT_TRIGGER, 0) == 255 && m_sceneChangeCount >= m_sceneChangeMaxCount && m_omakeTwoLeft)
	{
		m_omakeTwoLeft = false;
		m_omakeTwoAbleFrame = 0;
		m_omakeTwoCommandNumber++;

		m_omakeOneLeft = true;
		m_omakeOneAbleFrame = 0;
		m_omakeOneCommandNumber = 0;
	}

	if (++m_omakeTwoAbleFrame > 60)
	{
		m_omakeTwoLeft = true;
		m_omakeTwoAbleFrame = 0;
		m_omakeTwoCommandNumber = 0;
	}

	
	if (!m_omakeOneOpen && !m_omakeTwoOpen)
	{
		if (m_omakeOneCommandNumber <= 3 && m_omakeTwoCommandNumber <= 3)
		{
			if (m_logoBlendValue < 255)
			{
				m_logoBlendValue += 17;
			}
		}
		else if (m_omakeOneCommandNumber == 4 || m_omakeTwoCommandNumber == 4)
		{
			if (m_logoBlendValue > 170)
			{
				m_logoBlendValue -= 5;
			}
		}
		else if (m_omakeOneCommandNumber == 5 || m_omakeTwoCommandNumber == 5)
		{
			if (m_logoBlendValue > 85)
			{
				m_logoBlendValue -= 5;
			}
		}
	}
	else
	{
		if (m_logoBlendValue > 0)
		{
			m_logoBlendValue -= 5;
		}
	}


	DrawGraph(1720, 720 + 24, mD_back, true);

	m_angle += m_add;
	if (m_angle < -12 || m_angle > 12) m_add = -m_add;
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
Title::Title()
{
	mD_select = LoadGraph("media\\title\\Aselect.png");
	mD_back = LoadGraph("media\\title\\BBack.png");

	mD_sceneOneStart = LoadGraph("media\\title\\start.png");

	m_sceneOneStartBlendCount = 50;
	m_isBlendDownSwitch = false;

	mD_sceneTwoStart = LoadGraph("media\\title\\gamestart.png");
	mD_sceneTwoEnd = LoadGraph("media\\title\\exit.png");

	m_cursolArea = TwoCursolArea::start;
	m_sceneTwoFontBigCount = 1.0f;
	m_isFontBigDownSwitch = false;

	m_backGroundColor = 10;

	m_sceneChange = Scene::one;

	m_sceneChangeCount = m_sceneChangeMaxCount;

	m_sceneSideDrawX = 0;

	m_endFlag = false;

	mD_TitleLogo = LoadGraph("media\\title\\石鹸君ロゴ.png");

	m_x = 960;
	m_y = -120;
	m_exRate = 0.65;
	m_add = -0.01;
	m_angle = 0;

	m_omakeOneCommandNumber = 0;
	m_omakeOneAbleFrame = 0;
	m_omakeOneLeft = true;
	m_omakeOneOpen = false;
	mD_omakeOne = LoadGraph("media\\title\\omakeOne.jpg");

	m_omakeTwoCommandNumber = 0;
	m_omakeTwoAbleFrame = 0;
	m_omakeTwoLeft = true;
	m_omakeTwoOpen = false;
	mD_omakeTwo = LoadGraph("media\\title\\omakeTwo.jpg");

	m_logoBlendValue = 255;
	m_selectCommandLeft = true;

	mD_backGround = LoadGraph("media\\title\\titlebackground.png");
	m_backGroundAngle = 0;
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
Title::~Title()
{
	if (mD_backGround != -1) DeleteGraph(mD_backGround);
	if (mD_omakeTwo != -1) DeleteGraph(mD_omakeTwo);
	if (mD_omakeOne != -1) DeleteGraph(mD_omakeOne);
	if (mD_TitleLogo != -1) DeleteGraph(mD_TitleLogo);
	if (mD_sceneTwoEnd != -1) DeleteGraph(mD_sceneTwoEnd);
	if (mD_sceneTwoStart != -1) DeleteGraph(mD_sceneTwoStart);
	if (mD_sceneOneStart != -1) DeleteGraph(mD_sceneOneStart);
	if (mD_back != -1) DeleteGraph(mD_back);
	if (mD_select != -1) DeleteGraph(mD_select);
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Title::Draw()
{
	// 背景
	DrawRotaGraph(1920 / 2, 1080 / 2, 1.0, 3.14 / 360 * ++m_backGroundAngle, mD_backGround, false);


	if (m_sceneChange == Scene::one)
	{
		DrawRotaGraph(m_x, m_y + 516, m_exRate, 3.14 / 180 * m_angle, mD_TitleLogo, true);

		SceneOneDraw();
	}
	else if (m_sceneChange == Scene::two)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_logoBlendValue);
		DrawRotaGraph(m_x, m_y + 516, m_exRate, 3.14 / 180 * m_angle, mD_TitleLogo, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

		SceneTwoDraw();
	}

	DrawGraph(1720, 720, mD_select, true);
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Title::Process()
{
	if (m_sceneChange == Scene::one)
	{
		SceneOneProcess();
		if (m_sceneChangeCount++ < m_sceneChangeMaxCount)
		{
			m_backGroundColor--;
			m_sceneSideDrawX += 1920 / m_sceneChangeMaxCount;
		}
	}
	else if (m_sceneChange == Scene::two)
	{
		SceneTwoProcess();
		if (m_sceneChangeCount++ < m_sceneChangeMaxCount)
		{
			m_backGroundColor++;
			m_sceneSideDrawX -= 1920 / m_sceneChangeMaxCount;
		}
	}
}
