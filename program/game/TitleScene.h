#pragma once

//----------------------------------------------------------------------------------------------------
//自作ファイル

#include "Scene.h"



//----------------------------------------------------------------------------------------------------

class TitleScene :public Scene {
public:

	//------------------------------------------------------------------------------------------------
	//関数

	TitleScene();

	void ChangeMenuScene();


	//------------------------------------------------------------------------------------------------
	//変数

	int x1 = 480 - 200;
	int y1 = 400 - 50;
	int x2 = 480 + 200;
	int y2 = 400 + 50;
	

	//------------------------------------------------------------------------------------------------
	//毎フレーム呼び出し

	void Update(float deltatime) override;
	void Render(float deltatime) override;


	//------------------------------------------------------------------------------------------------

};