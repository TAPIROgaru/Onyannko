#pragma once
#include <unordered_map>
#include "../library/math.h"

//----------------------------------------------------------------------------------------------------
//自作ファイル

#include "Scene.h"

#include "Object.h"
#include "CharaObj.h"
#include "Camera.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "CircleHit.h"
#include "Square.h"


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

	void isHit_bullet();

	void DrawBuckGround();

	void isHit_wall();


	//------------------------------------------------------------------------------------------------
	//他ソースファイルから使う関数
	
	//=======================================================
	//弾生成
	// 1.初期座標
	// 2.x角度
	// 3.y角度
	// 4.陣営
	//=======================================================
	void MakeBullet(t2k::Vector3, float, float, bool);


	//=======================================================
	//カメラ座標を考慮したマウス座標を取得できる関数
	// return マウス座標
	//=======================================================
	t2k::Vector3 GetMousePosition();


	//=======================================================
	//カメラ座標を考慮した座標を取得できる関数
	// 1.修正するVector座標
	// 
	// return 修正されたVector座標
	//=======================================================
	t2k::Vector3 FixPositionVector(t2k::Vector3);


	//------------------------------------------------------------------------------------------------
	//変数


	std::list <Object*> Op;      //Object
	std::list <Bullet*> Bp;      //Bullet
	std::list <Square*> Sp;      //Square
	std::list <Square*> Sp_wall; //Square
	Enemy* Ep  = nullptr;        //Enemy
	Player* Pp = nullptr;        //Player

	Camera cam;                  //Cameraクラス

	std::vector<std::vector<std::string>>datas;
	std::vector<std::vector<std::string>>map;

	bool _start_flag = false;

	bool _over = false;

	bool _init = true;

	float count = 0;
	float start = 3;

	int img_bullet = 0;


	//------------------------------------------------------------------------------------------------
	//マスの種類

	enum {

		FLOOR,
		WALL,
		ROCK
	};


	//------------------------------------------------------------------------------------------------
	//毎フレーム呼び出し

	void Update(float deltatime) override;
	void Render(float deltatime) override;


	//------------------------------------------------------------------------------------------------

};