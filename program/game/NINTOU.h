#pragma once


//------------------------------------------------------------------------------------------
//自作ファイル

#include "Skill.h"

class NINTOU :public Skill {
public:

	//--------------------------------------------------------------------------------------
	//コンストラクタ
	NINTOU(tpr::Vector2 pos_, int angle);


	//--------------------------------------------------------------------------------------
	//関数

	void Active(tpr::Vector2 pos, float dire_x, float dire_y, CharaObj* p)override;

	void TurnOff(float deltatime)override;


	//--------------------------------------------------------------------------------------
	//変数

	CharaObj* p_p = nullptr;
	CharaObj* e_p = nullptr;

	float moving_distance = 7.0f;
	int origin_defense = 0;

	bool _move = false;


	//--------------------------------------------------------------------------------------
	//毎フレーム呼び出し

	void Skill_UpDate(float deltatime)override;
	void Skill_Render(Camera* cam)override;
};