#pragma once


//------------------------------------------------------------------------------------------
//����t�@�C��

#include "Skill.h"

class BLINK :public Skill {
public:

	//--------------------------------------------------------------------------------------
	//�R���X�g���N�^

	BLINK(tpr::Vector2 pos_, int angle);

	//--------------------------------------------------------------------------------------
	//�֐�

	void Active(tpr::Vector2 pos, float dire_x, float dire_y, CharaObj* p)override;

	void TurnOff(float deltatime)override;

	//--------------------------------------------------------------------------------------
	//�ϐ�

	float move_amount = 64.0f;
	tpr::Vector2 pos;

	//--------------------------------------------------------------------------------------
	//���t���[���Ăяo��

	void Skill_UpDate(float deltatime)override;
	void Skill_Render(Camera* cam)override;
};