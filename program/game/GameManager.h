#pragma once
#include "DxLib.h"
#include <list>

//----------------------------------------------------------------------------------------------------
//自作ファイル

#include "Scene.h"
#include "PlayScene.h"
#include "TitleScene.h"
#include "MenuScene.h"


//----------------------------------------------------------------------------------------------------

class GameManager {
public:

	//------------------------------------------------------------------------------------------------
	//スクリーンサイズ　フィールドサイズ

	static constexpr int SCREEN_W = 960;
	static constexpr int SCREEN_H = 540;

	static constexpr int FIELD_W = SCREEN_W * 1.2;
	static constexpr int FIELD_H = SCREEN_H * 1.2;

	static constexpr bool WINDOW_MODE = true;

	//------------------------------------------------------------------------------------------------

	//コンストラクタ
	GameManager();


	//------------------------------------------------------------------------------------------------
	//関数

	void DrawBuckGround();


	//------------------------------------------------------------------------------------------------
	//他ソースファイルから使う関数

	//カメラ座標を考慮したマウス座標を取得できる関数
	t2k::Vector3 GetMousePosition();

	//カメラ座標を考慮した座標を取得できる関数
	t2k::Vector3 FixPositionVector(t2k::Vector3);


	//------------------------------------------------------------------------------------------------
	//変数

	int img = 0;

	t2k::Vector3 img_pos1 = { -FIELD_W, -FIELD_H,0 };
	t2k::Vector3 img_pos2 = { FIELD_W, FIELD_H,0 };

	//------------------------------------------------------------------------------------------------
	//リスト　ポインタ

	std::list <Scene*> Sp;      //Scene
	PlayScene* SPp = nullptr;   //Play
	TitleScene* STp = nullptr;  //Title
	MenuScene* SMp = nullptr;   //Menu


	//------------------------------------------------------------------------------------------------
	//毎フレーム呼び出し

	void Update(float deltatime);
	void Render(float deltatime);


	//------------------------------------------------------------------------------------------------
};