#pragma once


//----------------------------------------------------------------------------------------------
//©ìƒtƒ@ƒCƒ‹

#include "TPRlib/tpr_library.h"

class Skill {
public:

	virtual ~Skill() {};

	//------------------------------------------------------------------------------------------
	//ŠÖ”


	//------------------------------------------------------------------------------------------
	//•Ï”

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