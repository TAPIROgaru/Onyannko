#pragma once


//------------------------------------------------------------------------------------------
//����t�@�C��

#include "Skill.h"

class KAGINAWA :public Skill {
public:

	//--------------------------------------------------------------------------------------
	//�R���X�g���N�^

	KAGINAWA(tpr::Vector2 pos_, int angle);


	//--------------------------------------------------------------------------------------
	//�֐�

	void Active(tpr::Vector2 pos, float dire_x, float dire_y, CharaObj* p)override;

	void TurnOff(float deltatime)override;

	bool isHit();


	//--------------------------------------------------------------------------------------
	//�ϐ�

	float throw_speed = 8.0f;
	float pull_speed = throw_speed * 1.5;
	tpr::Line* line = nullptr;
	CharaObj* p = nullptr;
	CharaObj* e_p = nullptr;
	t2k::Vector3 origin_pos;
	int r = 16;

	bool _hit = false;


	//--------------------------------------------------------------------------------------
	//���t���[���Ăяo��

	void Skill_UpDate(float deltatime)override;
	void Skill_Render(Camera* cam)override;
};