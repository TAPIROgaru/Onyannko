#pragma once

//----------------------------------------------------------------------------------------------------
//����t�@�C��

#include "../Object.h"
#include "../TPRlib/tpr_library.h"


//----------------------------------------------------------------------------------------------------

class NINTOU :public Object {
public:

	//------------------------------------------------------------------------------------------------
	//�֐�

	NINTOU(tpr::Vector2 pos_, tpr::Vector2 dire_, bool _team_);

	void Move(float deltatime);
	bool isDelete();


	//------------------------------------------------------------------------------------------------
	//�ϐ�

	float scope = 1.0f;
	float count = 0;

	float speed = 3.0f;

	tpr::Vector2 dire;

	float angle = 0.0f;
	float exrate = 1.0f;

	t2k::Vector3 prve_pos;

	float size_x = 16.0f;
	float size_y = 4.0f;

	//------------------------------------------------------------------------------------------------
	//���t���[���Ăяo��

	void Update(float deltatime) override;
	void Render(Camera* cam)     override;


	//------------------------------------------------------------------------------------------------

};