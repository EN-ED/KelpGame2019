#pragma once
#include "DxLib.h"
#include "InputKey.hpp"


class Title
{
private:
	int m_backGroundColor;		// �w�i�F

	enum class Scene { one, two };

	Scene m_sceneChange;

	int m_sceneChangeCount;

	const int m_sceneChangeMaxCount = 20;

	int m_sceneSideDrawX;

	const int m_sceneTwoDefaultSideDrawX = 1920;


	int m_sceneOneStart;		// �ŏ��̃X�^�[�g����

	int m_sceneOneStartBlendCount;		// �ŏ��̕����̓��ߒl
	bool m_isBlendDownSwitch;

	void SceneOneDraw();
	void SceneOneProcess();



	int m_sceneTwoStart;		// 2�Ԗڂ̃X�^�[�g����
	int m_sceneTwoEnd;			// 2�Ԗڂ̏I������

	enum class TwoCursolArea { start, end };

	TwoCursolArea m_cursolArea;			// �J�[�\���̈ʒu

	float m_sceneTwoFontBigCount;		// �ŏ��̕����̃T�C�Y�l
	bool m_isFontBigDownSwitch;

	void SceneTwoDraw();
	void SceneTwoProcess();


public:
	Title();
	~Title();


	// �`��
	void Draw();

	// �v���Z�X
	void Process();
};

