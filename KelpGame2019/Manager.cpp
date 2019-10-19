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
		SetDrawBright(255, 255, 255);

		p_baseMove = new Title();
		SoundProcess::Play(SoundProcess::E_BGM::title);
		break;


		// ゲーム本編
	case ESceneNumber::GAME:
		delete p_baseMove;
		p_baseMove = nullptr;

		p_baseMove = new Game(1);
		SoundProcess::Play(SoundProcess::E_BGM::mainLoop);
		break;


		// おまけ１
	case ESceneNumber::OMAKEONE:
		delete p_baseMove;
		p_baseMove = nullptr;

		p_baseMove = new Game(2);
		SoundProcess::Play(SoundProcess::E_BGM::mainLoop);
		break;


		// ゲーム本編
	case ESceneNumber::OMAKETWO:
		delete p_baseMove;
		p_baseMove = nullptr;

		p_baseMove = new Game(3);
		SoundProcess::Play(SoundProcess::E_BGM::mainLoop);
		break;


	default:
		break;
	}
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
Manager::Manager()
{
	// 初期化
	BASICPARAM::e_preScene = ESceneNumber::LOGO;
	BASICPARAM::e_nowScene = ESceneNumber::LOGO;


	// メモリの初期化
	p_baseMove = nullptr;
	p_baseMove = new Logo();


	switch (BASICPARAM::e_nowScene)
	{
	case ESceneNumber::LOGO:
		break;

	case ESceneNumber::TITLE:
		SoundProcess::Play(SoundProcess::E_BGM::title);
		break;

	case ESceneNumber::GAME:
		SoundProcess::Play(SoundProcess::E_BGM::mainLoop);
		break;

	case ESceneNumber::OMAKEONE:
		SoundProcess::Play(SoundProcess::E_BGM::mainLoop);
		break;

	case ESceneNumber::OMAKETWO:
		SoundProcess::Play(SoundProcess::E_BGM::mainLoop);
		break;

	default:
		break;
	}
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


		SoundProcess::BGMLoop();
	}
	// 現在と直前のシーンが異なったら
	else
	{
		SoundProcess::BGMLoop();


		// シーンを変える
		SceneChange();


		// 直前のシーンと現在のシーンを同じにする
		BASICPARAM::e_preScene = BASICPARAM::e_nowScene;
	}
}