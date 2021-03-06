#pragma once
#include "../library/t2klib.h"

//----------------------------------------------------------------------------------------------------
//自作ファイル

#include "Object.h"
#include "TPRlib/tpr_library.h"


//----------------------------------------------------------------------------------------------------

class Square : public Object {
public:

	//------------------------------------------------------------------------------------------------
	//関数

	//=====================================================
	//	コンストラクタ
	// 1. Vector3 描画座標
	// 2. int 画像データ
	//=====================================================
	Square(t2k::Vector3 start, int img);


	//------------------------------------------------------------------------------------------------
	//変数

	int img = 0;

	int size_w_ = 32;
	int size_h_ = 32;

	tpr::Quadrilateral* quad = nullptr;


	//------------------------------------------------------------------------------------------------
	//毎フレーム呼び出し

	void Update(float deltatime) override;
	void Render(Camera* camera) override;


	//------------------------------------------------------------------------------------------------
};