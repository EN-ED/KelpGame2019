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
		delete p_baseMove;
		p_baseMove = nullptr;
		/*SetDrawBright(255, 255, 255);*/

		p_baseMove = new Title();
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
	p_baseMove = new Logo();
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
	}
	// ���݂ƒ��O�̃V�[�����قȂ�����
	else
	{
		// �V�[����ς���
		SceneChange();


		// ���O�̃V�[���ƌ��݂̃V�[���𓯂��ɂ���
		BASICPARAM::e_preScene = BASICPARAM::e_nowScene;
	}
}