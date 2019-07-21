#pragma once
#include "BaseScene.hpp"
#include <random>


class Game : public BaseScene
{
private:
	int mD_backGroundDraw;					// �w�i�摜
	int mD_playerDraw;						// �v���C���[�摜
	int mD_chaserDraw;						// �ǂ���������̉摜
	int mD_garbageDraw;						// ��Q���摜
	int mD_underGroundDraw;					// ���摜

	const int m_mostMaxY = 1080 - 128;		// �v���C���[�̍ő�Œ�ӈʒu
	int m_playerHP;							// �v���C���[�̗̑�
	const int m_playerMaxHP = 256;

	int m_nowSpeed;							// ���݂̃X�s�[�h
	int m_lowNowSpeed;						// ���݂̃R���}�ȉ��̃X�s�[�h
	bool m_lowSpeedChange;					// �R���}�ȉ��̃X�s�[�h�̐��l�ϊ��^�C�~���O


public:
	Game();
	~Game();


	// �`��
	void Draw() override;

	// �v���Z�X
	void Process() override;
};

