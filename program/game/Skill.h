#pragma once


//----------------------------------------------------------------------------------------------
//自作ファイル

#include "TPRlib/tpr_library.h"

class Skill {
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
};