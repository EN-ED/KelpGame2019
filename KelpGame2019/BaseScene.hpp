#pragma once



// シーンの動き
enum class ESceneNumber
{
	LOGO, TITLE, GAME, OMAKEONE, OMAKETWO, TUTORIAL, GAMERETURN
};



// 全体で必要な変数
namespace BASICPARAM
{
	// 直前のシーン
	extern ESceneNumber e_preScene;

	// 現在のシーン
	extern ESceneNumber e_nowScene;
}


/*
ムーブの大本
*/
class BaseScene
{
protected:
	// 強制終了フラッグ
	bool m_endFlag = false;


public:
	virtual ~BaseScene() {};

	// 描画
	virtual void Draw() = 0;

	// プロセス
	virtual void Process() = 0;


	// 強制的に終了させる
	const bool& GetEnd() const { return m_endFlag; }
};