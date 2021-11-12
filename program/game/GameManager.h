#pragma once
#include "DxLib.h"
#include <list>

//----------------------------------------------------------------------------------------------------
//自作ファイル

#include "Scene.h"
#include "PlayScene.h"
#include "TitleScene.h"
#include "MenuScene.h"
#include "ResultScene.h"

#include "Camera.h"


//----------------------------------------------------------------------------------------------------

class GameManager {
public:

	//------------------------------------------------------------------------------------------------
	//スクリーンサイズ　フィールドサイズ

	static constexpr int SCREEN_W = 960;
	static constexpr int SCREEN_H = 540;

	static constexpr int FIELD_W = SCREEN_W * 1.5;
	static constexpr int FIELD_H = SCREEN_H * 1.5;

	static constexpr bool WINDOW_MODE = false;

	//------------------------------------------------------------------------------------------------

	//コンストラクタ
	GameManager();


	//------------------------------------------------------------------------------------------------
	//関数

	void DrawBuckGround();

	void ChangeScene();

	void Init();

	//------------------------------------------------------------------------------------------------
	//他ソースファイルから使う関数



	//------------------------------------------------------------------------------------------------
	//変数

	bool _init = true;

	int img_aim;
	int img_mouse;

	t2k::Vector3 img_pos1 = { -FIELD_W, -FIELD_H,0 };
	t2k::Vector3 img_pos2 = { FIELD_W, FIELD_H,0 };


	//------------------------------------------------------------------------------------------------
	//リスト　ポインタ

	std::list <Scene*> Sp;      //Scene
	PlayScene* SPp = nullptr;   //Play
	TitleScene* STp = nullptr;  //Title
	MenuScene* SMp = nullptr;   //Menu
	ResultScene* SRp = nullptr; //Result


	//------------------------------------------------------------------------------------------------
	//毎フレーム呼び出し

	void Update(float deltatime);
	void Render(float deltatime);


	//------------------------------------------------------------------------------------------------
};