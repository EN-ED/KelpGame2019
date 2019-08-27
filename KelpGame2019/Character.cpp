#include "Character.hpp"
#include "DxLib.h"
#include "InputKey.hpp"
#include <random>
#include <cmath>
#include <string>

constexpr float PI_MATHF = 3.14159265359f;


/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Character::PositionProcess()
{
	if (m_nowState == ESTATE::speedUp)
	{
		// �����J�E���g������Ă��Ȃ�������
		if (m_speedUpCount < 1.0)
		{
			m_playerX += static_cast<int>(std::sinf(PI_MATHF * m_speedUpCount) * 120.0f);
		}
	}
	else if (m_nowState == ESTATE::speedMAX)
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
	else if (m_nowState == ESTATE::speedDown)
	{
		// ��������߂�
		if (m_speedUpCount > 0.1f)
		{
			m_playerX -= static_cast<int>(std::sinf(PI_MATHF * m_speedUpCount) * 120.0f);
		}
	}
	else if (m_nowState == ESTATE::damageHit)
	{
		m_playerX -= 2;
	}
	else if(m_nowState ==ESTATE::normal)
	{
		if (m_playerX < m_defaultX)
		{
			m_playerX++;
		}
		else if (m_playerX > m_defaultX)
		{
			m_playerX--;
		}
	}


	m_playerY = m_playerUnderY - m_playerSize;
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Character::DamageProcess()
{
	if (KeyData::Get(KEY_INPUT_D) == 1 && !m_isNowSpeedUp && m_nowState != ESTATE::speedDown)
	{
		if (m_isDamageHit != true) m_isDamageHit = true;
		m_nowState = ESTATE::damageHit;
		m_speedUpChargeCount = -(m_speedUpChargeMax + m_speedUpChargeMax / 2);
	}


	// �_���[�W���󂯂���
	if (m_isDamageHit)
	{
		m_speedUpChargeCount = -(m_speedUpChargeMax + m_speedUpChargeMax / 2);
		// �_���[�W�J�E���g���ő�ɂȂ�����
		if (++m_damageCount > m_damageMaxCount && m_isGroundFlag)
		{
			m_damageCount = 0;
			m_isDamageHit = false;
			m_nowState = ESTATE::normal;
		}
	}
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Character::SpeedProcess()
{
	// ��������
	if (m_nowState == ESTATE::speedUp)
	{
		m_nowSpeed += m_addSpeed;		// ���x�����Z���Ă���
	}
	// �ő������
	else if (m_nowState == ESTATE::speedMAX)
	{

	}
	// �ʏ펞
	else if(m_nowState == ESTATE::speedDown)
	{
		if (m_nowSpeed > m_playerMaxSpeed + 0.5f)
		{
			m_nowSpeed -= m_addSpeed;		// ���x���������Ă���
		}
	}
	else if(m_nowState == ESTATE::normal)
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
	if (m_isDamageHit)
	{
		if (m_nowSpeed > m_playerMaxSpeed / 2)
		{
			m_nowSpeed += m_jumpDownSpeed;
		}
	}
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Character::SpeedUpProcess()
{
	// Z�L�[��������A�������ł���悤�ɂȂ��Ă�����
	if (KeyData::Get(KEY_INPUT_Z) == 1 && m_speedUpChargeCount == m_speedUpChargeMax && !m_isJumpFlag && !m_isDamageHit)
	{
		m_isNowSpeedUp = true;
		m_nowState = ESTATE::speedUp;
		m_playerDrawAnimCount = m_runFirstPlayerAnim;
	}


	if (m_nowState == ESTATE::speedUp)
	{
		m_playerDrawAnimCount = m_runFirstPlayerAnim;

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
			m_nowState = ESTATE::speedMAX;
		}
	}
	else if (m_nowState == ESTATE::speedMAX)
	{
		// �����ő咆�J�E���g����������ȏゾ������(�y�����ɖ߂��Ă��钆
		if (++m_speedMaxWaitCount > m_speedMaxWaitMaxCount)
		{
			m_nowState = ESTATE::speedDown;
			m_isNowSpeedUp = false;
		}
	}
	else if (m_nowState == ESTATE::speedDown)
	{
		if (m_speedMaxWaitCount != 0) m_speedMaxWaitCount = 0;


		// ��������߂�
		if (m_speedUpCount > 0.1f)
		{
			m_speedUpCount -= 0.1f;
			m_addSpeed -= std::sinf(PI_MATHF * m_speedUpCount) * 1.5f;
		}
		else
		{
			m_nowState = ESTATE::normal;
		}
	}
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Character::PlayerJump()
{
	if (!m_isDamageHit && !m_isFlyDamageHit)
	{
		// �n�ʂɐG��ĂȂ�(�����Ă�
		if (!m_isGroundFlag)
		{
			m_gravityPower += m_jumpGravityEnergy;
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

		// �W�����v�{�^����������
		if (m_isGroundFlag && KeyData::Get(KEY_INPUT_SPACE) == 1 && !m_isNowSpeedUp)
		{
			m_isJumpFlag = true;
			m_isLongJump = true;
			m_isGroundFlag = false;
			m_jumpPower = m_jumpMinPower;
			m_playerDrawAnimCount = m_jumpFirstPlayerAnim;
		}

		// �W�����v���삵�Ă�����
		if (m_isJumpFlag)
		{
			// �W�����v�{�^���𗣂�����
			if (KeyData::Get(KEY_INPUT_SPACE) == -1)
			{
				m_isLongJump = false;
			}


			// ���������Ă�����
			if (m_isLongJump && KeyData::Get(KEY_INPUT_SPACE) > 1 && m_jumpPower <= m_jumpMaxPower)
			{
				m_jumpPower += m_jumpAddPower;
			}


			// ��ɏグ��
			m_playerUnderY -= m_jumpPower;
		}
	}
	else
	{
		// �n�ʂɐG��ĂȂ�(�����Ă�
		if (!m_isGroundFlag)
		{
			if (!m_isFlyDamageHit) m_isFlyDamageHit = true;
			m_playerUnderY += 16;

			// �n�ʂɖ��܂�����
			if (m_playerUnderY > m_mostMaxY)
			{
				m_isFlyDamageHit = false;
				m_playerUnderY = m_mostMaxY;
				m_gravityPower = 0;
				m_jumpPower = m_jumpMinPower;
				m_isGroundFlag = true;
				m_isJumpFlag = false;
			}
		}
	}
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
Character::Character()
{
	ZeroMemory(mD_playerArray, sizeof(mD_playerArray));
	for (int i = 0; i != m_playerDrawNum; ++i)
	{
		std::string str = "media\\anim_blink\\" + std::to_string(i) + ".png";
		mD_playerArray[i] = LoadGraph(str.c_str());
	}
	m_playerDrawAnimCount = 0;

	m_damageCount = 0;
	m_isDamageHit = false;

	m_isNowSpeedUp = false;
	m_nowSpeed = 0.0f;
	m_addSpeed = 1.0f;
	m_nowState = ESTATE::normal;
	m_speedUpCount = 0;
	m_speedMaxWaitCount = 0;
	m_nowSpeedThirdDigit = 0;
	m_nowSpeedSecondDigit = 0;
	m_nowSpeedFirstDigit = 0;
	m_nowSpeedDecimalPoint = 0;
	m_speedUpChargeCount = 0;

	m_playerUnderY = m_mostMaxY;
	m_playerX = m_defaultX;
	m_playerY = m_playerUnderY - m_playerSize;
	m_prePlayerX = m_playerX;
	m_prePlayerY = m_playerY;

	m_isGroundFlag = true;
	m_isJumpFlag = false;
	m_isLongJump = false;
	m_jumpPower = m_jumpMinPower;
	m_gravityPower = 0;
	m_isFlyDamageHit = false;
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
Character::~Character()
{
	for (int i = 0; i != m_playerDrawNum; ++i)
	{
		if (mD_playerArray[i] != -1) DeleteGraph(mD_playerArray[i]);
	}
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Character::Draw()
{
	// ���x
	if (m_nowSpeedThirdDigit != 0)
	{
		DrawFormatString(199, 131, GetColor(255, 255, 255), "%d%d%d.%d", m_nowSpeedThirdDigit, m_nowSpeedSecondDigit, m_nowSpeedFirstDigit, m_nowSpeedDecimalPoint);
	}
	else if (m_nowSpeedSecondDigit != 0)
	{
		DrawFormatString(199, 131, GetColor(255, 255, 255), "%d%d.%d", m_nowSpeedSecondDigit, m_nowSpeedFirstDigit, m_nowSpeedDecimalPoint);
	}
	else if (m_nowSpeedFirstDigit != 0)
	{
		DrawFormatString(199, 131, GetColor(255, 255, 255), "%d.%d", m_nowSpeedFirstDigit, m_nowSpeedDecimalPoint);
	}
	else
	{
		DrawFormatString(199, 131, GetColor(255, 255, 255), "0.%d", m_nowSpeedDecimalPoint);
	}

	DrawFormatString(199, 151, GetColor(255, 255, 255), "%d", m_playerX);
	

	// �v���C���[
	DrawGraph(m_playerX, m_playerY, mD_playerArray[static_cast<int>(m_playerDrawAnimCount / m_playerDrawAnimSpeed)], true);


	/*switch (m_nowState)
	{
	case ESTATE::normal:
		printfDx("normal\n");
		break;
	case ESTATE::damageHit:
		printfDx("damageHit\n");
		break;
	case ESTATE::speedDown:
		printfDx("speedDown\n");
		break;
	case ESTATE::speedMAX:
		printfDx("speedMAX\n");
		break;
	case ESTATE::speedUp:
		printfDx("speedUp\n");
		break;
	default:
		break;
	}*/
	printfDx("%d\n", m_speedUpChargeCount);
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Character::BlurDraw()
{
	DrawGraph(m_prePlayerX, m_prePlayerY, mD_playerArray[static_cast<int>(m_playerDrawAnimCount / m_playerDrawAnimSpeed)], true);
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Character::Process()
{
	m_prePlayerX = m_playerX;
	m_prePlayerY = m_playerY;


	if (++m_playerDrawAnimCount >= m_playerDrawAnimSpeed * m_playerDrawNum) m_playerDrawAnimCount = 0;


	SpeedProcess();


	SpeedUpProcess();


	PlayerJump();


	DamageProcess();


	PositionProcess();


	if (m_isNowSpeedUp)
	{
		if (m_speedUpChargeCount != 0) m_speedUpChargeCount = 0;
	}
	else
	{
		if (m_speedUpChargeCount < m_speedUpChargeMax) m_speedUpChargeCount++;
	}

	int temp = static_cast<int>(m_nowSpeed * 10);
	if (temp > 1000)
	{
		m_nowSpeedThirdDigit = temp / 1000;
		m_nowSpeedSecondDigit = temp / 100 - (m_nowSpeedThirdDigit * 10);
		m_nowSpeedFirstDigit = temp / 10 - (m_nowSpeedThirdDigit * 100) - (m_nowSpeedSecondDigit * 10);
		m_nowSpeedDecimalPoint = temp - (m_nowSpeedThirdDigit * 1000) - (m_nowSpeedSecondDigit * 100) - (m_nowSpeedFirstDigit * 10);
	}
	else if (temp > 100)
	{
		m_nowSpeedThirdDigit = 0;
		m_nowSpeedSecondDigit = temp / 100;
		m_nowSpeedFirstDigit = temp / 10 - (m_nowSpeedSecondDigit * 10);
		m_nowSpeedDecimalPoint = temp - (m_nowSpeedSecondDigit * 100) - (m_nowSpeedFirstDigit * 10);
	}
	else if (temp > 10)
	{
		m_nowSpeedThirdDigit = 0;
		m_nowSpeedSecondDigit = 0;
		m_nowSpeedFirstDigit = temp / 10;
		m_nowSpeedDecimalPoint = temp - (m_nowSpeedFirstDigit * 10);
	}
	else
	{
		m_nowSpeedThirdDigit = 0;
		m_nowSpeedSecondDigit = 0;
		m_nowSpeedFirstDigit = 0;
		m_nowSpeedDecimalPoint = temp;
	}
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
const bool& Character::GetIsSpeedUp() const
{
	return m_isNowSpeedUp;
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
const float& Character::GetSpeed() const
{
	return m_nowSpeed;
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
const int Character::GetFromDefaultAreaX() const
{
	return m_defaultX - m_playerX;
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Character::SetIsDamageHit(bool& t_isDamageHit)
{
	m_isDamageHit = t_isDamageHit;
}
