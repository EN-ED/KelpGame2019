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
	/// クラスポインタ------------------------------
	BackGround* mp_backGround;
	Character* mp_character;
	Chaser* mp_chaser;
	std::vector<Garbage*> mp_garbage;


	/// 処理系--------------------------------------
	bool m_isFirstSpeedUp;			// ブラー処理のReplayInitを呼ぶためのもの

		// 今のシーン
	enum class NowMove { start, main, gameclear, gameover };
	NowMove m_nowMove;		// 今のシーンを保持

		// ファイル読み込み
	void FileLoad(std::string t_mapStr);
	int m_nowGameCorse;		// ファイルを読み込むコースを指定


	/// ゲーム開始前のアニメーション関係------------
	void FirstDraw();
	void FirstProcess();

	int m_firstFrameCount;				// 全体の動くフレームカウント

	int m_firstCharacterX;
	bool m_firstCharacterTurn;

	int m_firstBackGroundX;

	int m_firstchaserX;


	/// ゲーム中関係--------------------------------
	void MainDraw();
	void MainProcess();

	int mD_firstTimer[3];				// ゲーム開始直前の３カウント画像

	int m_maxLoad;						// ゴールまでの長さ
	float m_nowLoad;					// 今の位置


	/// ゲームオーバー関係--------------------------
	void GameOverDraw();
	void GameOverProcess();

	int mD_gameOver;					// ゲームオーバー画像
	int mD_overReset;					// やり直し画像
	int mD_overTitle;					// タイトルへ戻る画像

	int m_overFrame;				// UIをゆっくり表示させるためのカウント
	bool m_overGameReset;			// ゲームオーバーからやり直すを選択したかどうか


	/// ゲームクリア関係----------------------------
	void GameClearDraw();
	void GameClearProcess();

	int mD_gameClear;				// ゲームクリア画像
	int mD_clearOmake;				// クリアのおまけ画像

	int m_clearFrame;				// UIをゆっくり表示させるためのカウント


public:
	Game(int t_stageCorse);
	~Game();


	// 描画
	void Draw() override;

	// プロセス
	void Process() override;
};

