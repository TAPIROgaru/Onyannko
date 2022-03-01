#pragma once

//----------------------------------------------------------------------------------------------------
//����t�@�C��

#include "Object.h"
#include "TPRlib/tpr_library.h"


//----------------------------------------------------------------------------------------------------

class Bullet :public Object {
public:

	//------------------------------------------------------------------------------------------------
	//�֐�

	Bullet(float, float, float, float, bool);
	Bullet(tpr::Vector2 pos, tpr::Vector2 dire, int img, bool _team, float speed, float scope, int r);

	void Move(float);
	bool isDelete();


	//------------------------------------------------------------------------------------------------
	//�ϐ�

	float scope = 1.0f;
	float count = 0;

	float speed = 6.0f;

	float direction_x = 0;
	float direction_y = 0;

	float angle = 0;

	t2k::Vector3 prve_pos;

	//------------------------------------------------------------------------------------------------
	//���t���[���Ăяo��

	void Update(float deltatime) override;
	void Render(Camera* cam)     override;


	//------------------------------------------------------------------------------------------------

};