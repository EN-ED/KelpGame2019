#include "Game.hpp"



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Game::SpeedProcess()
{
	// 速度変換カウントが60以上だったら
	if (m_speedChangeCount++ > 60) m_isSpeedChange = true;		// 速度を少し変えるようにする


	// 現在の速度がプレイヤーの最大速度 - 2以下だったら
	if (m_nowSpeed < m_playerMaxSpeed - 2)
	{
		m_nowSpeed++;		// 速度を加算していく
	}
	else if (m_nowSpeed > m_playerMaxSpeed + 1)
	{
		m_nowSpeed--;
	}
	// 現在の速度がプレイヤーの最大速度 - 2より大きかったら
	else
	{
		// 速度を少し変えるときだったら
		if (m_isSpeedChange)
		{
			m_nowSpeed = m_playerMaxSpeed - 1;		// 現在の速度をプレイヤーの最大速度 - 1にする
		}
		// 速度を少しも変えないときだったら
		else
		{
			m_nowSpeed = m_playerMaxSpeed;		// 現在の速度をプレイヤーの最大速度にする
		}
	}


	// 現在の速度がm_playerMaxSpeed - 2以下もしくは速度を少し変えるときだったら
	if ((m_nowSpeed < m_playerMaxSpeed - 2 || m_nowSpeed > m_playerMaxSpeed + 1) || m_isSpeedChange)
	{
		// 速度変換カウントが10で割り切れる値だったら
		if (m_speedChangeCount % 10 == 0)
		{
			// コンマ以下の数値を変える
			{
				std::random_device rnd;     // 非決定的な乱数生成器を生成
				std::mt19937 mt(rnd());     //  メルセンヌ・ツイスタの32ビット版、引数は初期シード値
				std::uniform_int_distribution<> rand(0, 9);        // [0, 9] 範囲の一様乱数
				m_lowNowSpeed = rand(mt);
			}
		}
	}
	// 現在の速度が68よりも大きくて速度を少しも変えないときだったら
	else
	{
		m_lowNowSpeed = 0;		// コンマ以下の値を0にする
	}


	// 速度変換カウントが80以上だったら
	if (m_speedChangeCount > 80)
	{
		m_speedChangeCount = 0;		// 速度変換カウントを0にする
		m_isSpeedChange = false;	// 速度を少し変えるフラッグを倒す
	}


	// Xキーを押されたら
	if (KeyData::Get(KEY_INPUT_X) == 1)
	{
		m_nowSpeed = m_playerMaxSpeed + m_maxMomentSpeed;		// 瞬間的にスピードを速くする
		m_playerX = m_playerMaxX;							// プレイヤーの位置を右にずらす
	}


	// プレイヤーの座標位置が0以上だったら
	if (m_playerX > 0)
	{
		m_playerX--;		// 戻していく
	}
	else if (m_playerX < 0)
	{
		m_playerX++;
	}


	// デバッグ
	// Cキーが押されたらぶつかったときを想定する
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


	// 地面に触れてない(浮いてる
	if (!m_isGroundFlag)
	{
		m_gravityPower += 2;
		m_playerY += m_gravityPower;
		m_playerX += m_jumpMoveX;

		// 地面に埋まったら
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

	// 地面にいてジャンプボタン押したら
	if (m_isGroundFlag && KeyData::Get(KEY_INPUT_SPACE) == 1)
	{
		m_isJumpFlag = true;
		m_isLongJump = true;
		m_isGroundFlag = false;
		m_isFallNow = false;
		m_jumpPower = m_jumpMinPower;
	}

	// ジャンプ動作していたら
	if (m_isJumpFlag)
	{
		if (KeyData::Get(KEY_INPUT_SPACE) == -1)
		{
			m_isLongJump = false;
		}
		// 長押ししていたら
		if (m_isLongJump && KeyData::Get(KEY_INPUT_SPACE) > 1 && m_jumpPower <= m_jumpMaxPower)
		{
			m_jumpPower += 5;
		}
		m_playerY -= m_jumpPower;
	}

	// 直前のY座標が今のY座標より上だったら
	if (m_preY < m_playerY)
	{
		m_isFallNow = true;
	}
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
Game::Game()
{
	mD_backGroundDraw = LoadGraph("media\\background.png");
	mD_playerDraw = LoadGraph("media\\player_size_diffe\\player×2.png");
	mD_chaserDraw = LoadGraph("media\\chaser.png");
	mD_garbageDraw = LoadGraph("media\\garbage.png");
	mD_underGroundDraw = LoadGraph("media\\underground.png");

	m_playerHP = m_playerMaxHP;

	m_nowSpeed = 0;
	std::random_device rnd;     // 非決定的な乱数生成器を生成
	std::mt19937 mt(rnd());     //  メルセンヌ・ツイスタの32ビット版、引数は初期シード値
	std::uniform_int_distribution<> rand(0, 9);        // [0, 9] 範囲の一様乱数
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
	// 背景
	DrawGraph(m_scrollX, 0, mD_backGroundDraw, false);
	DrawGraph(m_scrollX + 1920, 0, mD_backGroundDraw, false);


	// 地面
	DrawGraph(m_scrollX, m_mostMaxY, mD_underGroundDraw, false);
	DrawGraph(m_scrollX + 1920, m_mostMaxY, mD_underGroundDraw, false);


	// 追いかけるもの
	DrawGraph(0, m_mostMaxY - 512, mD_chaserDraw, true);


	// 速度
	DrawFormatString(199, 131, GetColor(255, 255, 255), "%d.%d", m_nowSpeed, m_lowNowSpeed);
	
	int size = 128;
	// プレイヤー
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


	// 現在のスピードが0じゃなかったら
	if(m_nowSpeed != 0) m_playerHP--;		// プレイヤーの体力を減らす


	// スクロール値が-1920以下だったら
	if (m_scrollX < -1920)
	{
		m_scrollX = 0;			// スクロール値を0に戻す
	}
	// スクロール値が-1920よりも大きかったら
	else
	{
		m_scrollX -= m_nowSpeed / 5;		// 現在の速度から5割った値ずつスクロール値を減らす
	}


	// プレイヤーの体力が0以下だったら
	if (m_playerHP <= 0)
	{
		BASICPARAM::e_nowScene = ESceneNumber::GAMEOVER;		// GAMEOVERのシーンへ移行する
	}
}
