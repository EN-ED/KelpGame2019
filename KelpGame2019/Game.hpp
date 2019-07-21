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
	const int m_playerMaxHP = 1024;						// �v���C���[�̍ő�̗͒l
	const int m_playerHPdiv = m_playerMaxHP / 32;		// �v���C���[�̗̑͂ɉ����đ傫�������������邽�߂̏��Z�l
	const int m_playerMaxSpeed = 70;			// �v���C���[�̍ő呬�x

	int m_scrollX;

	int m_nowSpeed;							// ���݂̃X�s�[�h
	int m_lowNowSpeed;						// ���݂̃R���}�ȉ��̃X�s�[�h
	int m_speedChangeCount;					// �R���}�ȉ��̃X�s�[�h�̐��l�ϊ��^�C�~���O
	bool m_isSpeedChange;					// �R���}�ȉ��̃X�s�[�h�̐��l�ϊ��^�C�~���O

	void SpeedProcess();

	void PlayerJump();

	int m_playerX;		// �v���C���[��X���W

	const int m_playerMaxX = 180;		// �v���C���[�̂��炵��Z���W�̍ő�l

	const int m_maxMomentSpeed = 30;		// �v���C���[�̏u�ԓI�ɉ������̉��Z�ő�l

	const int m_playerHitHaleX = 20;		// �v���C���[���Ԃ����ĂЂ�񂾎���Z���W�̍ő�l

	const int m_haleDownMaxSpeed = 20;		// �v���C���[���Ԃ������Ƃ��̌����ő�l

	const int m_jumpMoveX = 3;				// �v���C���[�̃W�����v���ɏ����E�ɂ����悤�ɂ���Ƃ��̍ő�X�l

	/// �W�����v�֘A--------------------------------------------

	int m_playerY;	// �v���C���[��Y���W

	bool m_isGroundFlag;	// �n�ʂɐG��Ă邩

	bool m_isJumpFlag;	// �W�����v���Ă��邩

	bool m_isLongJump;	// �������W�����v��

	int m_jumpPower;	// �W�����v��

	int m_gravityPower;	// �d��

	bool m_isFallNow;	// �����Ă��邩�ǂ���

	int m_preY;	// ���O��Y���W

	const int m_jumpMaxPower = 50;		// �W�����v�͂̍ő�l

	const int m_jumpMinPower = 10;		// �W�����v�͂̍ŏ��l
	/// --------------------------------------------------------


public:
	Game();
	~Game();


	// �`��
	void Draw() override;

	// �v���Z�X
	void Process() override;
};

