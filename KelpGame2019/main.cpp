#include "InputKey.hpp"


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


	SetWindowText("KelpGame2019");					// メインウインドウのウインドウタイトルを変更する
	SetBackgroundColor(0, 0, 0);			// 背景色を白に変更
	ChangeWindowMode(TRUE);						// ウィンドウズモードにさせる
	SetEnableXAudioFlag(TRUE);					// XAudioを使用するようにする


	SetGraphMode(winWidth, winHeight, bitColor);			// 画面サイズ設定
	GetDefaultState(&winWidth, &winHeight, &bitColor);		// デフォルトウィンドウ値を得る
	SetWindowSize(winWidth, winHeight);						// デフォルトウィンドウサイズに合わせてゲームサイズを変更


	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)
	{
		return -1;			// エラーが起きたら直ちに終了
	}


	// Effekseerを初期化する。引数には画面に表示する最大パーティクル数を設定する。
	if (Effkseer_Init(500) == -1)
	{
		DxLib_End();
		return -1;
	}


	// フルスクリーンウインドウの切り替えでリソースが消えるのを防ぐ。
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);


	Effekseer_Set2DSetting(1920, 1080);	// 2Dエフェクトの最大範囲を設定


	SetDrawScreen(DX_SCREEN_BACK);	// 背景描画
	SetMouseDispFlag(FALSE);		// マウスカーソルを非表示にする


	KeyData::UpDate();


	int movieDraw = LoadGraph("media\\movieLogo.mp4");
	int dxlibLogo = LoadGraph("media\\DxLogo.jpg");

	int nowLogoNumber = 0;
	int movieZoom = 0;
	int logoTransTime = 0;


	
	// メインループ
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && KeyData::CheckEnd())
	{
		KeyData::UpDate();

		if (logoTransTime < 50)
		{
			SetDrawBright(logoTransTime * 5, logoTransTime * 5, logoTransTime * 5);
		}
		else if(logoTransTime > 250)
		{
			SetDrawBright(250 - ((logoTransTime - 250) * 5), 250 - ((logoTransTime - 250) * 5), 250 - ((logoTransTime - 250) * 5));
		}
		if (nowLogoNumber == 0)
		{
			logoTransTime++;
			DrawGraph(960 - 120, 540 - 120, dxlibLogo, false);
			if (logoTransTime >= 300)
			{
				logoTransTime = 0;
				nowLogoNumber = 1;
				PlayMovieToGraph(movieDraw);
			}
		}
		else if (nowLogoNumber == 1)
		{
			logoTransTime++;
			movieZoom += 3;
			DrawExtendGraph(960 - 480 - movieZoom * 2, 540 - 220 - movieZoom, 960 + 480 + movieZoom * 2, 540 + 220 + movieZoom, movieDraw, false);

			if (logoTransTime >= 300)
			{
				logoTransTime = 0;
				nowLogoNumber = 0;
				movieZoom = 0;
				SeekMovieToGraph(movieDraw, 0);
				PauseMovieToGraph(movieDraw);
			}
		}
	}

	PauseMovieToGraph(movieDraw);

	DeleteGraph(movieDraw);

	// 削除
	Effkseer_End();		// Effekseerを終了する
	DxLib_End();		// DXライブラリの後始末


	return 0;
}