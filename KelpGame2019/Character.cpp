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
		// 加速カウントが足りていなかったら
		if (m_speedUpCount < 1.0)
		{
			m_playerX += static_cast<int>(std::sinf(PI_MATHF * m_speedUpCount) * 120.0f);
		}
	}
	else if (m_nowState == ESTATE::speedMAX)
	{
		// 加速最大中カウントが上限半分以上だったら(軽く左に戻っている中
		if (m_speedMaxWaitCount > m_speedMaxWaitMaxCount / 2 && m_speedMaxWaitCount <= m_speedMaxWaitMaxCount)
		{
			m_playerX -= static_cast<int>(std::sinf(PI_MATHF / 5.0f) * 8.0f);
		}
		// 加速最大中カウントが上限半分以下だったら(軽く右に進んでいる中
		else if (m_speedMaxWaitCount < /* [<]なのはSpeedProcessに合わせるため */ m_speedMaxWaitMaxCount / 2)
		{
			m_playerX += static_cast<int>(std::sinf(PI_MATHF / 5.0f) * 8.0f);
		}
	}
	else if (m_nowState == ESTATE::speedDown)
	{
		// 加速から戻す
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
		m_preDamageSpeed = m_nowSpeed;
	}


	// ダメージを受けたら
	if (m_isDamageHit)
	{
		// ダメージカウントが最大になったら
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
	// 加速中時
	if (m_nowState == ESTATE::speedUp)
	{
		m_nowSpeed += m_addSpeed;		// 速度を加算していく
	}
	// 最大加速時
	else if (m_nowState == ESTATE::speedMAX)
	{

	}
	// 通常時
	else if(m_nowState == ESTATE::speedDown)
	{
		if (m_nowSpeed > m_playerMaxSpeed + 0.5f)
		{
			m_nowSpeed -= m_addSpeed;		// 速度を減少していく
		}
	}
	else if(m_nowState == ESTATE::normal)
	{
		// 最大加速より小さかったら
		if (m_nowSpeed < m_playerMaxSpeed - 0.5f)
		{
			m_nowSpeed += m_addSpeed;		// 速度を加算していく
		}
		// 最大加速より大きかったら
		else if (m_nowSpeed > m_playerMaxSpeed + 0.5f)
		{
			m_nowSpeed -= m_addSpeed;		// 速度を減少していく
		}
		// 浮動小数点的に間にいたら
		else
		{
			// 同じにさせる
			if (m_nowSpeed != static_cast<float>(m_playerMaxSpeed))
			{
				m_nowSpeed = static_cast<float>(m_playerMaxSpeed);
			}
		}
	}
	else if (m_nowState == ESTATE::damageHit)
	{
		if (m_nowSpeed > m_preDamageSpeed * 0.7)
		{
			m_nowSpeed += m_damageDownSpeed;
		}
	}
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Character::SpeedUpProcess()
{
	// Zキーを押されたら
	if (KeyData::Get(KEY_INPUT_Z) == 1 && m_speedUpChargeCount == m_speedUpChargeMax && !m_isJumpFlag && !m_isDamageHit)
	{
		m_isNowSpeedUp = true;
		m_nowState = ESTATE::speedUp;
		m_playerDrawAnimCount = m_runFirstPlayerAnim;
	}


	if (m_nowState == ESTATE::speedUp)
	{
		m_playerDrawAnimCount = m_runFirstPlayerAnim;

		// 加速カウントを進める
		m_speedUpCount += 0.1f;


		// 加速カウントが足りていなかったら
		if (m_speedUpCount < 1.0)
		{
			m_addSpeed += std::sinf(PI_MATHF * m_speedUpCount) * 1.5f;
		}
		// 加速カントがたまったら
		else
		{
			m_nowState = ESTATE::speedMAX;
		}
	}
	else if (m_nowState == ESTATE::speedMAX)
	{
		// 加速最大中カウントが上限半分以上だったら(軽く左に戻っている中
		if (++m_speedMaxWaitCount > m_speedMaxWaitMaxCount)
		{
			m_nowState = ESTATE::speedDown;
			m_isNowSpeedUp = false;
		}
	}
	else if (m_nowState == ESTATE::speedDown)
	{
		if (m_speedMaxWaitCount != 0) m_speedMaxWaitCount = 0;


		// 加速から戻す
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
		// 地面に触れてない(浮いてる
		if (!m_isGroundFlag)
		{
			m_gravityPower += m_jumpGravityEnergy;
			m_playerUnderY += m_gravityPower;

			// 地面に埋まったら
			if (m_playerUnderY > m_mostMaxY)
			{
				m_playerUnderY = m_mostMaxY;
				m_gravityPower = 0;
				m_jumpPower = m_jumpMinPower;
				m_isGroundFlag = true;
				m_isJumpFlag = false;
			}
		}

		// ジャンプボタン押したら
		if (m_isGroundFlag && KeyData::Get(KEY_INPUT_SPACE) == 1 && !m_isNowSpeedUp)
		{
			m_isJumpFlag = true;
			m_isLongJump = true;
			m_isGroundFlag = false;
			m_jumpPower = m_jumpMinPower;
			m_playerDrawAnimCount = m_jumpFirstPlayerAnim;
		}

		// ジャンプ動作していたら
		if (m_isJumpFlag)
		{
			// ジャンプボタンを離したら
			if (KeyData::Get(KEY_INPUT_SPACE) == -1)
			{
				m_isLongJump = false;
			}


			// 長押ししていたら
			if (m_isLongJump && KeyData::Get(KEY_INPUT_SPACE) > 1 && m_jumpPower <= m_jumpMaxPower)
			{
				m_jumpPower += m_jumpAddPower;
			}


			// 上に上げる
			m_playerUnderY -= m_jumpPower;
		}
	}
	else
	{
		// 地面に触れてない(浮いてる
		if (!m_isGroundFlag)
		{
			if (!m_isFlyDamageHit) m_isFlyDamageHit = true;
			m_playerUnderY += 16;

			// 地面に埋まったら
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
	ZeroMemory(mD_playerArraySpeed, sizeof(mD_playerArraySpeed));
	for (int i = 0; i != m_playerDrawNum; ++i)
	{
		std::string str = "media\\anim_blink\\" + std::to_string(i) + ".png";
		mD_playerArray[i] = LoadGraph(str.c_str());
		mD_playerArraySpeed[i] = LoadGraph(str.c_str());
		GraphFilter(mD_playerArraySpeed[i], DX_GRAPH_FILTER_LEVEL, 60, 210, 120, 0, 255);
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
		if (mD_playerArraySpeed[i] != -1) DeleteGraph(mD_playerArraySpeed[i]);
	}
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Character::Draw()
{
	// 速度
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
	

	// プレイヤー
	DrawGraph(m_playerX, m_playerY, mD_playerArray[static_cast<int>(m_playerDrawAnimCount / m_playerDrawAnimSpeed)], true);
	DrawRectGraph(m_playerX, m_playerY, 0, 0, static_cast<int>(m_playerSize * static_cast<float>(m_speedUpChargeCount) / m_speedUpChargeMax), m_playerSize, mD_playerArraySpeed[static_cast<int>(m_playerDrawAnimCount / m_playerDrawAnimSpeed)], TRUE, FALSE);


	switch (m_nowState)
	{
	case ESTATE::normal:
		if (m_speedUpChargeCount == m_speedUpChargeMax && !m_isJumpFlag && !m_isDamageHit)
		{
			DrawFormatString(980, 200, GetColor(0, 255, 255), "通常の加速できる石鹸君");
		}
		else
		{
			DrawFormatString(980, 200, GetColor(255, 255, 255), "通常の石鹸君");
		}
		break;
	case ESTATE::damageHit:
		DrawFormatString(980, 200, GetColor(255, 0, 0), "ダメージ中の石鹸君");
		break;
	case ESTATE::speedDown:
		DrawFormatString(980, 200, GetColor(255, 255, 0), "急加速から戻り中の石鹸君");
		break;
	case ESTATE::speedMAX:
		DrawFormatString(980, 200, GetColor(255, 255, 0), "急加速最大の石鹸君");
		break;
	case ESTATE::speedUp:
		DrawFormatString(980, 200, GetColor(255, 255, 0), "急加速中の石鹸君");
		break;
	default:
		break;
	}
	//printfDx("%d\n", static_cast<int>(m_playerSize * static_cast<float>(m_speedUpChargeCount) / m_speedUpChargeMax));
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
