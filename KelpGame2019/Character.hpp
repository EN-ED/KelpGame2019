#pragma once
#include "DxLib.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <string>
#include "SoundProcess.hpp"
#include "InputController.hpp"



/*
�Ό��N�i��l���j
*/
class Character
{
public:
	// �ǂ̏�Q���ɓ������������肷�邽�߂̗�
	enum class EHitGarbageID { doro, mizutamari, sekiyu, none };


private:
	/// �摜------------------------------------------------
	int mD_playerArray[20];				// �ʏ�̐Ό��N
	int mD_playerDirtArray[20];			// �D�ɐZ�������Ό��N
	int mD_playerWaterArray[20];			// ���ɐZ�������Ό��N
	int mD_playerSpeedArray[20];		// �������Ă���Ό��N

	int mD_speedUpDescription;			// �����ł��邱�Ƃ�������摜

	int mD_jumpDescription;				// �W�����v�{�^����������摜

	int mD_speedNumber[10];				// ���x�̉摜
	int mD_speedComma;					// ���x�̃R���}�摜



	/// �摜�̏����n----------------------------------------
	const int m_playerDrawNum = 20;				// �摜�̃R�}��
	const int m_playerDrawAnimSpeed = 6;		// �摜�̃R�}�𑗂鑬�x�̍ő�
	int m_playerDrawAnimCount;					// �摜�̃R�}�𑗂鑬�x�̃J�E���g

	const int m_runFirstPlayerAnim = m_playerDrawAnimSpeed * 13;	// �}���������Ƃ��̐Ό��N�̃t���[���R�}

	const int m_jumpFirstPlayerAnim = m_playerDrawAnimSpeed * 8;	// �W�����v�����Ƃ��̐Ό��N�̃t���[���R�}



	/// ���W�̏����n----------------------------------------
	const int m_playerSize = 192;			// �v���C���[�̉摜�T�C�Y
	const int m_mostMaxY = 1080 - 128;		// �v���C���[�̍ő�Œ�ӈʒu
	const int m_defaultX = 284;				// �v���C���[�̊X���W

	int m_playerX, m_playerY;		// �Ό��N�̍��W
	int m_prePlayerX, m_prePlayerY;	// �Ό��N�̒��O���W

		// �Ό��N�̏�Ԃ�������
	enum class ESTATE{ normal, speedUp, speedMAX, speedDown, damageHit, heal, doroDamageHit };
	ESTATE m_nowState;				// ���݂̏��
	
		// ���W����
	void PositionProcess();



	/// ���R�k�������n-----------------------------------------
	int m_smallCount;					// ���Ԍo�߂ŐΌ��N���������Ȃ�J�E���g
	const int m_smallCountTime = 30;	// �������Ȃ�^�C�~���O

	float m_smallSpeed;					// �Ό��N�̏k�����Ă��鐔�l
	const float m_smallValue = 0.005f;	// �k�����鐔�l



	/// �_���[�W�����n------------------------------------------
	int m_damageCount;						// �_���[�W���󂯂����o�̃J�E���g
	const int m_damageMaxCount = 30;		// �_���[�W���󂯂����o�̃J�E���g�̍ő�

	bool m_isDamageHit;						// �_���[�W���󂯂����ǂ���

	float m_preDamageMAXSpeed;				// �_���[�W�ɂ�錸���̍ő�l
	const float m_damageDownSpeed = -1.25f;	// �_���[�W�ɂ�錸���̉��Z�l

	const float m_damageSmallValue = 0.05f;	// �_���[�W�ɂ��k�����鐔�l

		// �_���[�W����
	void HitGarbageProcess();



	/// ��Q�������n-------------------------------------------
	bool m_isHitGarbage;					// ��Q���ɓ����������ǂ���

		/// ������Q��ID�ɑ΂��ĉ��x��������Ȃ��悤�ɂ��邽�߂̕ϐ��Q
	int m_hitGarbageID;						// �z�u����Ă����Q��ID�̂����ǂ�ɂ���������
	int m_preHitGarbageID;					// ���O�ɓ���������Q��ID�͂ǂꂩ

