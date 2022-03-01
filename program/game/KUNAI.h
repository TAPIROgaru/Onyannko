#pragma once


//------------------------------------------------------------------------------------------
//����t�@�C��

#include "Skill.h"
#include "TPRlib/HitPoints.h"

class KUNAI :public Skill {
public:

	//--------------------------------------------------------------------------------------
	//�R���X�g���N�^
	KUNAI(tpr::Vector2 pos_, int angle);


	//--------------------------------------------------------------------------------------
	//�֐�

	void Active(tpr::Vector2 pos, float dire_x, float dire_y, CharaObj* p)override;

	void TurnOff(float deltatime)override;

	void isHit();

	void Move();


	//--------------------------------------------------------------------------------------
	//�ϐ�

	int hitpoint = 5;
	float speed = 8.0f;
	int damage = 1;

	tpr::Hitpoints hp = tpr::Hitpoints(25, 5);


	//--------------------------------------------------------------------------------------
	//���t���[���Ăяo��

	void Skill_UpDate(float deltatime)override;
	void Skill_Render(Camera* cam)override;
};