#pragma once


//------------------------------------------------------------------------------------------
//����t�@�C��

#include "Skill.h"

class KAKUREMI :public Skill {
public:

	//--------------------------------------------------------------------------------------
	//�R���X�g���N�^
	KAKUREMI(tpr::Vector2 pos_, int angle);


	//--------------------------------------------------------------------------------------
	//�֐�

	void Active(tpr::Vector2 pos, float dire_x, float dire_y, CharaObj* p)override;

	void TurnOff(float deltatime)override;


	//--------------------------------------------------------------------------------------
	//�ϐ�

	int origin_img = 0;
	int origin_r = 0;
	int origin_speed = 0;

	int change_speed = 0;

	CharaObj* p = nullptr;

	int flame_count = 0;


	//--------------------------------------------------------------------------------------
	//���t���[���Ăяo��

	void Skill_UpDate(float deltatime)override;
	void Skill_Render(Camera* cam)override;
};