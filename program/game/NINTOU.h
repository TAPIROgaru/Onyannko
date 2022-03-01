#pragma once


//------------------------------------------------------------------------------------------
//����t�@�C��

#include "Skill.h"

class NINTOU :public Skill {
public:

	//--------------------------------------------------------------------------------------
	//�R���X�g���N�^
	NINTOU(tpr::Vector2 pos_, int angle);


	//--------------------------------------------------------------------------------------
	//�֐�

	void Active(tpr::Vector2 pos, float dire_x, float dire_y, CharaObj* p)override;

	void TurnOff(float deltatime)override;


	//--------------------------------------------------------------------------------------
	//�ϐ�

	CharaObj* p_p = nullptr;
	CharaObj* e_p = nullptr;

	float moving_distance = 7.0f;
	int origin_defense = 0;

	bool _move = false;


	//--------------------------------------------------------------------------------------
	//���t���[���Ăяo��

	void Skill_UpDate(float deltatime)override;
	void Skill_Render(Camera* cam)override;
};