#pragma once


//------------------------------------------------------------------------------------------
//自作ファイル

#include "Skill.h"
#include "TPRlib/HitPoints.h"

class KUNAI :public Skill {
public:

	//--------------------------------------------------------------------------------------
	//コンストラクタ
	KUNAI(tpr::Vector2 pos_, int angle);


	//--------------------------------------------------------------------------------------
	//関数

	void Active(tpr::Vector2 pos, float dire_x, float dire_y, CharaObj* p)override;

	void TurnOff(float deltatime)override;

	void isHit();

	void Move();


	//--------------------------------------------------------------------------------------
	//変数

	static constexpr int MAX_HP = 4;
	int hitpoint = MAX_HP;
	float speed = 8.0f;
	int damage = 1;

	tpr::Hitpoints hp = tpr::Hitpoints(25, 5);


	//--------------------------------------------------------------------------------------
	//毎フレーム呼び出し

	void Skill_UpDate(float deltatime)override;
	void Skill_Render(Camera* cam)override;
};