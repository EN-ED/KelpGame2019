#include "Manager.hpp"



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Manager::SceneChange()
{
	// ���̃V�[��
	switch (BASICPARAM::e_nowScene)
	{
		// ���S
	case ESceneNumber::LOGO:
		delete p_baseMove;
		p_baseMove = nullptr;

		p_baseMove = new Logo();
		break;


		// �^�C�g��
	case ESceneNumber::TITLE:
		SoundProcess::Play(SoundProcess::E_BGM::title);
		delete p_baseMove;
		p_baseMove = nullptr;
		SetDrawBright(255, 255, 255);

		p_baseMove = new Title();
		break;


		// �Q�[���{��
	case ESceneNumber::GAME:
		delete p_baseMove;
		p_baseMove = nullptr;

		p_baseMove = new Game();
		break;


		// �Q�[���I�[�o�[
	case ESceneNumber::GAMEOVER:
		delete p_baseMove;
		p_baseMove = nullptr;

		p_baseMove = new GameOver();
		break;


	default:
		break;
	}
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
Manager::Manager()
{
	// ������
	BASICPARAM::e_preScene = ESceneNumber::TITLE;
	BASICPARAM::e_nowScene = ESceneNumber::TITLE;


	// �������̏�����
	p_baseMove = nullptr;
	p_baseMove = new Title();


	switch (BASICPARAM::e_nowScene)
	{
	case ESceneNumber::LOGO:
		break;

	case ESceneNumber::TITLE:
		//SoundProcess::Play(SoundProcess::E_BGM::title);
		break;

	case ESceneNumber::GAME:
		break;

	case ESceneNumber::GAMEOVER:
		break;

	default:
		break;
	}
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
Manager::~Manager()
{
	// �V�[���{�̂̍폜
	delete p_baseMove;
	p_baseMove = nullptr;
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Manager::Update()
{
	// ���݂̃V�[���ƒ��O�̃V�[���������Ƃ�
	if (BASICPARAM::e_nowScene == BASICPARAM::e_preScene)
	{
		// �Q�[���̕`��Ɋւ���
		p_baseMove->Draw();


		// �Q�[���̃v���Z�X�Ɋւ���
		p_baseMove->Process();


		switch (BASICPARAM::e_nowScene)
		{
		case ESceneNumber::LOGO:
			break;

		case ESceneNumber::TITLE:
			SoundProcess::BGMLoop(true);
			break;

		case ESceneNumber::GAME:
			break;

		case ESceneNumber::GAMEOVER:
			break;

		default:
			break;
		}
	}
	// ���݂ƒ��O�̃V�[�����قȂ�����
	else
	{
		switch (BASICPARAM::e_nowScene)
		{
		case ESceneNumber::LOGO:
			break;

		case ESceneNumber::TITLE:
			break;

		case ESceneNumber::GAME:
			SoundProcess::BGMLoop(false);
			break;

		case ESceneNumber::GAMEOVER:
			break;

		default:
			break;
		}


		// �V�[����ς���
		SceneChange();


		// ���O�̃V�[���ƌ��݂̃V�[���𓯂��ɂ���
		BASICPARAM::e_preScene = BASICPARAM::e_nowScene;
	}
}