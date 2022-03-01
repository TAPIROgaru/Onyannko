#pragma once


//------------------------------------------------------------------------------------------
//����t�@�C��

#include "Skill.h"

class MAKIBISI :public Skill {
public:

	//--------------------------------------------------------------------------------------
	//�R���X�g���N�^
	MAKIBISI(tpr::Vector2 pos_, int angle);


	//--------------------------------------------------------------------------------------
	//�֐�

	void Active(tpr::Vector2 pos, float dire_x, float dire_y, CharaObj* p)override;

	void TurnOff(float deltatime)override;

	void isHit();


	//--------------------------------------------------------------------------------------
	//�ϐ�

	CharaObj* e_p = nullptr;
	float origin_speed = 0.0f;

	bool _hit = false;


	//--------------------------------------------------------------------------------------
	//���t���[���Ăяo��

	void Skill_UpDate(float deltatime)override;
	void Skill_Render(Camera* cam)override;
};