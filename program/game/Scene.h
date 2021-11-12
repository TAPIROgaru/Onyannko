#pragma once

#include "../library/t2klib.h"
#include "DxLib.h"
#include <list>


//----------------------------------------------------------------------------------------------------
//自作ファイル

#include "Camera.h"


//----------------------------------------------------------------------------------------------------

class Scene {
public:

	//------------------------------------------------------------------------------------------------
	//関数

	virtual ~Scene() {};

	//------------------------------------------------------------------------------------------------
	//変数

	bool _switch = false;

	int img_back = 0;


	//------------------------------------------------------------------------------------------------
	//毎フレーム呼び出し

	virtual void Update(float deltatime) {};
	virtual void Render(float deltatime) {};


	//------------------------------------------------------------------------------------------------
};