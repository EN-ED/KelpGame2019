#pragma once
#include "BaseScene.hpp"
#include "DxLib.h"
#include "InputController.hpp"
#include "SoundProcess.hpp"



/*
�^�C�g���̃V�[���̑�{
*/
class Title : public BaseScene
{
private:
	int m_backGroundColor;		// �w�i�F

	enum class Scene { one, two };		// �V�[��

	Scene m_sceneChange;		// ���݂̃V�[��

	int m_sceneChangeCount;		// �V�[���̈ړ������܂ŃJ�E���g

	const int m_sceneChangeMaxCount = 20;		// �V�[���̈ړ��I���܂ł̃J�E���g�l

	int m_sceneSideDrawX;			// �V�[���ړ����̉��ړ��l�ione��two�𗼕��`�悷��j

	const int m_sceneTwoDefaultSideDrawX = 1920;		// �V�[���ړ����̉��ő�l

	int mD_select;

	int mD_back;

	int mD_TitleLogo;

	int m_x;
	int m_y;
	double m_exRate;
	double m_add;
	double m_angle;

	int mD_backGround;
	int m_backGroundAngle;


	/// �V�[���P�����Ɋւ���

	int mD_sceneOneStart;		// �ŏ��̃X�^�[�g����

	int m_sceneOneStartBlendCount;		// �ŏ��̕����̓��ߒl
	bool m_isBlendDownSwitch;			// �����̓��ߒl�������邩�ǂ���

	void SceneOneDraw();		// �V�[���P�̕`��
	void SceneOneProcess();		// �V�[���P�̃v���Z�X


	/// �V�[���Q�����Ɋւ���

	int mD_sceneTwoStart;		// 2�Ԗڂ̃X�^�[�g����
	int mD_sceneTwoEnd;			// 2�Ԗڂ̏I������

	enum class TwoCursolArea { start, end, omakeOne, omakeTwo };		// �J�[�\���̈ʒu

	TwoCursolArea m_cursolArea;			// �J�[�\���̈ʒu���ǂ��ɂ��邩

	float m_sceneTwoFontBigCount;		// �J�[�\�����������Ă��镶���̃T�C�Y�l
	bool m_isFontBigDownSwitch;			// �����̃T�C�Y�l�������邩�ǂ���

	void SceneTwoDraw();			// �V�[���Q�̕`��
	void SceneTwoProcess();			// �V�[���Q�̃v���Z�X


	/// ���܂��P
	int m_omakeOneCommandNumber;
	int m_omakeOneAbleFrame;
	bool m_omakeOneLeft;
	bool m_omakeOneOpen;
	int mD_omakeOne;


	/// ���܂��Q
	int m_omakeTwoCommandNumber;
	int m_omakeTwoAbleFrame;
	bool m_omakeTwoLeft;
	bool m_omakeTwoOpen;
	int mD_omakeTwo;

	int m_logoBlendValue;
	bool m_selectCommandLeft;


public:
	Title();
	~Title();


	// �`��
	void Draw() override;

	// �v���Z�X
	void Process() override;
};

