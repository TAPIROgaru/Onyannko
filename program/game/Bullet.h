#pragma once

//----------------------------------------------------------------------------------------------------
//自作ファイル

#include "Object.h"
#include "TPRlib/tpr_library.h"


//----------------------------------------------------------------------------------------------------

class Bullet :public Object {
public:

	//------------------------------------------------------------------------------------------------
	//関数

	Bullet(float, float, float, float, bool);
	Bullet(tpr::Vector2 pos, tpr::Vector2 dire, int img, bool _team, float speed, float scope, int r);

	void Move(float);
	bool isDelete();


	//------------------------------------------------------------------------------------------------
	//変数

	float scope = 1.0f;
	float count = 0;

	float speed = 6.0f;

	float direction_x = 0;
	float direction_y = 0;

	float angle = 0;

	t2k::Vector3 prve_pos;

	//------------------------------------------------------------------------------------------------
	//毎フレーム呼び出し

	void Update(float deltatime) override;
	void Render(Camera* cam)     override;


	//------------------------------------------------------------------------------------------------

};