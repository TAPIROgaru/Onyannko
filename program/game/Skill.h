#pragma once


//----------------------------------------------------------------------------------------------
//自作ファイル

#include "Object.h"
#include "TPRlib/tpr_library.h"
#include "Camera.h"

class CharaObj;

class Skill :public Object {
public:

	virtual ~Skill() {};

	//------------------------------------------------------------------------------------------
	//関数

	bool isHit_Bullet();

	bool isHit_Enemy(tpr::Vector2 pos);

	virtual void Active(tpr::Vector2 pos, float dire_x, float dire_y, CharaObj* p) {};

	virtual void TurnOff(float deltatime) {};


	//------------------------------------------------------------------------------------------
	//変数

	int my_number;
	float cool_time_count = 0.0f;
	float cool_time = 0.0f;
	float count = 0.0f;
	int flame_count = 0;

	std::vector<int> skill_img;
	int scroll_img_close;
	int scroll_img_open;

	int angle;
	tpr::Vector2 dire;
	tpr::Vector2 pos_b;

	bool _active = false;
	bool _end_effect = false;
	bool _effect = false;

	//------------------------------------------------------------------------------------------
	//毎フレーム呼び出し

	virtual void Skill_UpDateMain(float deltatime, tpr::Vector2 pos_);
	virtual void Skill_UpDate(float deltatime) {}
	virtual void Skill_RenderMain(Camera* cam);
	virtual void Skill_RenderDebug(Camera* cam);
	virtual void Skill_Render(Camera* cam) {}


	//------------------------------------------------------------------------------------------
};