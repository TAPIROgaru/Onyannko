#pragma once


//------------------------------------------------------------------------------------------
//自作ファイル

#include "Skill.h"

class SHOTGUN :public Skill {
public:

	//--------------------------------------------------------------------------------------
	//コンストラクタ
	SHOTGUN(tpr::Vector2 pos_, int angle);

	//--------------------------------------------------------------------------------------
	//関数

	void Active(tpr::Vector2 pos, float dire_x, float dire_y, CharaObj* p)override;

	void TurnOff(float deltatime)override;


	//--------------------------------------------------------------------------------------
	//変数

	float speed = 4.0f;
	float scope = 0.8f;

	//--------------------------------------------------------------------------------------
	//毎フレーム呼び出し

	void Skill_UpDate(float deltatime)override;
	void Skill_Render(Camera* cam)override;
};