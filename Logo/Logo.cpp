#include "Logo.hpp"
#include "DxLib.h"



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
Logo::Logo()
{
	m_dxlibLogo = LoadGraph("media\\DxLogo.jpg");
	m_teamLogo = LoadGraph("media\\notmovie.png");

	m_nowLogoNumber = ELOGONOW::dxlib;
	m_logoTransTime = 0;
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
Logo::~Logo()
{
	if (m_teamLogo != -1) DeleteGraph(m_teamLogo);
	if (m_dxlibLogo != -1) DeleteGraph(m_dxlibLogo);
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
		DrawGraph(960 - 120/*���S���W - ���T�C�Y�̔���*/, 540 - 120/*���S���W - �c�T�C�Y�̔���*/, m_dxlibLogo, true);		// dxlib�̃��S��\��
	}
	// ���݂̃��S��ID��1�Ԗڂ�������
	else if (m_nowLogoNumber == ELOGONOW::team)
	{
		DrawGraph(960 - 960/*���S���W - ���T�C�Y�̔���*/, 540 - 540/*���S���W - �c�T�C�Y�̔���*/, m_teamLogo, true);		// team�̃��S��\��
	}
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Logo::Process()
{
	// ���݂̃��S��ID��0�Ԗڂ�������
	if (m_nowLogoNumber == ELOGONOW::dxlib)
	{
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
		// ���S�\�����Ԃ�300���傫��������
		if (m_logoTransTime++ >= 300)
		{
			m_logoTransTime = 0;				// ���S�\�����Ԃ����Z�b�g����
			m_nowLogoNumber = ELOGONOW::dxlib;				// ���S��ID��1�Ԗڂɂ���
		}
	}
}
