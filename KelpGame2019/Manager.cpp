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


		// �`���[�g���A��
	case ESceneNumber::TUTORIAL:
		SoundProcess::Play(SoundProcess::E_BGM::tutorial);
		delete p_baseMove;
		p_baseMove = nullptr;

		p_baseMove = new Tutorial();
		break;


		// �Q�[���{��
	case ESceneNumber::GAME:
		SoundProcess::Play(SoundProcess::E_BGM::mainLoop);
		delete p_baseMove;
		p_baseMove = nullptr;

		p_baseMove = new Game(1);
		break;


		// �Q�[���{�҂�蒼��
	case ESceneNumber::GAMERETURN:
		BASICPARAM::e_preScene = ESceneNumber::GAME;
		BASICPARAM::e_nowScene = ESceneNumber::GAME;
		SoundProcess::Play(SoundProcess::E_BGM::mainLoop);
		delete p_baseMove;
		p_baseMove = nullptr;

		p_baseMove = new Game(1);
		break;


		// ���܂��P
	case ESceneNumber::OMAKEONE:
		SoundProcess::Play(SoundProcess::E_BGM::mainLoop);
		delete p_baseMove;
		p_baseMove = nullptr;

		p_baseMove = new Game(2);
		break;


		// �Q�[���{��
	case ESceneNumber::OMAKETWO:
		SoundProcess::Play(SoundProcess::E_BGM::mainLoop);
		delete p_baseMove;
		p_baseMove = nullptr;

		p_baseMove = new Game(3);
		break;


	default:
		break;
	}
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
Manager::Manager()
{
	// ������
	BASICPARAM::e_preScene = ESceneNumber::LOGO;
	BASICPARAM::e_nowScene = ESceneNumber::LOGO;


	// �������̏�����
	p_baseMove = nullptr;
	p_baseMove = new Logo();


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



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
Manager::~Manager()
{
	// �V�[���{�̂̍폜
	if (p_baseMove != nullptr) delete p_baseMove;
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


		SoundProcess::BGMLoop();
	}
	// ���݂ƒ��O�̃V�[�����قȂ�����
	else
	{
		// �V�[����ς���
		SceneChange();


		SoundProcess::BGMLoop();


		// ���O�̃V�[���ƌ��݂̃V�[���𓯂��ɂ���
		BASICPARAM::e_preScene = BASICPARAM::e_nowScene;
	}
}