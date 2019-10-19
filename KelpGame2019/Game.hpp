#pragma once
#include "BaseScene.hpp"
#include "BackGround.hpp"
#include "Character.hpp"
#include "Chaser.hpp"
#include "DxLib.h"
#include "InputKey.hpp"
#include "BlurScreen.hpp"
#include "Garbage.hpp"

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>


class Game : public BaseScene
{
private:
	BackGround* mp_backGround;
	Character* mp_character;
	Chaser* mp_chaser;

	bool m_isFirstSpeedUp;

	std::vector<Garbage*> mp_garbage;

	void MainDraw();
	void MainProcess();

	void GameOverDraw();
	void GameOverProcess();

	void GameClearDraw();
	void GameClearProcess();

	void TutorialDraw();
	void TutorialProcess();

	enum class NowMove { tutorial, main, gameclear, gameover };
	NowMove m_nowMove;

	void FileLoad(std::string t_mapStr);


public:
	Game(int t_stageCorse);
	~Game();


	// ï`âÊ
	void Draw() override;

	// ÉvÉçÉZÉX
	void Process() override;
};

