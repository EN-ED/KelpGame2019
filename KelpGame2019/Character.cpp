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
	// 最大まで加速中
	if (m_isSpeedUp == 1)
	{
		// 加速カウントが足りていなかったら
		if (m_speedUpCount < 1.0)
		{
			m_playerX += static_cast<int>(std::sinf(PI_MATHF * m_speedUpCount) * 120.0f);
		}
	}
	// 加速最大時だったら
	else if (m_isSpeedUp == 2)
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
	else
	{
		// 加速から戻す
		if (m_speedUpCount > 0.1f)
		{
			m_playerX -= static_cast<int>(std::sinf(PI_MATHF * m_speedUpCount) * 120.0f);
		}
	}
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Character::DamageProcess()
{
	// ダメージを受けたら
	if (m_isDamageHit)
	{
		// ダメージカウントが最大になったら
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
	// 加速中時
	if (m_isSpeedUp == 1)
	{
		m_nowSpeed += m_addSpeed;		// 速度を加算していく
	}
	// 最大加速時
	else if (m_isSpeedUp == 2)
	{

	}
	// 通常時
	else
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


	// 地面に触れてない(浮いてる
	if (!m_isGroundFlag)
	{
		m_nowSpeed += m_jumpDownSpeed;
	}


	// Zキーを押され、加速ができるようになっていたら
	if (KeyData::Get(KEY_INPUT_Z) == 1 && m_speedMaxWaitCount == 0)
	{
		m_isSpeedUp = 1;
		m_playerDrawAnimCount = 78;
	}


	// 最大まで加速中
	if (m_isSpeedUp == 1)
	{
		m_playerDrawAnimCount = 78;

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
			// 加速最大中とする
			m_isSpeedUp = 2;
		}
	}
	// 加速最大時だったら
	else if (m_isSpeedUp == 2)
	{
		// 加速最大中カウントが上限半分以上だったら(軽く左に戻っている中
		if (++m_speedMaxWaitCount > m_speedMaxWaitMaxCount)
		{
			// 通常時に戻る
			m_isSpeedUp = 0;
		}
	}
	else
	{
		// 加速が出来るまでカウントを減らす
		if (m_speedMaxWaitCount > 0)
		{
			m_speedMaxWaitCount--;
		}


		// 加速から戻す
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
	// 地面に触れてない(浮いてる
	if (!m_isGroundFlag)
	{
		m_gravityPower += 2;
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

	// 地面にいてジャンプボタン押したら
	if (m_isGroundFlag && KeyData::Get(KEY_INPUT_SPACE) == 1)
	{
		m_isJumpFlag = true;
		m_isLongJump = true;
		m_isGroundFlag = false;
		m_jumpPower = m_jumpMinPower;
	}

	// ジャンプ動作していたら
	if (m_isJumpFlag)
	{
		// ジャンプボタンを話したら
		if (KeyData::Get(KEY_INPUT_SPACE) == -1)
		{
			m_isLongJump = false;
		}


		// 長押ししていたら
		if (m_isLongJump && KeyData::Get(KEY_INPUT_SPACE) > 1 && m_jumpPower <= m_jumpMaxPower)
		{
			m_jumpPower += 5;
		}


		// 上に上げる
		m_playerUnderY -= m_jumpPower;
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

	m_nowSpeed = 0.0f;
	m_addSpeed = 1.0f;
	m_isSpeedUp = 0;
	m_speedUpCount = 0;
	m_speedMaxWaitCount = 0;
	m_nowSpeedThirdDigit = 0;
	m_nowSpeedSecondDigit = 0;
	m_nowSpeedFirstDigit = 0;
	m_nowSpeedDecimalPoint = 0;

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


	PlayerJump();


	DamageProcess();


	PositionProcess();


	m_playerY = m_playerUnderY - m_playerSize;

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
const bool Character::GetIsSpeedUp() const
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



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
const float& Character::GetSpeed() const
{
	return m_nowSpeed;
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Character::SetIsDamageHit(bool& t_isDamageHit)
{
	m_isDamageHit = t_isDamageHit;
}
