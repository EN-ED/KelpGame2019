#pragma once
#include "BaseScene.hpp"
#include "Logo.hpp"
#include "Title.hpp"
#include "Game.hpp"
#include "DxLib.h"
#include "Tutorial.hpp"



/*
�Q�[���̑�{
*/
class Manager
{
private:
	BaseScene* p_baseMove;	// �V�[���̊��N���X

	// �V�[����؂�ւ���
	void SceneChange();


public:
	Manager();
	~Manager();


	// ���C���v���Z�X
	void Update();

	// �I��������
	const bool GetEnd() const { return p_baseMove->GetEnd(); }
};