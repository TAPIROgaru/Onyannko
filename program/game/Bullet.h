#pragma once

//----------------------------------------------------------------------------------------------------
//自作ファイル

#include"Object.h"


//----------------------------------------------------------------------------------------------------

class Bullet :public Object {
public:

	//------------------------------------------------------------------------------------------------
	//関数

	Bullet();


	//------------------------------------------------------------------------------------------------
	//変数




	//------------------------------------------------------------------------------------------------
	//毎フレーム呼び出し

	void Update(float deltatime) override;
	void Render(Camera* cam)     override;


	//------------------------------------------------------------------------------------------------

};