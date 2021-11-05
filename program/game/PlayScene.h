#pragma once

//----------------------------------------------------------------------------------------------------
//自作ファイル

#include "Scene.h"

#include "Object.h"
#include "CharaObj.h"
#include "Camera.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"


//----------------------------------------------------------------------------------------------------

class PlayScene :public Scene {
public:

	//------------------------------------------------------------------------------------------------
	//関数

	PlayScene();

	void Delete();

	void SavePlayer();


	//------------------------------------------------------------------------------------------------
	//他ソースファイルから使う関数
	
	//弾生成
	void MakeBullet(t2k::Vector3, float, float, float);

	//カメラ座標を考慮したマウス座標を取得できる関数
	t2k::Vector3 GetMousePosition();

	//カメラ座標を考慮した座標を取得できる関数
	t2k::Vector3 FixPositionVector(t2k::Vector3);


	//------------------------------------------------------------------------------------------------
	//変数


	std::list <Object*> Op;     //Object
	std::list <Bullet*> Bp;     //Bullet
	std::list <Enemy*> Ep;      //Enemy
	Player* Pp = nullptr;       //Player

	Camera cam;                 //Cameraクラス


	//------------------------------------------------------------------------------------------------
	//毎フレーム呼び出し

	void Update(float deltatime) override;
	void Render(float deltatime) override;


	//------------------------------------------------------------------------------------------------

};