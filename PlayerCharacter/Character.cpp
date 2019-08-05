#include "Character.hpp"
#include <random>
#include <cmath>

#define PI_MATHF 3.14159265359f



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Character::SpeedProcess()
{
	// ���݂̑��x���v���C���[�̍ő呬�x�ȉ���������
	if (m_isSpeedUp == 1)
	{
		if (m_nowSpeed < (m_playerMaxSpeed + m_isSpeedUp * 30.0f) - 1.0f)
		{
			m_nowSpeed += m_addSpeed;		// ���x�����Z���Ă���
		}
		else if (m_nowSpeed > (m_playerMaxSpeed + m_isSpeedUp * 30.0f) + 1.0f)
		{
			m_nowSpeed -= m_addSpeed;		// ���x�����Z���Ă���
		}
	}
	else
	{
		if (m_nowSpeed < (m_playerMaxSpeed) - 1.0f)
		{
			m_nowSpeed += m_addSpeed;		// ���x�����Z���Ă���
		}
		else if (m_nowSpeed > (m_playerMaxSpeed) + 1.0f)
		{
			m_nowSpeed -= m_addSpeed;		// ���x�����Z���Ă���
		}
	}


	// �n�ʂɐG��ĂȂ�(�����Ă�
	if (!m_isGroundFlag)
	{
		m_nowSpeed += m_jumpDownSpeed;
	}


	if (KeyData::Get(KEY_INPUT_Z) == 1 && m_speedMaxWaitCount == 0)
	{
		m_isSpeedUp = 1;
		m_speedUpCount = 0;
	}

	if (m_isSpeedUp == 1)
	{
		m_speedUpCount += 0.1f;
		if (m_speedUpCount < 1.0)
		{
			m_addSpeed += std::sinf(PI_MATHF * m_speedUpCount) * 4.0f;
			m_playerX += static_cast<int>(std::sinf(PI_MATHF * m_speedUpCount) * 120.0f);
		}
		else
		{
			m_isSpeedUp = 2;
		}
	}
	else if (m_isSpeedUp == 2)
	{
		m_speedMaxWaitCount++;
		if (m_speedMaxWaitCount > (m_speedMaxWaitMaxCount / 4) * 3 && m_speedMaxWaitCount <= m_speedMaxWaitMaxCount)
		{
			m_addSpeed += std::sinf(PI_MATHF / 5.0f) * 0.1f;
			m_playerX += static_cast<int>(std::sinf(PI_MATHF / 5.0f) * 5.0f);
		}
		else if (m_speedMaxWaitCount > (m_speedMaxWaitMaxCount / 4) * 2 && m_speedMaxWaitCount <= (m_speedMaxWaitMaxCount / 4) * 3)
		{
			m_addSpeed -= std::sinf(PI_MATHF / 5.0f) * 0.1f;
			m_playerX -= static_cast<int>(std::sinf(PI_MATHF / 5.0f) * 5.0f);
		}
		else if (m_speedMaxWaitCount > m_speedMaxWaitMaxCount / 4 && m_speedMaxWaitCount <= (m_speedMaxWaitMaxCount / 4) * 2)
		{
			m_addSpeed -= std::sinf(PI_MATHF / 5.0f) * 0.1f;
			m_playerX -= static_cast<int>(std::sinf(PI_MATHF / 5.0f) * 5.0f);
		}
		else if (m_speedMaxWaitCount <= m_speedMaxWaitMaxCount / 4)
		{
			m_addSpeed += std::sinf(PI_MATHF / 5.0f) * 0.1f;
			m_playerX += static_cast<int>(std::sinf(PI_MATHF / 5.0f) * 5.0f);
		}
		else
		{
			m_isSpeedUp = 0;
		}
	}
	else
	{
		if (m_speedMaxWaitCount > 0)
		{
			m_speedMaxWaitCount--;
		}
		m_speedUpCount -= 0.1f;
		if (m_speedUpCount > 0)
		{
			m_addSpeed -= std::sinf(PI_MATHF * m_speedUpCount) * 4.0f;
			m_playerX -= static_cast<int>(std::sinf(PI_MATHF * m_speedUpCount) * 120.0f);
		}
	}
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Character::PlayerJump()
{
	// �n�ʂɐG��ĂȂ�(�����Ă�
	if (!m_isGroundFlag)
	{
		m_gravityPower += 2;
		m_playerUnderY += m_gravityPower;

		// �n�ʂɖ��܂�����
		if (m_playerUnderY > m_mostMaxY)
		{
			m_playerUnderY = m_mostMaxY;
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
		m_playerUnderY -= m_jumpPower;
	}
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
Character::Character()
{
	mD_playerDraw = LoadGraph("media\\player.png");

	m_damageCount = 0;

	m_nowSpeed = 0.0f;
	m_addSpeed = 1.0f;
	m_isSpeedUp = 0;
	m_speedUpCount = 0;
	m_speedMaxWaitCount = 0;

	m_playerUnderY = m_mostMaxY;
	m_playerY = m_playerUnderY - m_playerSize;
	m_playerX = m_defaultX;

	m_isGroundFlag = true;
	m_isJumpFlag = false;
	m_isLongJump = false;
	m_jumpPower = m_jumpMinPower;
	m_gravityPower = 0;



	/// �֌W�Ȃ�����
	m_backGroundColorRed = 10;
	m_backGroundColorGreen = 10;
	m_backGroundColorBlue = 10;

	std::random_device rnd;     // �񌈒�I�ȗ���������𐶐�
	std::mt19937 mt(rnd());     //  �����Z���k�E�c�C�X�^��32�r�b�g�ŁA�����͏����V�[�h�l
	std::uniform_int_distribution<> rand(0, 5);        // [0, 9] �͈͂̈�l����
	m_backGroundSwitch = rand(mt);
	m_isBackGroundChange = false;
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
Character::~Character()
{
	if (mD_playerDraw != -1) DeleteGraph(mD_playerDraw);
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Character::Draw()
{
	/// �֌W�Ȃ�����
	// �w�i
	DrawBox(0, 0, 1920, 1080, GetColor(m_backGroundColorRed, m_backGroundColorGreen, m_backGroundColorBlue), true);
	DrawBox(100, 140, 150, 140 - static_cast<int>(m_nowSpeed), GetColor(125, 125, 125), true);


	// ���x
	DrawFormatString(199, 131, GetColor(255, 255, 255), "%f", m_nowSpeed);


	// �v���C���[
	if (m_damageCount >= 15)
	{
		DrawGraph(m_playerX, m_playerY, mD_playerDraw, true);
	}

	DrawFormatString(0, 0, GetColor(255, 255, 255), "%d", m_playerX);
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Character::Process()
{
	SpeedProcess();


	PlayerJump();


	m_playerY = m_playerUnderY - m_playerSize;


	if (++m_damageCount > 30) m_damageCount = 0;



	/// �֌W�Ȃ�����
	if (m_isBackGroundChange)
	{
		std::random_device rnd;     // �񌈒�I�ȗ���������𐶐�
		std::mt19937 mt(rnd());     //  �����Z���k�E�c�C�X�^��32�r�b�g�ŁA�����͏����V�[�h�l
		std::uniform_int_distribution<> rand(0, 5);        // [0, 9] �͈͂̈�l����
		m_backGroundSwitch = rand(mt);
		m_isBackGroundChange = false;
	}
	else
	{
		switch (m_backGroundSwitch)
		{
		case 0:
			if (m_backGroundColorRed > 180)
			{
				m_isBackGroundChange = true;
			}
			m_backGroundColorRed += m_speedMaxWaitCount > 0 ? 4 : 1;
			break;

		case 1:
			if (m_backGroundColorGreen > 180)
			{
				m_isBackGroundChange = true;
			}
			m_backGroundColorGreen += m_speedMaxWaitCount > 0 ? 4 : 1;
			break;

		case 2:
			if (m_backGroundColorBlue > 180)
			{
				m_isBackGroundChange = true;
			}
			m_backGroundColorBlue += m_speedMaxWaitCount > 0 ? 4 : 1;
			break;

		case 3:
			if (m_backGroundColorRed < 10)
			{
				m_isBackGroundChange = true;
			}
			m_backGroundColorRed -= m_speedMaxWaitCount > 0 ? 4 : 1;
			break;

		case 4:
			if (m_backGroundColorGreen < 10)
			{
				m_isBackGroundChange = true;
			}
			m_backGroundColorGreen -= m_speedMaxWaitCount > 0 ? 4 : 1;
			break;

		case 5:
			if (m_backGroundColorBlue < 10)
			{
				m_isBackGroundChange = true;
			}
			m_backGroundColorBlue -= m_speedMaxWaitCount > 0 ? 4 : 1;
			break;

		default:
			m_backGroundColorRed = 0;
			m_backGroundColorGreen = 0;
			m_backGroundColorBlue = 0;
			break;
		}
	}
}
