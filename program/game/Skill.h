#pragma once


//----------------------------------------------------------------------------------------------
//自作ファイル

#include "Object.h"
#include "TPRlib/tpr_library.h"
#include "Camera.h"

class Skill :public Object {
public:

	virtual ~Skill() {};

	//------------------------------------------------------------------------------------------
	//関数


	//------------------------------------------------------------------------------------------
	//変数

	int my_number;
	float count = 0;
	float cool_time;
	bool _active = false;

	std::vector<int> skill_img;
	int scroll_img_close;
	int scroll_img_open;

	int angle;

	virtual void Active(tpr::Vector2 pos, float dire_x, float dire_y) {};

	//------------------------------------------------------------------------------------------
	//毎フレーム呼び出し

	virtual void Update(float deltatime, tpr::Vector2 pos_) {};
	virtual void Render(Camera* cam) {};


	//------------------------------------------------------------------------------------------
};