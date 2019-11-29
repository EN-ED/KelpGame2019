#pragma once
#ifndef _SOUNDPROCESS_HPP
#define _SOUNDPROCESS_HPP
#include "DxLib.h"



/*
サウンド全て
*/
namespace SoundProcess
{
	enum class E_SE
	{
		jump, speedUp, slip, selectCancel, selectDo, gameClear, gameOver, debuff, catchTouyu, none
	};

	enum class E_BGM
	{
		title, main, mainLoop, tutorial, none
	};


	void Init();

	void Release();

	void Play(const E_SE number);

	void Play(const E_BGM number);

	void BGMLoop();
}


#endif // !_SOUNDPROCESS_HPP