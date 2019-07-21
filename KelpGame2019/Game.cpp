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
	if (m_nowSpeed < m_playerMaxSpeed - 2 || m_isSpeedChange)
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
	std::random_device rnd;     // 非決定的な乱数生成器を生成
	std::mt19937 mt(rnd());     //  メルセンヌ・ツイスタの32ビット版、引数は初期シード値
	std::uniform_int_distribution<> rand(0, 9);        // [0, 9] 範囲の一様乱数
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
	

	// プレイヤー
	DrawExtendGraph(284 + ((m_playerMaxHP - m_playerHP) / m_playerHPdiv), (m_mostMaxY - 64) + ((m_playerMaxHP - m_playerHP) / (m_playerHPdiv / 2))
		, 284 + 64 - ((m_playerMaxHP - m_playerHP) / m_playerHPdiv), m_mostMaxY, mD_playerDraw, true);
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Game::Process()
{
	SpeedProcess();


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
