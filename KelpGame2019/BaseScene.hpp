#pragma once
#include "EffekseerForDXLib.h"
#include "InputKey.hpp"



// �V�[���̓���
enum class ESceneNumber
{
	LOGO, TITLE
};



// �S�̂ŕK�v�ȕϐ�
namespace BASICPARAM
{
	// ���O�̃V�[��
	extern ESceneNumber e_preScene;

	// ���݂̃V�[��
	extern ESceneNumber e_nowScene;
}


/*
���[�u�̑�{
*/
class BaseScene
{
protected:
	// �����I���t���b�O
	bool m_endFlag;


public:
	// �`��
	virtual void Draw() = 0;

	// �v���Z�X
	virtual void Process() = 0;


	// �����I�ɏI��������
	const bool& GetEnd() const { return m_endFlag; }
};