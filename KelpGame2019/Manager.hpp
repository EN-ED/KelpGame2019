#pragma once
#include "BaseScene.hpp"
#include "Logo.hpp"
#include "Title.hpp"
#include "Game.hpp"
#include "DxLib.h"
#include "Tutorial.hpp"



/*
ゲームの大本
*/
class Manager
{
private:
	BaseScene* p_baseMove;	// シーンの基底クラス

	// シーンを切り替える
	void SceneChange();


public:
	Manager();
	~Manager();


	// メインプロセス
	void Update();

	// 終了させる
	const bool GetEnd() const { return p_baseMove->GetEnd(); }
};