#include "Manager.hpp"



/// ---------------------------------------------------------------------------------------
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
		SoundProcess::Play(SoundProcess::E_BGM::title);
		delete p_baseMove;
		p_baseMove = nullptr;
		SetDrawBright(255, 255, 255);

		p_baseMove = new Title();
		break;


		// チュートリアル
	case ESceneNumber::TUTORIAL:
		SoundProcess::Play(SoundProcess::E_BGM::tutorial);
		delete p_baseMove;
		p_baseMove = nullptr;

		p_baseMove = new Tutorial();
		break;


		// ゲーム本編
	case ESceneNumber::GAME:
		SoundProcess::Play(SoundProcess::E_BGM::mainLoop);
		delete p_baseMove;
		p_baseMove = nullptr;

		p_baseMove = new Game(1);
		break;


		// ゲーム本編やり直す
	case ESceneNumber::GAMERETURN:
		BASICPARAM::e_preScene = ESceneNumber::GAME;
		BASICPARAM::e_nowScene = ESceneNumber::GAME;
		SoundProcess::Play(SoundProcess::E_BGM::mainLoop);
		delete p_baseMove;
		p_baseMove = nullptr;

		p_baseMove = new Game(1);
		break;


		// おまけ１
	case ESceneNumber::OMAKEONE:
		SoundProcess::Play(SoundProcess::E_BGM::mainLoop);
		delete p_baseMove;
		p_baseMove = nullptr;

		p_baseMove = new Game(2);
		break;


		// ゲーム本編やり直す
	case ESceneNumber::OMAKEONERETURN:
		BASICPARAM::e_preScene = ESceneNumber::OMAKEONE;
		BASICPARAM::e_nowScene = ESceneNumber::OMAKEONE;
		SoundProcess::Play(SoundProcess::E_BGM::mainLoop);
		delete p_baseMove;
		p_baseMove = nullptr;

		p_baseMove = new Game(2);
		break;


		// ゲーム本編
	case ESceneNumber::OMAKETWO:
		SoundProcess::Play(SoundProcess::E_BGM::mainLoop);
		delete p_baseMove;
		p_baseMove = nullptr;

		p_baseMove = new Game(3);
		break;


		// ゲーム本編やり直す
	case ESceneNumber::OMAKETWORETURN:
		BASICPARAM::e_preScene = ESceneNumber::OMAKETWO;
		BASICPARAM::e_nowScene = ESceneNumber::OMAKETWO;
		SoundProcess::Play(SoundProcess::E_BGM::mainLoop);
		delete p_baseMove;
		p_baseMove = nullptr;

		p_baseMove = new Game(3);
		break;


	default:
		break;
	}
}



/// ---------------------------------------------------------------------------------------
Manager::Manager()
{
#ifdef _DEBUG
	BASICPARAM::e_preScene = ESceneNumber::GAME;
	BASICPARAM::e_nowScene = ESceneNumber::GAME;

	p_baseMove = nullptr;
	p_baseMove = new Game(1);
#elif NDEBUG
	BASICPARAM::e_preScene = ESceneNumber::LOGO;
	BASICPARAM::e_nowScene = ESceneNumber::LOGO;

	p_baseMove = nullptr;
	p_baseMove = new Logo();
#endif


	switch (BASICPARAM::e_nowScene)
	{
	case ESceneNumber::LOGO:
		break;

	case ESceneNumber::TITLE:
		SoundProcess::Play(SoundProcess::E_BGM::title);
		break;

	case ESceneNumber::TUTORIAL:
		SoundProcess::Play(SoundProcess::E_BGM::tutorial);
		break;

	case ESceneNumber::GAME:
		SoundProcess::Play(SoundProcess::E_BGM::mainLoop);
		break;

	case ESceneNumber::GAMERETURN:
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



/// ---------------------------------------------------------------------------------------
Manager::~Manager()
{
	if (p_baseMove != nullptr) delete p_baseMove;
}



/// ---------------------------------------------------------------------------------------
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
		// シーンを変える
		SceneChange();


		SoundProcess::BGMLoop();


		// 直前のシーンと現在のシーンを同じにする
		BASICPARAM::e_preScene = BASICPARAM::e_nowScene;
	}
}