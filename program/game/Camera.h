#pragma once
#include "../library/t2klib.h"
#include "DxLib.h"


//----------------------------------------------------------------------------------------------------
//自作ファイル



//----------------------------------------------------------------------------------------------------

class Camera {
public:

	//------------------------------------------------------------------------------------------------
	//関数

	Camera();



	//------------------------------------------------------------------------------------------------
	//変数


	//座標
	t2k::Vector3 pos = { 0,0,0 };


	//------------------------------------------------------------------------------------------------
	//毎フレーム呼び出し

	void update(float,t2k::Vector3);
	void render();

	//------------------------------------------------------------------------------------------------
};