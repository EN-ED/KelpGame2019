#pragma once
#include "BaseScene.hpp"
#include "DxLib.h"
#include "InputController.hpp"
#include "Character.hpp"
#include "BackGround.hpp"
#include "Garbage.hpp"



/*
�Q�[���J�n�O�̃`���[�g���A���̃V�[���̑�{
*/
class Tutorial : public BaseScene
{
private:
	/// �N���X�|�C���^-----------------------
	Character* mp_character;
	BackGround* mp_backGround;
	Garbage* mp_garbage[4];


	/// �摜---------------------------------
	int mD_skip;
	int mD_AJump;
	int mD_damage;
	int mD_speed;
	int mD_touyu;
	int mD_start;


	/// �����n-------------------------------
	int m_blendValue;

	int m_stopNum;
	bool m_stopFlag;

	void MainProcess();
	void StopProcess();


public:
	Tutorial();
	~Tutorial();


	// �`��
	void Draw() override;

	// �v���Z�X
	void Process() override;
};

