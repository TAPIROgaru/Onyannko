#pragma once


//----------------------------------------------------------------------------------------------------
//自作ファイル

#include "Skill.h"

class TEPPO :public Skill {
public:

	//------------------------------------------------------------------------------------------------
	//コンストラクタ
	TEPPO(tpr::Vector2 pos_, int angle);


	//------------------------------------------------------------------------------------------------
	//関数

	void Active(tpr::Vector2 pos, float dire_x, float dire_y, CharaObj* p)override;
};