#pragma once


//------------------------------------------------------------------------------------------
//����t�@�C��

#include "Skill.h"

class Bullet;


class TEPPO :public Skill {
public:

	//--------------------------------------------------------------------------------------
	//�R���X�g���N�^
	TEPPO(tpr::Vector2 pos_, int angle);


	//--------------------------------------------------------------------------------------
	//�֐�

	void Active(tpr::Vector2 pos, float dire_x, float dire_y, CharaObj* p)override;

	void TurnOff(float deltatime)override;

	void isHit();


	//--------------------------------------------------------------------------------------
	//�ϐ�

	float speed = 7.0f;
	float scope = 0.7f;
	int damage = 2;

	Bullet* bp = nullptr;

	CharaObj* e_p = nullptr;

	//--------------------------------------------------------------------------------------
	//���t���[���Ăяo��

	void Skill_UpDate(float deltatime)override;
	void Skill_Render(Camera* cam)override;
};