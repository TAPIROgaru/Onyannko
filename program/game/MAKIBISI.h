#pragma once


//------------------------------------------------------------------------------------------
//自作ファイル

#include "Skill.h"

class MAKIBISI :public Skill {
public:

	//--------------------------------------------------------------------------------------
	//コンストラクタ
	MAKIBISI(tpr::Vector2 pos_, int angle);


	//--------------------------------------------------------------------------------------
	//関数

	void Active(tpr::Vector2 pos, float dire_x, float dire_y, CharaObj* p)override;

	void TurnOff(float deltatime)override;

	void isHit();


	//--------------------------------------------------------------------------------------
	//変数

	CharaObj* e_p = nullptr;
	int origin_speed = 0;

	bool _hit = false;


	//--------------------------------------------------------------------------------------
	//毎フレーム呼び出し

	void Skill_UpDate(float deltatime)override;
	void Skill_Render(Camera* cam)override;
};