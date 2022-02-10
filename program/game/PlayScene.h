#pragma once
#include <unordered_map>
#include "../library/math.h"

//----------------------------------------------------------------------------------------------------
//自作ファイル

#include "Scene.h"

#include "Object.h"
#include "CharaObj.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Square.h"
#include "TPRlib/tpr_library.h"


//----------------------------------------------------------------------------------------------------

class PlayScene :public Scene {
public:

	//------------------------------------------------------------------------------------------------
	//関数

	PlayScene();

	void Delete();

	void SavePlayer();

	void Start(float);

	void isOver();

	void Init();

	void LoadBuckGround();

	void isHit_bullet();


	//------------------------------------------------------------------------------------------------
	//他ソースファイル等から使う関数

	
	//=======================================================
	// 弾生成
	// 1. 初期座標
	// 2. x角度
	// 3. y角度
	// 4. 陣営
	//=======================================================
	void MakeBullet(t2k::Vector3, float, float, bool);


	//=======================================================
	// カメラ座標を考慮したマウス座標を取得できる関数
	// 
	// return マウス座標
	//=======================================================
	t2k::Vector3 GetMousePosition();


	//=======================================================
	// カメラ座標を考慮した座標を取得できる関数(Vector3)
	// 1. 修正するVector座標
	// 
	// return 修正されたVector座標
	//=======================================================
	t2k::Vector3 FixPositionVector(t2k::Vector3);


	//=======================================================
	// カメラ座標を考慮した座標を取得できる関数(Vector2)
	// 1. 修正するVector座標
	// 
	// return 修正されたVector座標
	//=======================================================
	tpr::Vector2 FixPositionVector(tpr::Vector2);


	//=======================================================
	// 壁の当たり判定(補正あり)
	// 1. Vector座標
	// 2. 1フレーム前の座標
	// 3. 円の半径
	//=======================================================
	void isHit_Wall(t2k::Vector3& pos, t2k::Vector3 prev_pos, float r);


	//=======================================================
	// 壁の当たり判定(補正無し)
	// 1. Vector座標
	// 2. 円の半径
	// 
	// return true 当たってる　false 当たってない
	//=======================================================
	bool isHit_Wall(t2k::Vector3 pos, float r);


	//=======================================================
	// 点と円の当たり判定
	// 1. 点のVector座標
	// 2. 円のVector座標
	// 3. 円の半径
	// 
	// return true 当たってる　false 当たってない
	//=======================================================
	inline bool isHit_DotAndCircle(t2k::Vector3 dot_pos, t2k::Vector3 cir_pos, float r);


	//=======================================================
	//	円と四角形の当たり判定後の座標補正
	// 1. 補正対象のVector座標
	// 2. 円の半径
	// 3. 衝突した四角形のVector座標
	// 4. 当たっている方向
	//=======================================================
	inline void isHit_ActionCorrectionPosition(t2k::Vector3& pos, float r, t2k::Vector3 dot_pos,int num);


	//=======================================================
	// Astar用のPlayerとEnemyの二次元座標作製
	// 1. Player用Vector2変数のアドレス
	// 2. Enemy用Vector2変数のアドレス
	//=======================================================
	void MakeVector2(tpr::Vector2_int* p_pos, tpr::Vector2_int* e_pos);


	//=======================================================
	// //PlayerとEnemyの間に障害物があるか
	// 
	// return true ある　false ない
	//=======================================================
	bool isHit_RayAndWall();


	//=======================================================
	// Enemyを始点、Playerを終点としたベクトルの
	// 単位ベクトルを得る
	// 
	// return PlayerとEnemyをつなぐ単位ベクトル
	//=======================================================
	tpr::Vector2 Normalize();


	//------------------------------------------------------------------------------------------------
	//変数

	//=======================================================
	//クラスのポインタ
	std::list <Object*> Op;      //Object
	std::list <Bullet*> Bp;      //Bullet
	std::list <Square*> Sp;      //Square
	std::list <Square*> Sp_wall; //Square
	Enemy* Ep  = nullptr;        //Enemy
	Player* Pp = nullptr;        //Player
	Camera cam;                  //Camera

	//=======================================================
	//CSV管理用変数
	std::vector<std::vector<std::string>>datas; //キャラデータ
	std::vector<std::vector<std::string>>map;   //マップデータ

	//=======================================================
	//開始と終了と初期化用変数
	bool _start_flag = false;

	bool _over = false;

	bool _init = true;

	float count = 0;
	float start = 3;

	//=======================================================
	//Astar用変数
	std::vector<std::vector<int>>astar_map;

	tpr::Vector2_int e_pos = { 0,0 };
	tpr::Vector2_int p_pos = { 0,0 };


	//------------------------------------------------------------------------------------------------
	//マスの種類

	enum {

		FLOOR,
		OUTSIDE_WALL,
		INSIDE_WALL,
		ROCK
	};


	//------------------------------------------------------------------------------------------------
	//毎フレーム呼び出し

	void Update(float deltatime) override;
	void Render(float deltatime) override;


	//------------------------------------------------------------------------------------------------

};