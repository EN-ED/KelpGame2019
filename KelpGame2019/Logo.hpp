#pragma once
#include "BaseScene.hpp"


class Logo : public BaseScene
{
private:
	/// �摜

	int mD_movieDraw;		// ����̉摜
	int mD_dxlibLogo;		// dxlib�̉摜


	/// �V�[���J�ڂɊւ���

	int m_nowLogoNumber;	// ���݂̃��S
	int m_movieZoom;		// ����̃Y�[���^�C��
	int m_logoTransTime;	// ���S�̑J�ڎ���

public:
	Logo();
	~Logo();


	// �`��
	void Draw() override;

	// �v���Z�X
	void Process() override;
};

