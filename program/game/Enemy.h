#pragma once

//----------------------------------------------------------------------------------------------
//自作ファイル

#include "CharaObj.h"
#include "Astar.h"
#include "Node.h"


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

	int search_range_palyer = 750;    //索敵範囲
	int search_range_bullet = 800;    //弾の認識範囲

	float bullet_direction_x = 0;     //弾を発射する向きX
	float bullet_direction_y = 0;     //弾を発射する向きY

	float angle = 0;                  //角度

	t2k::Vector3 prev_pos;            //1フレーム前の座標

	tpr::Astar* astar = nullptr;      //経路探索

	unsigned int flame_count = 0;     //フレームのカウント

	std::list<tpr::Node*> route;      //動くルート

	std::list<tpr::Vector2> move_pos; //ワールド座標


	//------------------------------------------------------------------------------------------
	//毎フレーム呼び出し

	void Update(float deltatime) override;
	void Render(Camera* cam)     override;


	//------------------------------------------------------------------------------------------

};