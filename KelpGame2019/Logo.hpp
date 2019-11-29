#pragma once
#include "BaseScene.hpp"
#include "DxLib.h"
#include "InputController.hpp"



/*
���S�̃V�[���̑�{
*/
class Logo : public BaseScene
{
private:
	// �摜-----------------------------------
	int mD_dxlibLogo;		// dxlib�̉摜
	int mD_skip;			// �X�L�b�v�摜

	// �`�[�����S�֌W-------------------------
	int mD_teamLogo;
	int mD_Re;				
	int mD_Okizari;
	int mD_Pazuru;
	int mD_Escape;


	// ���S�̓���-----------------------------
	int m_x;
	int m_y;
	int m_addX;
	int m_addY;
	int m_turnY;

	
	// �V�[���̏����֌W-----------------------
	enum class ELOGONOW { dxlib, team };
	ELOGONOW m_nowLogoNumber;	// ���݂̃��S
	int m_logoTransTime;	// ���S�̑J�ڎ���


public:
	Logo();
	~Logo();


	// �`��
	void Draw() override;

	// �v���Z�X
	void Process() override;
};

