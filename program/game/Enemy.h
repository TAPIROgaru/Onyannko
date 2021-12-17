#pragma once

//----------------------------------------------------------------------------------------------
//自作ファイル

#include "CharaObj.h"
#include "TPRlib/tpr_library.h"

//----------------------------------------------------------------------------------------------------
//クラスの前方宣言

class tpr::Astar;


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

	int search_range_palyer = 500;      //索敵範囲

	float bullet_direction_x = 0;       //弾を発射する向きX
	float bullet_direction_y = 0;       //弾を発射する向きY

	float angle = 0;                    //角度

	bool _fire = false;

	t2k::Vector3 prev_pos;              //1フレーム前の座標

	tpr::Astar* astar = nullptr;        //経路探索

	unsigned int flame_count = 0;       //フレームのカウント

	std::list<tpr::Node*> route;        //動くルート

	std::vector<tpr::Vector2_int> move_pos; //ワールド座標
	int move_count = 0;
	bool _astar_falg = true;

	tpr::Vector2 avo_dire;


	//------------------------------------------------------------------------------------------
	//毎フレーム呼び出し

	void Update(float deltatime) override;
	void Render(Camera* cam)     override;


	//------------------------------------------------------------------------------------------

};