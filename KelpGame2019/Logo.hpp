#pragma once
#include "BaseScene.hpp"
#include "DxLib.h"
#include "InputController.hpp"


class Logo : public BaseScene
{
private:
	/// �摜

	int mD_teamLogo;		// ����̉摜
	int mD_dxlibLogo;		// dxlib�̉摜
	int mD_skip;
	int mD_Re;
	int mD_Okizari;
	int mD_Pazuru;
	int mD_Escape;

	int m_x;
	int m_y;
	int m_addX;
	int m_addY;
	int m_turnY;


	/// �V�[���J�ڂɊւ���

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

