#pragma once
#include "BaseScene.hpp"
#include "DxLib.h"
#include "InputController.hpp"
#include "Character.hpp"
#include "BackGround.hpp"
#include "Garbage.hpp"


class Tutorial : public BaseScene
{
private:
	int mD_skip;
	int mD_AJump;
	int mD_damage;
	int mD_speed;
	int mD_touyu;
	int m_blendValue;
	int mD_start;

	Character* mp_character;
	BackGround* mp_backGround;
	Garbage* mp_garbage[4];

	void MainProcess();
	void StopProcess();

	int m_stopNum;
	bool m_stopFlag;


public:
	Tutorial();
	~Tutorial();


	// ï`âÊ
	void Draw() override;

	// ÉvÉçÉZÉX
	void Process() override;
};

