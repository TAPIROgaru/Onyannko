#pragma once

//----------------------------------------------------------------------------------------------
//自作ファイル

#include "CharaObj.h"
#include "Astar.h"


//----------------------------------------------------------------------------------------------

class Enemy :public CharaObj {
public:

	//------------------------------------------------------------------------------------------
	//関数

	Enemy(int);
	~Enemy();


	void Move(float);       //操作
	void LoadStatus(int);   //プレイヤーステータスのロード
	void FireBullet(float); //弾を撃つ
	void FindPlayer(float); //プレイヤーとの位置関係


	//------------------------------------------------------------------------------------------
	//変数

	int search_range_palyer = 750; //索敵範囲
	int search_range_bullet = 800;

	float bullet_direction_x = 0;  //弾を発射する向き
	float bullet_direction_y = 0;

	float angle = 0;               //角度

	tpr::Astar* astar = nullptr;  //経路探索


	//------------------------------------------------------------------------------------------
	//毎フレーム呼び出し

	void Update(float deltatime) override;
	void Render(Camera* cam)     override;


	//------------------------------------------------------------------------------------------

};