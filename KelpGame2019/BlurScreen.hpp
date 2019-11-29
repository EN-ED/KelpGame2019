#pragma once
#ifndef _BLURSCREEN_HPP
#define _BLURSCREEN_HPP
#include "DxLib.h"



/*
�u���[����
*/
struct BlurScreen
{
private:
	int m_screen[2];									// �w�ʂɎg���X�N���[���摜
	int m_current;										// 2���̂ǂ̉摜���g���Ă��邩
	int m_alpha;										// ���ߒl
	int m_screenWidth, m_screenHeight;					// �X�N���[���̊e�傫��
	int m_offsetX1, m_offsetX2, m_offsetY1, offsetY2;	// �u���[�������������
	int m_notBlendDraw;									// ���t���[�������u���[���������Ȃ����߂̃J�E���g�ϐ�


public:
	BlurScreen() 
	{
		m_screen[0] = 0;
		m_screen[1] = 0;
		m_current = 0;
		m_alpha = 0;
		m_screenWidth = 0;
		m_screenHeight = 0;
		m_offsetX1 = 0;
		m_offsetX2 = 0; 
		m_offsetY1 = 0; 
		offsetY2 = 0; 
		m_notBlendDraw = 0;
	}
	~BlurScreen() {}


	// ������
	void Init(int t_alpha, int t_offsetX1, int t_offsetY1, int t_offsetX2, int t_offsetY2);

	// �u���[�������钼�O�Ɉ�񂾂��Ă�
	void ReplayInit();

	// ���
	void Release();

	// �u���[����������`��̒��O�ɒu��
	void PreRenderBlurScreen();

	// �u���[����������`��̌�ɒu��
	void PostRenderBlurScreen();
};

#endif // !_BLURSCREEN_HPP