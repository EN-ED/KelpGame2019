#include "Character.hpp"
#include "DxLib.h"
#include "InputKey.hpp"
#include <random>
#include <cmath>

constexpr float PI_MATHF = 3.14159265359f;



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Character::PositionProcess()
{
	// �ő�܂ŉ�����
	if (m_isSpeedUp == 1)
	{
		// �����J�E���g������Ă��Ȃ�������
		if (m_speedUpCount < 1.0)
		{
			m_playerX += static_cast<int>(std::sinf(PI_MATHF * m_speedUpCount) * 120.0f);
		}
	}
	// �����ő厞��������
	else if (m_isSpeedUp == 2)
	{
		// �����ő咆�J�E���g����������ȏゾ������(�y�����ɖ߂��Ă��钆
		if (m_speedMaxWaitCount > m_speedMaxWaitMaxCount / 2 && m_speedMaxWaitCount <= m_speedMaxWaitMaxCount)
		{
			m_playerX -= static_cast<int>(std::sinf(PI_MATHF / 5.0f) * 8.0f);
		}
		// �����ő咆�J�E���g����������ȉ���������(�y���E�ɐi��ł��钆
		else if (m_speedMaxWaitCount < /* [<]�Ȃ̂�SpeedProcess�ɍ��킹�邽�� */ m_speedMaxWaitMaxCount / 2)
		{
			m_playerX += static_cast<int>(std::sinf(PI_MATHF / 5.0f) * 8.0f);
		}
	}
	else
	{
		// ��������߂�
		if (m_speedUpCount > 0.1f)
		{
			m_playerX -= static_cast<int>(std::sinf(PI_MATHF * m_speedUpCount) * 120.0f);
		}
	}
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Character::DamageProcess()
{
	// �_���[�W���󂯂���
	if (m_isDamageHit)
	{
		// �_���[�W�J�E���g���ő�ɂȂ�����
		if (++m_damageCount > m_damageMaxCount)
		{
			m_damageCount = 0;
			m_isDamageHit = false;
		}
	}
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Character::SpeedProcess()
{
	// ��������
	if (m_isSpeedUp == 1)
	{
		m_nowSpeed += m_addSpeed;		// ���x�����Z���Ă���
	}
	// �ő������
	else if (m_isSpeedUp == 2)
	{

	}
	// �ʏ펞
	else
	{
		// �ő������菬����������
		if (m_nowSpeed < m_playerMaxSpeed - 0.5f)
		{
			m_nowSpeed += m_addSpeed;		// ���x�����Z���Ă���
		}
		// �ő�������傫��������
		else if (m_nowSpeed > m_playerMaxSpeed + 0.5f)
		{
			m_nowSpeed -= m_addSpeed;		// ���x���������Ă���
		}
		// ���������_�I�ɊԂɂ�����
		else
		{
			// �����ɂ�����
			if (m_nowSpeed != static_cast<float>(m_playerMaxSpeed))
			{
				m_nowSpeed = static_cast<float>(m_playerMaxSpeed);
			}
		}
	}


	// �n�ʂɐG��ĂȂ�(�����Ă�
	if (!m_isGroundFlag)
	{
		m_nowSpeed += m_jumpDownSpeed;
	}


	// Z�L�[��������A�������ł���悤�ɂȂ��Ă�����
	if (KeyData::Get(KEY_INPUT_Z) == 1 && m_speedMaxWaitCount == 0)
	{
		m_isSpeedUp = 1;
	}


	// �ő�܂ŉ�����
	if (m_isSpeedUp == 1)
	{
		// �����J�E���g��i�߂�
		m_speedUpCount += 0.1f;


		// �����J�E���g������Ă��Ȃ�������
		if (m_speedUpCount < 1.0)
		{
			m_addSpeed += std::sinf(PI_MATHF * m_speedUpCount) * 1.5f;
		}
		// �����J���g�����܂�����
		else
		{
			// �����ő咆�Ƃ���
			m_isSpeedUp = 2;
		}
	}
	// �����ő厞��������
	else if (m_isSpeedUp == 2)
	{
		// �����ő咆�J�E���g����������ȏゾ������(�y�����ɖ߂��Ă��钆
		if (++m_speedMaxWaitCount > m_speedMaxWaitMaxCount)
		{
			// �ʏ펞�ɖ߂�
			m_isSpeedUp = 0;
		}
	}
	else
	{
		// �������o����܂ŃJ�E���g�����炷
		if (m_speedMaxWaitCount > 0)
		{
			m_speedMaxWaitCount--;
		}


		// ��������߂�
		if (m_speedUpCount > 0.1f)
		{
			m_speedUpCount -= 0.1f;
			m_addSpeed -= std::sinf(PI_MATHF * m_speedUpCount) * 1.5f;
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
		// �W�����v�{�^����b������
		if (KeyData::Get(KEY_INPUT_SPACE) == -1)
		{
			m_isLongJump = false;
		}


		// ���������Ă�����
		if (m_isLongJump && KeyData::Get(KEY_INPUT_SPACE) > 1 && m_jumpPower <= m_jumpMaxPower)
		{
			m_jumpPower += 5;
		}


		// ��ɏグ��
		m_playerUnderY -= m_jumpPower;
	}
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
Character::Character()
{
	mD_playerDraw = LoadGraph("media\\player.png");
	mD_playerDamageDraw = LoadGraph("media\\player.png");
	GraphFilter(mD_playerDamageDraw, DX_GRAPH_FILTER_HSB, 1, 0, 90, -60);

	m_damageCount = 0;
	m_isDamageHit = false;

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
	if (mD_playerDamageDraw != -1) DeleteGraph(mD_playerDamageDraw);
	if (mD_playerDraw != -1) DeleteGraph(mD_playerDraw);
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Character::Draw()
{
	// ���x
	DrawFormatString(199, 131, GetColor(255, 255, 255), "%f", m_nowSpeed);


	// �v���C���[
	if (m_damageCount >= m_damageMaxCount / 2)
	{
		DrawGraph(m_playerX, m_playerY, mD_playerDamageDraw, true);
	}
	else
	{
		DrawGraph(m_playerX, m_playerY, mD_playerDraw, true);
	}
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Character::Process()
{
	SpeedProcess();


	PlayerJump();


	DamageProcess();


	PositionProcess();


	m_playerY = m_playerUnderY - m_playerSize;



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
			m_backGroundColorRed += 1;
			break;

		case 1:
			if (m_backGroundColorGreen > 180)
			{
				m_isBackGroundChange = true;
			}
			m_backGroundColorGreen += 1;
			break;

		case 2:
			if (m_backGroundColorBlue > 180)
			{
				m_isBackGroundChange = true;
			}
			m_backGroundColorBlue += 1;
			break;

		case 3:
			if (m_backGroundColorRed < 10)
			{
				m_isBackGroundChange = true;
			}
			m_backGroundColorRed -= 1;
			break;

		case 4:
			if (m_backGroundColorGreen < 10)
			{
				m_isBackGroundChange = true;
			}
			m_backGroundColorGreen -= 1;
			break;

		case 5:
			if (m_backGroundColorBlue < 10)
			{
				m_isBackGroundChange = true;
			}
			m_backGroundColorBlue -= 1;
			break;

		default:
			m_backGroundColorRed = 0;
			m_backGroundColorGreen = 0;
			m_backGroundColorBlue = 0;
			break;
		}
	}
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
const bool& Character::GetIsSpeedUp() const
{
	if (m_isSpeedUp == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}
