#pragma once


//----------------------------------------------------------------------------------------------------
//自作ファイル

#include "Skill.h"

class SHOTGUN :public Skill {
public:

	//------------------------------------------------------------------------------------------------
	//コンストラクタ
	SHOTGUN(tpr::Vector2 pos_, int angle);

	//------------------------------------------------------------------------------------------------
	//関数

	void Active(tpr::Vector2 pos, float dire_x, float dire_y)override;
};