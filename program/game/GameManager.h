#pragma once
#include "DxLib.h"
#include <list>
#include <string>
#include <unordered_map>
using namespace std;

//----------------------------------------------------------------------------------------------------
//自作ファイル



//----------------------------------------------------------------------------------------------------
//クラスの前方宣言

class Scene;
class PlayScene;
class TitleScene;
class MenuScene;
class ResultScene;


//----------------------------------------------------------------------------------------------------

class GameManager {
public:

	//------------------------------------------------------------------------------------------------
	//スクリーンサイズ　フィールドサイズ　タイルサイズ

	static constexpr int SCREEN_W = 960;
	static constexpr int SCREEN_H = 540;

	static constexpr int FIELD_W = 576;   // 1152
	static constexpr int FIELD_H = 400;   // 800

	static constexpr int TILE_SIZE_W = 32;
	static constexpr int TILE_SIZE_H = 32;

	static constexpr int TILE_VALUE_W = 40;
	static constexpr int TILE_VALUE_H = 28;

	static constexpr int TILE_VALUE_W_WALL = 6;
	static constexpr int TILE_VALUE_H_WALL = 6;

	static constexpr bool WINDOW_MODE = true;

	//------------------------------------------------------------------------------------------------

	//コンストラクタ
	GameManager();


	//------------------------------------------------------------------------------------------------
	//関数

	void ChangeScene();

	void Init();

	//------------------------------------------------------------------------------------------------
	//他ソースファイルから使う関数

	//画像呼び出し
	int loadGraph(std::string);

	//------------------------------------------------------------------------------------------------
	//変数

	std::vector<std::vector<std::string>>datas;
	std::unordered_map<std::string, int> image;

	bool _init = true;

	int img_aim;
	int img_mouse;


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