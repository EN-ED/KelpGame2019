#pragma once
#include "DxLib.h"



#ifndef _INPUTCONTROLLER_H
#define _INPUTCONTROLLER_H
namespace PadStick
{
	const int XINPUT_LEFT_TRIGGER = 0;
	const int XINPUT_RIGHT_TRIGGER = 1;
	const int  XINPUT_LEFT_THUMB_X = 2;
	const int  XINPUT_LEFT_THUMB_Y = 3;
	const int  XINPUT_RIGHT_THUMB_X = 4;
	const int  XINPUT_RIGHT_THUMB_Y = 5;

	const int  XINPUT_THUMB_MAX = 32767;
	const int  XINPUT_THUMB_MIN = -32768;

	const int XINPUT_THUMB_PLUS = 0;
	const int XINPUT_THUMB_MINUS = 4;
}
#endif // !_INPUTCONTROLLER_H



// ゲームパッドの入力状態
class PadData {
	static int button[4][16];		// ゲームパッドの入力状態格納用変数
	static int stick[4][6];			// ゲームパッドのスティック関連の入力状態収納用変数
	static int stickCheck[4][8];	// ゲームパッドのスティックの入力状態収納用変数の最大までの倒しチェック

	// ゲームパッドのスティックのデッドゾーン数値を保存
	static short thumbLX_DeadMAX;
	static short thumbLX_DeadMIN;
	static short thumbLY_DeadMAX;
	static short thumbLY_DeadMIN;
	static short thumbRX_DeadMAX;
	static short thumbRX_DeadMIN;
	static short thumbRY_DeadMAX;
	static short thumbRY_DeadMIN;

	static XINPUT_STATE input[4];	// ゲームパッドのナンバー
	static __int8 padNum;			// 繋がってるゲームパッドの数

public:
	PadData();
	~PadData();

	static void SetPadNum();																			// 接続されてるゲームパッドを確認
	static void SetDedZone(short thumbLX_MAX, short thumbLX_MIN, short thumbLY_MAX, short thumbLY_MIN
		, short thumbRX_MAX, short thumbRX_MIN, short thumbRY_MAX, short thumbRY_MIN);					// デッドゾーンの設定
	static void UpDate();																				// ゲームパッドの入力の状態更新
	static int Get(int code, int padNum);																// ゲームパッドの入力状態取得
	static int GetStick(int code, int padNum);															// ゲームパッドのスティックの入力状態取得
	static int GetStickCheck(int code, int padNum, bool plus);														// ゲームパッドのスティックの押し倒し入力状態取得
	static __int8 GetPadNum();																			// 接続されてるゲームパッドの数
	static bool CheckEnd();																				// 強制終了
};
