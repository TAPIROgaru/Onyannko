#pragma once


//------------------------------------------------------------------------------------------
//自作ファイル

#include "Skill.h"

class KAKUREMI :public Skill {
public:

	//--------------------------------------------------------------------------------------
	//コンストラクタ
	KAKUREMI(tpr::Vector2 pos_, int angle);


	//--------------------------------------------------------------------------------------
	//関数

	void Active(tpr::Vector2 pos, float dire_x, float dire_y, CharaObj* p)override;

	void TurnOff(float deltatime)override;


	//--------------------------------------------------------------------------------------
	//変数

	int origin_img = 0;
	int origin_r = 0;
	int origin_speed = 0;

	int change_speed = 0;

	CharaObj* p = nullptr;

	int flame_count = 0;


	//--------------------------------------------------------------------------------------
	//毎フレーム呼び出し

	void Skill_UpDate(float deltatime)override;
	void Skill_Render(Camera* cam)override;
};