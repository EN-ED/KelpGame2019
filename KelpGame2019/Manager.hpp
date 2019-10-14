#pragma once
#include "BaseScene.hpp"
#include "Logo.hpp"
#include "Title.hpp"
#include "Game.hpp"
#include "GameOver.hpp"
#include "DxLib.h"



/*
�Q�[���̑�{
*/
class Manager
{
private:
	/// �V�[���Ɋւ���-------------------------------------------

	// �V�[���̊��N���X
	BaseScene* p_baseMove;

	// �V�[����؂�ւ���
	void SceneChange();


public:
	// �R���X�g���N�^
	Manager();

	// �f�X�g���N�^
	~Manager();


	// ���C���v���Z�X
	void Update();

	// �I��������
	const bool& GetEnd() const { return p_baseMove->GetEnd(); }
};