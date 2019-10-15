#include "Logo.hpp"



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
Logo::Logo()
{
	mD_dxlibLogo = LoadGraph("media\\logo\\DxLogo.jpg");
	mD_teamLogo = LoadGraph("media\\logo\\notmovie.png");
	mD_skip = LoadGraph("media\\logo\\ASkip.png");

	m_nowLogoNumber = ELOGONOW::dxlib;
	m_logoTransTime = 0;

	m_endFlag = false;
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
Logo::~Logo()
{
	if (mD_skip != -1) DeleteGraph(mD_skip);
	if (mD_teamLogo != -1) DeleteGraph(mD_teamLogo);
	if (mD_dxlibLogo != -1) DeleteGraph(mD_dxlibLogo);
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Logo::Draw()
{
	// ���S�Ђ傶���Ԃ�50�J�E���g�ȉ���������
	if (m_logoTransTime < 50)
	{
		SetDrawBright(m_logoTransTime * 5, m_logoTransTime * 5, m_logoTransTime * 5);		// ���邳�����񂾂񖾂邭����
	}
	// ���S�\�����Ԃ�250�J�E���g�ȏゾ������
	else if (m_logoTransTime > 250)
	{
		SetDrawBright(250 - ((m_logoTransTime - 250) * 5), 250 - ((m_logoTransTime - 250) * 5), 250 - ((m_logoTransTime - 250) * 5));		// ���邳�����񂾂�Â�����
	}


	// ���݂̃��S��ID��0�Ԗڂ�������
	if (m_nowLogoNumber == ELOGONOW::dxlib)
	{
		DrawGraph(960 - 120/*���S���W - ���T�C�Y�̔���*/, 540 - 120/*���S���W - �c�T�C�Y�̔���*/, mD_dxlibLogo, true);		// dxlib�̃��S��\��
	}
	// ���݂̃��S��ID��1�Ԗڂ�������
	else if (m_nowLogoNumber == ELOGONOW::team)
	{
		DrawGraph(960 - 960/*���S���W - ���T�C�Y�̔���*/, 540 - 540/*���S���W - �c�T�C�Y�̔���*/, mD_teamLogo, true);		// team�̃��S��\��
	}

	DrawGraph(1720, 720, mD_skip, true);
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Logo::Process()
{
	// ���݂̃��S��ID��0�Ԗڂ�������
	if (m_nowLogoNumber == ELOGONOW::dxlib)
	{
		if (PadData::GetButton(XINPUT_BUTTON_A, 0) == 1)
		{
			m_logoTransTime = 0;				// ���S�\�����Ԃ����Z�b�g����
			m_nowLogoNumber = ELOGONOW::team;				// ���S��ID��1�Ԗڂɂ���
		}
		// ���S�\�����Ԃ�300���傫��������
		if (m_logoTransTime++ >= 300)
		{
			m_logoTransTime = 0;				// ���S�\�����Ԃ����Z�b�g����
			m_nowLogoNumber = ELOGONOW::team;				// ���S��ID��1�Ԗڂɂ���
		}
	}
	// ���݂̃��S��ID��1�Ԗڂ�������
	else if (m_nowLogoNumber == ELOGONOW::team)
	{
		if (PadData::GetButton(XINPUT_BUTTON_A, 0) == 1)
		{
			BASICPARAM::e_nowScene = ESceneNumber::TITLE;					// ���S��ID��1�Ԗڂɂ���
		}
		// ���S�\�����Ԃ�300���傫��������
		if (m_logoTransTime++ >= 300)
		{
			BASICPARAM::e_nowScene = ESceneNumber::TITLE;					// ���S��ID��1�Ԗڂɂ���
		}
	}
}
