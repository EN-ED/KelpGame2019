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
	const int m_playerMaxHP = 512;						// �v���C���[�̍ő�̗͒l
	const int m_playerHPdiv = m_playerMaxHP / 32;		// �v���C���[�̗̑͂ɉ����đ傫�������������邽�߂̏��Z�l
	const int m_playerMaxSpeed = 70;			// �v���C���[�̍ő呬�x

	int m_scrollX;

	int m_nowSpeed;							// ���݂̃X�s�[�h
	int m_lowNowSpeed;						// ���݂̃R���}�ȉ��̃X�s�[�h
	int m_speedChangeCount;					// �R���}�ȉ��̃X�s�[�h�̐��l�ϊ��^�C�~���O
	bool m_isSpeedChange;					// �R���}�ȉ��̃X�s�[�h�̐��l�ϊ��^�C�~���O

	void SpeedProcess();

public:
	Game();
	~Game();


	// �`��
	void Draw() override;

	// �v���Z�X
	void Process() override;
};

