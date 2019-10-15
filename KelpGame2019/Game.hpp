#pragma once
#include "BaseScene.hpp"
#include "BackGround.hpp"
#include "Character.hpp"
#include "Chaser.hpp"
#include "DxLib.h"
#include "InputKey.hpp"
#include "BlurScreen.hpp"
#include "Garbage.hpp"


class Game : public BaseScene
{
private:
	BackGround* mp_backGround;
	Character* mp_character;
	Chaser* mp_chaser;

	bool m_isFirstSpeedUp;

	Garbage* mp_garbage[3];
	const int m_garbageNum = 3;


public:
	Game();
	~Game();


	// ï`âÊ
	void Draw() override;

	// ÉvÉçÉZÉX
	void Process() override;
};

