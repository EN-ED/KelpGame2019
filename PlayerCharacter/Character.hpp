#pragma once
#include "DxLib.h"
#include "InputKey.hpp"


class Character
{
private:
	int mD_playerDraw;						// �v���C���[�摜
	const int m_playerSize = 128;			// �v���C���[�̉摜�T�C�Y

	const int m_mostMaxY = 1080 - 128;		// �v���C���[�̍ő�Œ�ӈʒu
	const int m_defaultX = 284;				// �v���C���[�̊X���W
	

	int m_damageCount;




	/// �X�s�[�h�֘A-------------------------------------------

	const int m_playerMaxSpeed = 70;			// �v���C���[�̍ő呬�x

	float m_nowSpeed;							// ���݂̃X�s�[�h

	float m_addSpeed;							// ���Z����X�s�[�h�l

	const float m_jumpDownSpeed = -1.25f;		// �W�����v���Ɍ������鐔�l

	int m_isSpeedUp;				// �������邩�ǂ���
	float m_speedUpCount;				// ��������������܂ł̎���

	int m_speedMaxWaitCount;		// �����ő�l�̎��Ɏ������鎞��

	const int m_speedMaxWaitMaxCount = 60;		// �����ő�l�̎��Ɏ������鎞�Ԃ̍ő�(2�Ŋ���؂�Ȃ��Ə��������

	int m_playerX;		// �v���C���[��X���W
	int m_playerY;		// �v���C���[��Y���W

	void SpeedProcess();
	/// --------------------------------------------------------


	/// �W�����v�֘A--------------------------------------------

	int m_playerUnderY;		// �v���C���[�̑�����Y���W

	bool m_isGroundFlag;	// �n�ʂɐG��Ă邩

	bool m_isJumpFlag;	// �W�����v���Ă��邩

	bool m_isLongJump;	// �������W�����v��

	int m_jumpPower;	// �W�����v��

	int m_gravityPower;	// �d��

	const int m_jumpMaxPower = 40;		// �W�����v�͂̍ő�l

	const int m_jumpMinPower = 10;		// �W�����v�͂̍ŏ��l

	void PlayerJump();
	/// --------------------------------------------------------



	/// �֌W�Ȃ�����
	int m_backGroundColorRed;			// �w�i�F��
	int m_backGroundColorGreen;			// �w�i�F��
	int m_backGroundColorBlue;			// �w�i�F��

	int m_backGroundSwitch;
	bool m_isBackGroundChange;




public:
	Character();
	~Character();


	// �`��
	void Draw();

	// �v���Z�X
	void Process();
};

