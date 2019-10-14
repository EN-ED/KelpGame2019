#pragma once
#include "BaseScene.hpp"
#include "BackGround.hpp"
#include "Character.hpp"
#include "Chaser.hpp"
#include "DxLib.h"
#include "InputKey.hpp"
#include "BlurScreen.hpp"


class Game : public BaseScene
{
private:
	BackGround* mp_backGround;
	Character* mp_character;
	Chaser* mp_chaser;

	bool m_isFirstSpeedUp;


public:
	Game();
	~Game();


	// 描画
	void Draw() override;

	// プロセス
	void Process() override;
};

