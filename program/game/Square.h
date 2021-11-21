#pragma once
#include "../library/t2klib.h"

//----------------------------------------------------------------------------------------------------
//自作ファイル

#include "Object.h"
#include "Camera.h"


//----------------------------------------------------------------------------------------------------

class Square : public Object {
public:

	//------------------------------------------------------------------------------------------------
	//関数

	//=====================================================
	//	コンストラクタ
	// 1. Vector3 描画座標
	// 2. int 画像データ
	// 3. 侵入できるかどうか
	// 　 できるなら2 できないなら3
	//=====================================================
	Square(t2k::Vector3, int, int);


	//------------------------------------------------------------------------------------------------
	//変数

	int img = 0;

	int size_w_ = 16;
	int size_h_ = 16;

	//------------------------------------------------------------------------------------------------
	//マスのデータ

	int    status;
	Square* open_bp = nullptr;
	int    est_cost;
	int    act_cost;
	int    score;
	int    type;

	//------------------------------------------------------------------------------------------------
	//ステータス

	enum {

		OPEN,
		CLOSE,
		YES,
		NO,
		START,
		GOAL
	};


	//------------------------------------------------------------------------------------------------
	//毎フレーム呼び出し

	void Update(float deltatime) override;
	void Render(Camera* camera) override;


	//------------------------------------------------------------------------------------------------
};