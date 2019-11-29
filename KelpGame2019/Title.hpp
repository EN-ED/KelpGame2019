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
	// �摜-------------------------------------------
	int mD_select;			// ����{�^���̐���
	int mD_back;			// �߂�{�^���̐���
	int mD_TitleLogo;		// �^�C�g�����S

	int mD_backGround;		// �w�i�摜


	// �w�i�摜�̏����n-------------------------------
	int m_backGroundAngle;	// �p�x


	// �^�C�g�����S�̏����n---------------------------
	int m_x, m_y;			// ���W
	double m_exRate;		// �傫��
	double m_add;			// �傫���̉��Z�l
	double m_angle;			// �p�x


	// �V�[���̏����n---------------------------------
		// �^�C�g���̃V�[��
	enum class Scene { one, two };

	Scene m_sceneChange;		// ���݂̃V�[��

	int m_sceneChangeCount;						// �V�[���̈ړ������܂ŃJ�E���g
	const int m_sceneChangeMaxCount = 20;		// �V�[���̈ړ��I���܂ł̃J�E���g�l

	int m_sceneSideDrawX;								// �V�[���ړ����̉��ړ��l�ione��two�𗼕��`�悷��j
	const int m_sceneTwoDefaultSideDrawX = 1920;		// �V�[���ړ����̉��ő�l

	int m_logoBlendValue;		// ���S�̓��ߒl


	// �V�[���P�����Ɋւ���摜-----------------------
	int mD_sceneOneStart;

	void SceneOneDraw();


	// �V�[���P�����Ɋւ��鏈��-----------------------
	int m_sceneOneStartBlendCount;		// �J�n�摜��傫�������菬�������鐔�l
	bool m_isBlendDownSwitch;			// �傫������̂�����������̂��ǂ���

	void SceneOneProcess();


	// �V�[���Q�����Ɋւ���摜-----------------------
	int mD_sceneTwoStart;
	int mD_sceneTwoEnd;

	void SceneTwoDraw();


	// �V�[���Q�����Ɋւ��鏈��-----------------------
		// �J�[�\���̈ʒu
	enum class TwoCursolArea { start, end, omakeOne, omakeTwo };
	TwoCursolArea m_cursolArea;		// �J�[�\���͂ǂ��ɂ��邩

	float m_sceneTwoFontBigCount;	// �I�����Ă���J�[�\����傫�������菬�������鐔�l
	bool m_isFontBigDownSwitch;		// �傫������̂�����������̂��ǂ���

	bool m_selectCommandLeft;	// �I���J�[�\�������ɂ��邩�ǂ���

	void SceneTwoProcess();


	// ���܂��P�Ɋւ���摜---------------------------
	int mD_omakeOne;


	// ���܂��P�Ɋւ��鏈��---------------------------
	int m_omakeOneCommandNumber;		// ���܂��P���o�����邽�߂̃R�}���h�������Ă��鐔
	int m_omakeOneAbleFrame;			// ���܂��P���o�������邽�߂̎��̃R�}���h�܂łɉ����Ă��Ȃ��t���[��
	bool m_omakeOneLeft;				// ���܂��P��I�����Ă��邩�ǂ���
	bool m_omakeOneOpen;				// ���܂��P���o�����������ǂ���


	// ���܂��Q�Ɋւ���摜---------------------------
	int mD_omakeTwo;


	// ���܂��Q�Ɋւ��鏈��---------------------------
	int m_omakeTwoCommandNumber;		// ���܂��Q���o�����邽�߂̃R�}���h�������Ă��鐔
	int m_omakeTwoAbleFrame;			// ���܂��Q���o�������邽�߂̎��̃R�}���h�܂łɉ����Ă��Ȃ��t���[��
	bool m_omakeTwoLeft;				// ���܂��Q��I�����Ă��邩�ǂ���
	bool m_omakeTwoOpen;				// ���܂��Q���o�����������ǂ���


public:
	Title();
	~Title();


	// �`��
	void Draw() override;

	// �v���Z�X
	void Process() override;
};

