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
	else if (m_nowSpeed > m_playerMaxSpeed + 1)
	{
		m_nowSpeed--;
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
	if ((m_nowSpeed < m_playerMaxSpeed - 2 || m_nowSpeed > m_playerMaxSpeed + 1) || m_isSpeedChange)
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


	// X�L�[�������ꂽ��
	if (KeyData::Get(KEY_INPUT_X) == 1)
	{
		m_nowSpeed = m_playerMaxSpeed + m_maxMomentSpeed;		// �u�ԓI�ɃX�s�[�h�𑬂�����
		m_playerX = m_playerMaxX;							// �v���C���[�̈ʒu���E�ɂ��炷
	}


	// �v���C���[�̍��W�ʒu��0�ȏゾ������
	if (m_playerX > 0)
	{
		m_playerX--;		// �߂��Ă���
	}
	else if (m_playerX < 0)
	{
		m_playerX++;
	}


	// �f�o�b�O
	// C�L�[�������ꂽ��Ԃ������Ƃ���z�肷��
	if (KeyData::Get(KEY_INPUT_C) == 1)
	{
		if (m_nowSpeed - m_haleDownMaxSpeed < 0)
		{
			m_nowSpeed = 0;
		}
		else
		{
			m_nowSpeed -= m_haleDownMaxSpeed;
		}
		m_playerX = -m_playerHitHaleX;
	}
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Game::PlayerJump()
{
	m_preY = m_playerY;


	// �n�ʂɐG��ĂȂ�(�����Ă�
	if (!m_isGroundFlag)
	{
		m_gravityPower += 2;
		m_playerY += m_gravityPower;
		m_playerX += m_jumpMoveX;

		// �n�ʂɖ��܂�����
		if (m_playerY > m_mostMaxY)
		{
			m_playerY = m_mostMaxY;
			m_isFallNow = false;
			m_gravityPower = 0;
			m_jumpPower = m_jumpMinPower;
			m_isGroundFlag = true;
			m_isJumpFlag = false;
		}
	}

	// �n�ʂɂ��ăW�����v�{�^����������
	if (m_isGroundFlag && KeyData::Get(KEY_INPUT_SPACE) == 1)
	{
		m_isJumpFlag = true;
		m_isLongJump = true;
		m_isGroundFlag = false;
		m_isFallNow = false;
		m_jumpPower = m_jumpMinPower;
	}

	// �W�����v���삵�Ă�����
	if (m_isJumpFlag)
	{
		if (KeyData::Get(KEY_INPUT_SPACE) == -1)
		{
			m_isLongJump = false;
		}
		// ���������Ă�����
		if (m_isLongJump && KeyData::Get(KEY_INPUT_SPACE) > 1 && m_jumpPower <= m_jumpMaxPower)
		{
			m_jumpPower += 5;
		}
		m_playerY -= m_jumpPower;
	}

	// ���O��Y���W������Y���W���ゾ������
	if (m_preY < m_playerY)
	{
		m_isFallNow = true;
	}
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
Game::Game()
{
	mD_backGroundDraw = LoadGraph("media\\background.png");
	mD_playerDraw = LoadGraph("media\\player_size_diffe\\player�~2.png");
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
	m_playerY = m_mostMaxY;
	m_preY = m_playerY;
	m_playerX = 0;
	
	m_isGroundFlag = true;
	m_isJumpFlag = false;
	m_isLongJump = false;
	m_jumpPower = m_jumpMinPower;
	m_gravityPower = 0;
	m_isFallNow = false;
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
	
	int size = 128;
	// �v���C���[
	DrawExtendGraph(284 + ((m_playerMaxHP - m_playerHP) / m_playerHPdiv) + m_playerX, (m_playerY - size) + ((m_playerMaxHP - m_playerHP) / (m_playerHPdiv / 2))
		, 284 + size - ((m_playerMaxHP - m_playerHP) / m_playerHPdiv) + m_playerX, m_playerY, mD_playerDraw, true);
	if (m_playerX > m_playerMaxX - 10)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 125);
		DrawExtendGraph(284 + ((m_playerMaxHP - m_playerHP) / m_playerHPdiv), (m_playerY - size) + ((m_playerMaxHP - m_playerHP) / (m_playerHPdiv / 2))
			, 284 + size - ((m_playerMaxHP - m_playerHP) / m_playerHPdiv), m_playerY, mD_playerDraw, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Game::Process()
{
	SpeedProcess();


	PlayerJump();


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