	EHitGarbageID m_hitGarbageObjectID;		// �ǂ̏�Q���ɓ���������



	/// �񕜏����n--------------------------------------------
	int m_healCount;						// �_���[�W���󂯂����o�̃J�E���g
	const int m_healMaxCount = 15;		// �_���[�W���󂯂����o�̃J�E���g�̍ő�

	bool m_nowHeal;							// �񕜏�Q���i�����j�ɓ����������ǂ���



	/// �X�s�[�h�����n-----------------------------------------
	float m_nowSpeed;						// ���݂̃X�s�[�h
	const float m_playerMaxSpeed = 70;		// �v���C���[�̍ő呬�x

	int m_nowSpeedThirdDigit;		// ���݂̑��x�̎O���ڂ̐���
	int m_nowSpeedSecondDigit;		// ���݂̑��x�̓񌅖ڂ̐���
	int m_nowSpeedFirstDigit;		// ���݂̑��x�̓񌅖ڂ̐���
	int m_nowSpeedDecimalPoint;		// ���݂̑��x�̏����_�̐���

		// �X�s�[�h����
	void SpeedProcess();



	/// �X�s�[�h�̉��������n------------------------------------
	bool m_isNowSpeedUp;				// ���������ǂ���

	int m_speedUpChargeCount;			// �����\�܂ł̎���
	const int m_speedUpChargeMax = 420;	// �����\�܂ł̍ő厞��

	float m_addSpeed;						// ���Z���ɉ��Z�����X�s�[�h�l
	float m_speedUpCount;					// �������ő�ɂȂ�܂ł̎���
	const float m_speedUpCountTime = 1.0f;	// �������ő厞�ɂȂ�܂ł̕K�v����
	int m_speedMaxWaitCount;				// �����ő�l�̎��Ɏ������鎞��
	const int m_speedMaxWaitMaxCount = 40;	// �����ő�l�̎��Ɏ������鎞�Ԃ̍ő�(2�Ŋ���؂�Ȃ��Ə��������

		// �X�s�[�h��������
	void SpeedUpProcess();



	/// �W�����v�����n------------------------------------------
	int m_playerUnderY;		// �v���C���[�̑�����Y���W
	
	bool m_isGroundFlag;	// �n�ʂɐG��Ă邩
	bool m_isJumpFlag;		// �W�����v���Ă��邩
	bool m_isLongJump;		// �������W�����v��

	int m_jumpPower;		// �W�����v��
	int m_gravityPower;		// �d��

	const int m_jumpMaxPower = 120;		// �W�����v�͂̍ő�l
	const int m_jumpMinPower = 24;		// �W�����v�͂̍ŏ��l

	const int m_jumpAddPower = 16;		// �W�����v���̏㏸�l
	const int m_jumpGravityEnergy = 8;	// �W�����v���̌����l

	bool m_isFlyDamageHit;		// �W�����v���Ƀ_���[�W���󂯂����ǂ���

		// �W�����v����
	void PlayerJump();



public:
	Character();
	~Character();


	// �`��
	void Draw();

	// �u���[�����`��
	void BlurDraw();

	// ����
	void Process();


	// �Q�[���J�n���̃A�j���[�V�����̕`��
	void FirstDraw(int t_x, int t_y, bool t_turn);

	// �Q�[���J�n���̃A�j���[�V�����̏���
	void FirstProcess();


	// ��Q������������
	void HitGarbageNow(const int t_garbageID, const EHitGarbageID t_garbageObjectID);


	const bool GetIsSpeedUp() const;

	const float GetSpeed() const;
	
	const float GetDefaultMAXSpeed() const;

	const int GetAreaX() const;
	
	const int GetAreaY() const;
	
	const float GetSize() const;
	
	const bool GetNowDamage() const;
	
	const bool GetNowHeal() const;
	
	const float GetSmallSpeed() const;
};

