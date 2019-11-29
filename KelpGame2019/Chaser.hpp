#pragma once
#include "DxLib.h"
#include <string>



/*
�X�����o�̖{��
*/
class Chaser
{
private:
	/// �摜-----------------------------------------
	int mD_chaserArray[31];


	/// �摜�̏����n---------------------------------
	const int m_chaserArrayNum = 31;

	int m_chaserSpeedCount;
	int m_chasrArraySpeed;


	/// �����n---------------------------------------
	int m_chaserX;
	const int m_chaserDefaultX = 256 - 512;

	int m_chaserXAddValue;


public:
	Chaser();
	~Chaser();


	// �`��
	void Draw();

	// ����
	void Process();

	// �Q�[���J�n���̃A�j���[�V�����`��
	void FirstDraw(int t_x);

	// �Q�[���J�n���̃A�j���[�V��������
	void FirstProcess();


	// �v���C���[�̑��x���������ă`�F�C�T�[�̑��x�𒲐�����
	// @param (t_playerSpeed) �v���C���[�̍��̃X�s�[�h
	// @param (t_defaultMAXSpeed) �ʏ펞�̃v���C���[�̏o����ő�X�s�[�h
	void SetPlyayerSpeed(const float t_playerSpeed, const float t_defaultMAXSpeed);

	const int GetX() const;
};

