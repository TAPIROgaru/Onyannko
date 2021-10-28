#pragma once
#include "DxLib.h"
#include <list>

//----------------------------------------------------------------------------------------------------
//自作ファイル

#include "Object.h"
#include "CharaObj.h"
#include "Camera.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"


//----------------------------------------------------------------------------------------------------

class GameManager {
public:

	//------------------------------------------------------------------------------------------------
	//スクリーンサイズ　フィールドサイズ

	static constexpr int SCREEN_W = 1920 / 2;
	static constexpr int SCREEN_H = 1080 / 2;

	static constexpr int FIELD_W = 1920;
	static constexpr int FIELD_H = 1080;

	//------------------------------------------------------------------------------------------------

	//コンストラクタ
	GameManager();

	//初期化
	void Init();

	//タイトルシーン
	bool Title(const float);
	//プレイシーン
	bool Play(const float);


	//------------------------------------------------------------------------------------------------
	//関数

	void Delete();   //削除

	void SavePlayer();


	//------------------------------------------------------------------------------------------------
	//他ソースファイルから使う関数

	//カメラ座標を考慮したマウス座標を取得できる関数
	t2k::Vector3 GetMousePosition();

	//カメラ座標を考慮した座標を取得できる関数
	t2k::Vector3 FixPositionVector(t2k::Vector3);

	//弾生成
	void MakeBullet(t2k::Vector3, float, float, float);


	//------------------------------------------------------------------------------------------------
	//変数

	 //初期化フラグ
	bool _init = true;

	//シーン管理
	t2k::Sequence<GameManager*> seq =
		t2k::Sequence<GameManager*>(this, &GameManager::Title);

	int img;

	t2k::Vector3 img_pos1 = { -SCREEN_W * 1.5, -SCREEN_H * 1.5,0 };
	t2k::Vector3 img_pos2 = { SCREEN_W * 1.5, SCREEN_H * 1.5,0 };

	//------------------------------------------------------------------------------------------------
	//リスト　ポインタ

	std::list <Object*> Op;   //Objectクラス
	std::list <Bullet*> Bp;   //Bulletクラス
	std::list <Enemy*> Ep;    //Enemyクラス

	Camera cam;               //Cameraクラス

	Player* Pp = nullptr;     //Playerクラス


	//------------------------------------------------------------------------------------------------
	//毎フレーム呼び出し

	void Update(float deltatime);
	void Render(float deltatime);


	//------------------------------------------------------------------------------------------------
};