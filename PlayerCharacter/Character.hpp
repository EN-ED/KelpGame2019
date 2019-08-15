#pragma once


class Character
{
private:
	const int m_playerDrawNum = 20;
	int mD_playerArray[20];

	const int m_playerDrawAnimSpeed = 6;
	int m_playerDrawAnimCount;

	const int m_playerSize = 192;			// �v���C���[�̉摜�T�C�Y

	const int m_mostMaxY = 1080 - 128;		// �v���C���[�̍ő�Œ�ӈʒu
	const int m_defaultX = 284;				// �v���C���[�̊X���W


	void PositionProcess();
	

	/// �_���[�W�֘A--------------------------------------------

	int m_damageCount;						// �_���[�W���󂯂����o�̃J�E���g

	const int m_damageMaxCount = 16;		// �_���[�W���󂯂����o�̃J�E���g�̍ő�

	int mD_playerDamageDraw;				// �_���[�W���o�p�̉摜

	bool m_isDamageHit;						// �_���[�W���󂯂����ǂ���

	void DamageProcess();
	/// --------------------------------------------------------


	/// �X�s�[�h�֘A-------------------------------------------

	const int m_playerMaxSpeed = 70;			// �v���C���[�̍ő呬�x

	float m_nowSpeed;							// ���݂̃X�s�[�h

	float m_addSpeed;							// ���Z����X�s�[�h�l

	const float m_jumpDownSpeed = -1.25f;		// �W�����v���Ɍ������鐔�l

	int m_isSpeedUp;				// �������邩�ǂ���
	float m_speedUpCount;				// ��������������܂ł̎���

	int m_speedMaxWaitCount;		// �����ő�l�̎��Ɏ������鎞��

	const int m_speedMaxWaitMaxCount = 40;		// �����ő�l�̎��Ɏ������鎞�Ԃ̍ő�(2�Ŋ���؂�Ȃ��Ə��������

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

