#include "Manager.hpp"
#include "DxLib.h"
#include "InputKey.hpp"
#include "InputController.hpp"
#include "SoundProcess.hpp"


/// --------------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// ウィンドウサイズを決める
	int winWidth = 1920;
	int winHeight = 1080;
	int bitColor = 32;


#ifdef _DEBUG
	SetOutApplicationLogValidFlag(TRUE);	// ログテキスト出力する
#elif NDEBUG
	SetOutApplicationLogValidFlag(FALSE);	// ログテキスト出力しない
#endif


	SetWindowText("滑れ！石鹸くん！");					// メインウインドウのウインドウタイトルを変更する
	SetBackgroundColor(0, 0, 0);			// 背景色を白に変更
	ChangeWindowMode(TRUE);						// ウィンドウズモードにさせる


	SetGraphMode(winWidth, winHeight, bitColor);			// 画面サイズ設定
	GetDefaultState(&winWidth, &winHeight, &bitColor);		// デフォルトウィンドウ値を得る
	SetWindowSize(winWidth, winHeight);						// デフォルトウィンドウサイズに合わせてゲームサイズを変更
	SetWindowIconID(333);

	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)
	{
		return -1;			// エラーが起きたら直ちに終了
	}


	SetDrawScreen(DX_SCREEN_BACK);	// 背景描画
	SetMouseDispFlag(FALSE);		// マウスカーソルを非表示にする

	SoundProcess::Init();

	KeyData::UpDate();

	PadData::SetPadNum();
	PadData::SetDedZone(20000, -20000, 20000, -20000, 20000, -20000, 20000, -20000);
	PadData::UpDate();
	
	Manager m_manager = Manager();

	
	// メインループ
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && !KeyData::IsCheckEnd() && !PadData::IsCheckEnd() && !m_manager.GetEnd())
	{
		KeyData::UpDate();
		PadData::UpDate();


		m_manager.Update();
	}

	// 削除
	m_manager.~Manager();
	SoundProcess::Release();
	DxLib_End();		// DXライブラリの後始末


	return 0;
}