#include "Logo.hpp"



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
Logo::Logo()
{
	mD_movieDraw = LoadGraph("media\\movieLogo.mp4");
	mD_dxlibLogo = LoadGraph("media\\DxLogo.jpg");

	m_nowLogoNumber = 0;
	m_movieZoom = 0;
	m_logoTransTime = 0;

	m_endFlag = false;
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
Logo::~Logo()
{
	PauseMovieToGraph(mD_movieDraw);
	if (mD_movieDraw != -1) DeleteGraph(mD_movieDraw);
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
	if (m_nowLogoNumber == 0)
	{
		DrawGraph(960 - 120, 540 - 120, mD_dxlibLogo, false);		// dxlib�̃��S��\��
	}
	// ���݂̃��S��ID��1�Ԗڂ�������
	else if (m_nowLogoNumber == 1)
	{
		DrawExtendGraph(960 - 480 - m_movieZoom * 2, 540 - 220 - m_movieZoom, 960 + 480 + m_movieZoom * 2, 540 + 220 + m_movieZoom, mD_movieDraw, false);		// �����\��
	}
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Logo::Process()
{
	// ���݂̃��S��ID��0�Ԗڂ�������
	if (m_nowLogoNumber == 0)
	{
		// Z�L�[�������ꂽ��
		if (KeyData::Get(KEY_INPUT_Z) == 1)
		{
			// ���S�\�����Ԃ�150�J�E���g�ȉ���������
			if (m_logoTransTime < 150)
			{
				m_logoTransTime = 150;				// ���S�\�����Ԃ�150�ɂ���
				SetDrawBright(250, 250, 250);		// ���邳�����S�\���̍ő�ɂ���
			}
			// ���S�\�����Ԃ�151�J�E���g�ȏゾ������
			else
			{
				m_logoTransTime = 300;				// ���S�\�����Ԃ�300�ɂ���
			}
		}


		// ���S�\�����Ԃ�300���傫��������
		if (m_logoTransTime++ >= 300)
		{
			m_logoTransTime = 0;				// ���S�\�����Ԃ����Z�b�g����
			m_nowLogoNumber = 1;				// ���S��ID��1�Ԗڂɂ���
			PlayMovieToGraph(mD_movieDraw);		// ������Đ�����
		}
	}
	// ���݂̃��S��ID��1�Ԗڂ�������
	else if (m_nowLogoNumber == 1)
	{
		// Z�L�[�������ꂽ��
		if (KeyData::Get(KEY_INPUT_Z) == 1)
		{
			// ���S�\�����Ԃ�150�J�E���g�ȉ���������
			if (m_logoTransTime < 150)
			{
				m_logoTransTime = 150;				// ���S�\�����Ԃ�150�ɂ���
				m_movieZoom = 450;					// ����̃Y�[���l��450�ɂ���
				SetDrawBright(250, 250, 250);		// ���邳�����S�\���̍ő�ɂ���
			}
			// ���S�\�����Ԃ�151�J�E���g�ȏゾ������
			else
			{
				BASICPARAM::e_nowScene = ESceneNumber::TITLE;		// TITLE�̃V�[���ֈڍs����
			}
		}

		// ���S�\�����Ԃ�300���傫��������
		if (m_logoTransTime++ >= 300)
		{
			BASICPARAM::e_nowScene = ESceneNumber::TITLE;		// TITLE�̃V�[���ֈڍs����
		}
		else
		{
			m_movieZoom += 3;		// ����̃Y�[���l��3�����Z����
		}
	}
}
