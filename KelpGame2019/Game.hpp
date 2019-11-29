#pragma once
#include "BaseScene.hpp"
#include "BackGround.hpp"
#include "Character.hpp"
#include "Chaser.hpp"
#include "DxLib.h"
#include "BlurScreen.hpp"
#include "Garbage.hpp"

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>



/*
�Q�[���̃V�[���̑�{
*/
class Game : public BaseScene
{
private:
	/// �N���X�|�C���^------------------------------
	BackGround* mp_backGround;
	Character* mp_character;
	Chaser* mp_chaser;
	std::vector<Garbage*> mp_garbage;


	/// �����n--------------------------------------
	bool m_isFirstSpeedUp;			// �u���[������ReplayInit���ĂԂ��߂̂���

		// ���̃V�[��
	enum class NowMove { start, main, gameclear, gameover };
	NowMove m_nowMove;		// ���̃V�[����ێ�

		// �t�@�C���ǂݍ���
	void FileLoad(std::string t_mapStr);
	int m_nowGameCorse;		// �t�@�C����ǂݍ��ރR�[�X���w��


	/// �Q�[���J�n�O�̃A�j���[�V�����֌W------------
	void FirstDraw();
	void FirstProcess();

	int m_firstFrameCount;				// �S�̂̓����t���[���J�E���g

	int m_firstCharacterX;
	bool m_firstCharacterTurn;

	int m_firstBackGroundX;

	int m_firstchaserX;


	/// �Q�[�����֌W--------------------------------
	void MainDraw();
	void MainProcess();

	int mD_firstTimer[3];				// �Q�[���J�n���O�̂R�J�E���g�摜

	int m_maxLoad;						// �S�[���܂ł̒���
	float m_nowLoad;					// ���̈ʒu


	/// �Q�[���I�[�o�[�֌W--------------------------
	void GameOverDraw();
	void GameOverProcess();

	int mD_gameOver;					// �Q�[���I�[�o�[�摜
	int mD_overReset;					// ��蒼���摜
	int mD_overTitle;					// �^�C�g���֖߂�摜

	int m_overFrame;				// UI���������\�������邽�߂̃J�E���g
	bool m_overGameReset;			// �Q�[���I�[�o�[�����蒼����I���������ǂ���


	/// �Q�[���N���A�֌W----------------------------
	void GameClearDraw();
	void GameClearProcess();

	int mD_gameClear;				// �Q�[���N���A�摜
	int mD_clearOmake;				// �N���A�̂��܂��摜

	int m_clearFrame;				// UI���������\�������邽�߂̃J�E���g


public:
	Game(int t_stageCorse);
	~Game();


	// �`��
	void Draw() override;

	// �v���Z�X
	void Process() override;
};

