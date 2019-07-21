#include "Game.hpp"



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Game::SpeedProcess()
{
	// ���x�ϊ��J�E���g��60�ȏゾ������
	if (m_speedChangeCount++ > 60) m_isSpeedChange = true;		// ���x�������ς���悤�ɂ���


	// ���݂̑��x���v���C���[�̍ő呬�x - 2�ȉ���������
	if (m_nowSpeed < m_playerMaxSpeed - 2)
	{
		m_nowSpeed++;		// ���x�����Z���Ă���
	}
	// ���݂̑��x���v���C���[�̍ő呬�x - 2���傫��������
	else
	{
		// ���x�������ς���Ƃ���������
		if (m_isSpeedChange)
		{
			m_nowSpeed = m_playerMaxSpeed - 1;		// ���݂̑��x���v���C���[�̍ő呬�x - 1�ɂ���
		}
		// ���x���������ς��Ȃ��Ƃ���������
		else
		{
			m_nowSpeed = m_playerMaxSpeed;		// ���݂̑��x���v���C���[�̍ő呬�x�ɂ���
		}
	}


	// ���݂̑��x��m_playerMaxSpeed - 2�ȉ��������͑��x�������ς���Ƃ���������
	if (m_nowSpeed < m_playerMaxSpeed - 2 || m_isSpeedChange)
	{
		// ���x�ϊ��J�E���g��10�Ŋ���؂��l��������
		if (m_speedChangeCount % 10 == 0)
		{
			// �R���}�ȉ��̐��l��ς���
			{
				std::random_device rnd;     // �񌈒�I�ȗ���������𐶐�
				std::mt19937 mt(rnd());     //  �����Z���k�E�c�C�X�^��32�r�b�g�ŁA�����͏����V�[�h�l
				std::uniform_int_distribution<> rand(0, 9);        // [0, 9] �͈͂̈�l����
				m_lowNowSpeed = rand(mt);
			}
		}
	}
	// ���݂̑��x��68�����傫���đ��x���������ς��Ȃ��Ƃ���������
	else
	{
		m_lowNowSpeed = 0;		// �R���}�ȉ��̒l��0�ɂ���
	}


	// ���x�ϊ��J�E���g��80�ȏゾ������
	if (m_speedChangeCount > 80)
	{
		m_speedChangeCount = 0;		// ���x�ϊ��J�E���g��0�ɂ���
		m_isSpeedChange = false;	// ���x�������ς���t���b�O��|��
	}
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
Game::Game()
{
	mD_backGroundDraw = LoadGraph("media\\background.png");
	mD_playerDraw = LoadGraph("media\\player.png");
	mD_chaserDraw = LoadGraph("media\\chaser.png");
	mD_garbageDraw = LoadGraph("media\\garbage.png");
	mD_underGroundDraw = LoadGraph("media\\underground.png");

	m_playerHP = m_playerMaxHP;

	m_nowSpeed = 0;
	std::random_device rnd;     // �񌈒�I�ȗ���������𐶐�
	std::mt19937 mt(rnd());     //  �����Z���k�E�c�C�X�^��32�r�b�g�ŁA�����͏����V�[�h�l
	std::uniform_int_distribution<> rand(0, 9);        // [0, 9] �͈͂̈�l����
	m_lowNowSpeed = rand(mt);

	m_speedChangeCount = 0;
	m_isSpeedChange = false;

	m_endFlag = false;

	m_scrollX = 0;
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
Game::~Game()
{
	if (mD_backGroundDraw != -1) DeleteGraph(mD_backGroundDraw);
	if (mD_playerDraw != -1) DeleteGraph(mD_playerDraw);
	if (mD_chaserDraw != -1) DeleteGraph(mD_chaserDraw);
	if (mD_garbageDraw != -1) DeleteGraph(mD_garbageDraw);
	if (mD_underGroundDraw != -1) DeleteGraph(mD_underGroundDraw);
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Game::Draw()
{
	// �w�i
	DrawGraph(m_scrollX, 0, mD_backGroundDraw, false);
	DrawGraph(m_scrollX + 1920, 0, mD_backGroundDraw, false);


	// �n��
	DrawGraph(m_scrollX, m_mostMaxY, mD_underGroundDraw, false);
	DrawGraph(m_scrollX + 1920, m_mostMaxY, mD_underGroundDraw, false);


	// �ǂ����������
	DrawGraph(0, m_mostMaxY - 512, mD_chaserDraw, true);


	// ���x
	DrawFormatString(199, 131, GetColor(255, 255, 255), "%d.%d", m_nowSpeed, m_lowNowSpeed);
	

	// �v���C���[
	DrawExtendGraph(284 + ((m_playerMaxHP - m_playerHP) / m_playerHPdiv), (m_mostMaxY - 64) + ((m_playerMaxHP - m_playerHP) / (m_playerHPdiv / 2))
		, 284 + 64 - ((m_playerMaxHP - m_playerHP) / m_playerHPdiv), m_mostMaxY, mD_playerDraw, true);
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Game::Process()
{
	SpeedProcess();


	// ���݂̃X�s�[�h��0����Ȃ�������
	if(m_nowSpeed != 0) m_playerHP--;		// �v���C���[�̗̑͂����炷


	// �X�N���[���l��-1920�ȉ���������
	if (m_scrollX < -1920)
	{
		m_scrollX = 0;			// �X�N���[���l��0�ɖ߂�
	}
	// �X�N���[���l��-1920�����傫��������
	else
	{
		m_scrollX -= m_nowSpeed / 5;		// ���݂̑��x����5�������l���X�N���[���l�����炷
	}


	// �v���C���[�̗̑͂�0�ȉ���������
	if (m_playerHP <= 0)
	{
		BASICPARAM::e_nowScene = ESceneNumber::GAMEOVER;		// GAMEOVER�̃V�[���ֈڍs����
	}
}
