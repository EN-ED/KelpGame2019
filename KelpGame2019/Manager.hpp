#pragma once
#include "BaseScene.hpp"
#include "Logo.hpp"
#include "Title.hpp"
#include "Game.hpp"
#include "GameOver.hpp"
#include "DxLib.h"



/*
ゲームの大本
*/
class Manager
{
private:
	/// シーンに関する-------------------------------------------

	// シーンの基底クラス
	BaseScene* p_baseMove;

	// シーンを切り替える
	void SceneChange();


public:
	// コンストラクタ
	Manager();

	// デストラクタ
	~Manager();


	// メインプロセス
	void Update();

	// 終了させる
	const bool& GetEnd() const { return p_baseMove->GetEnd(); }
};