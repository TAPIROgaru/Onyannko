#pragma once


//------------------------------------------------------------------------------------------
//����t�@�C��

#include "Skill.h"

class TORINOKO :public Skill {
public:

	//--------------------------------------------------------------------------------------
	//�R���X�g���N�^
	TORINOKO(tpr::Vector2 pos_, int angle);

	//--------------------------------------------------------------------------------------
	//�֐�

	void Active(tpr::Vector2 pos, float dire_x, float dire_y, CharaObj* p)override;

	void TurnOff(float deltatime)override;


	//--------------------------------------------------------------------------------------
	//�ϐ�


	//--------------------------------------------------------------------------------------
	//���t���[���Ăяo��

	void Skill_UpDate(float deltatime)override;
	void Skill_Render(Camera* cam)override;
};