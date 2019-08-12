#include "Character.hpp"
#include "DxLib.h"
#include "InputKey.hpp"
#include <random>
#include <cmath>

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
	}


	// 最大まで加速中
	if (m_isSpeedUp == 1)
	{
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



	/// 関係ないもの
	m_backGroundColorRed = 10;
	m_backGroundColorGreen = 10;
	m_backGroundColorBlue = 10;

	std::random_device rnd;     // 非決定的な乱数生成器を生成
	std::mt19937 mt(rnd());     //  メルセンヌ・ツイスタの32ビット版、引数は初期シード値
	std::uniform_int_distribution<> rand(0, 5);        // [0, 9] 範囲の一様乱数
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
	// 速度
	DrawFormatString(199, 131, GetColor(255, 255, 255), "%f", m_nowSpeed);


	// プレイヤー
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



	/// 関係ないもの
	if (m_isBackGroundChange)
	{
		std::random_device rnd;     // 非決定的な乱数生成器を生成
		std::mt19937 mt(rnd());     //  メルセンヌ・ツイスタの32ビット版、引数は初期シード値
		std::uniform_int_distribution<> rand(0, 5);        // [0, 9] 範囲の一様乱数
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
