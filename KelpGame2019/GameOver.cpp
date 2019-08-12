#include "GameOver.hpp"
#include "DxLib.h"
#include "InputKey.hpp"



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
GameOver::GameOver()
{
	mD_movieDraw = LoadGraph("media\\movieLogo.mp4");
	PlayMovieToGraph(mD_movieDraw);

	m_endFlag = false;
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
GameOver::~GameOver()
{
	if (mD_movieDraw != -1) DeleteGraph(mD_movieDraw);
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void GameOver::Draw()
{
	DrawExtendGraph(960 - 480 - 900 * 2, 540 - 220 - 900, 960 + 480 + 900 * 2, 540 + 220 + 900, mD_movieDraw, false);		// �����\��

	DrawFormatString(0, 0, GetColor(255, 255, 255), "gameover");				// �Q�[���I�[�o�[�̃V�[�����ƕ\��

	DrawFormatString(800, 500, GetColor(255, 255, 255), "Z�L�[�Ń^�C�g���߂��");			// �^�C�g���ւ̈ړ��L�[��\��
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void GameOver::Process()
{
	// Z�L�[����������
	if (KeyData::Get(KEY_INPUT_Z) == 1)
	{
		BASICPARAM::e_nowScene = ESceneNumber::TITLE;				// TITLE�̃V�[���ֈڍs����
	}


	// ���悪�I�����Ă�����
	if (!GetMovieStateToGraph(mD_movieDraw))
	{
		SeekMovieToGraph(mD_movieDraw, 0);		// �ʒu���ŏ��ɖ߂�
		PlayMovieToGraph(mD_movieDraw);			// ������Đ�����
	}
}
