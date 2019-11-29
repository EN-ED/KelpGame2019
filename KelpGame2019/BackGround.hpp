#pragma once
#include "DxLib.h"


/*
�Q�[�����̔w�i�̖{��
*/
class BackGround
{
private:
	/// �摜-----------------------------------
	int mD_backGround;			// �w�i�摜
	int mD_underGround;			// ���摜
	
	int m_areaX;				// �X�N���[���ł̍��W
	int m_speed;				// �X�N���[���̑��x


public:
	/// @param (t_stageCorse) ���X�e�[�W�Ȃ̂�
	BackGround(int t_stageCorse);
	~BackGround();


	// �`��
	void Draw();

	// ����
	void Process();

	// �L�����N�^�[�̑��x����X�N���[���X�s�[�h��ݒ�
	// @param (t_speed) �L�����N�^�[�̑��x
	void SetSpeed(const float t_speed);
};

