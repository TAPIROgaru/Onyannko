#pragma once


//------------------------------------------------------------------------------------------
//自作ファイル

#include "Skill.h"

class Bullet;


class TEPPO :public Skill {
public:

	//--------------------------------------------------------------------------------------
	//コンストラクタ
	TEPPO(tpr::Vector2 pos_, int angle);


	//--------------------------------------------------------------------------------------
	//関数

	void Active(tpr::Vector2 pos, float dire_x, float dire_y, CharaObj* p)override;

	void TurnOff(float deltatime)override;

	void isHit();


	//--------------------------------------------------------------------------------------
	//変数

	float speed = 7.0f;
	float scope = 0.7f;
	int damage = 2;

	Bullet* bp = nullptr;

	CharaObj* e_p = nullptr;

	//--------------------------------------------------------------------------------------
	//毎フレーム呼び出し

	void Skill_UpDate(float deltatime)override;
	void Skill_Render(Camera* cam)override;
};