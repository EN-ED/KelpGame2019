#include "Manager.hpp"



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Manager::SceneChange()
{
	// 今のシーン
	switch (BASICPARAM::e_nowScene)
	{
		// ロゴ
	case ESceneNumber::LOGO:
		delete p_baseMove;
		p_baseMove = nullptr;

		p_baseMove = new Logo();
		break;


		// タイトル
	case ESceneNumber::TITLE:
		delete p_baseMove;
		p_baseMove = nullptr;
		/*SetDrawBright(255, 255, 255);*/

		p_baseMove = new Title();
		break;


	default:
		break;
	}
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
Manager::Manager()
{
	// 初期化
	BASICPARAM::e_preScene = ESceneNumber::TITLE;
	BASICPARAM::e_nowScene = ESceneNumber::TITLE;


	// メモリの初期化
	p_baseMove = nullptr;
	p_baseMove = new Logo();
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
Manager::~Manager()
{
	// シーン本体の削除
	delete p_baseMove;
	p_baseMove = nullptr;
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Manager::Update()
{
	// 現在のシーンと直前のシーンが同じとき
	if (BASICPARAM::e_nowScene == BASICPARAM::e_preScene)
	{
		// ゲームの描画に関する
		p_baseMove->Draw();


		// ゲームのプロセスに関する
		p_baseMove->Process();
	}
	// 現在と直前のシーンが異なったら
	else
	{
		// シーンを変える
		SceneChange();


		// 直前のシーンと現在のシーンを同じにする
		BASICPARAM::e_preScene = BASICPARAM::e_nowScene;
	}
}