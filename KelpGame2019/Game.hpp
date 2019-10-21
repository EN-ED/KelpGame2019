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
ゲームのシーンの大本
*/
class Game : public BaseScene
{
private:
	BackGround* mp_backGround;
	Character* mp_character;
	Chaser* mp_chaser;

	bool m_isFirstSpeedUp;

	std::vector<Garbage*> mp_garbage;

	void FirstDraw();
	void FirstProcess();

	void MainDraw();
	void MainProcess();

	void GameOverDraw();
	void GameOverProcess();

	void GameClearDraw();
	void GameClearProcess();

	enum class NowMove { start, main, gameclear, gameover };
	NowMove m_nowMove;

	void FileLoad(std::string t_mapStr);

	int m_firstCharacterX;
	bool m_firstCharacterTurn;
	int m_firstFrameCount;
	int m_firstBackGroundX;
	int m_firstchaserX;

	int m_firstTimer[3];

	int mD_gameClear;
	int mD_clearOmake;

	int m_clearFrame;

	int mD_gameOver;
	int mD_overReset;
	int mD_overTitle;

	int m_overFrame;

	bool m_overGameReset;

	int m_maxLoad;
	float m_nowLoad;



public:
	Game(int t_stageCorse);
	~Game();


	// 描画
	void Draw() override;

	// プロセス
	void Process() override;
};

