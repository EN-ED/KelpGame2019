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

