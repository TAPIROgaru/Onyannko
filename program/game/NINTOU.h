#pragma once


//----------------------------------------------------------------------------------------------------
//自作ファイル

#include "Skill.h"

class NINTOU :public Skill {

	//------------------------------------------------------------------------------------------------
	//コンストラクタ
	NINTOU();


	//------------------------------------------------------------------------------------------------
	//関数

	void Active(tpr::Vector2 pos, float dire_x, float dire_y)override;
};