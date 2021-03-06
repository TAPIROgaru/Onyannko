#pragma once

//----------------------------------------------------------------------------------------------------
//自作ファイル

#include "CharaObj.h"
#include "Scroll.h"


//----------------------------------------------------------------------------------------------------

class Player :public CharaObj {
public:

	//------------------------------------------------------------------------------------------------
	//関数

	Player();
	~Player();

	void Move(float);       //操作
	void LoadStatus();      //プレイヤーステータスのロード
	void FireBullet(float); //弾を撃つ
	void ShootDirection();  //発射する向き


	//------------------------------------------------------------------------------------------------
	//変数
	
	float bullet_direction_x = 0; //弾を発射する向き
	float bullet_direction_y = 0;

	float magnitude = 0;          //単位ベクトル

	float angle = 0;              //角度

	int mouse_img = 0;

	//------------------------------------------------------------------------------------------------
	//毎フレーム呼び出し

	void Update(float deltatime) override;
	void Render(Camera* cam)     override;


	//------------------------------------------------------------------------------------------------
};