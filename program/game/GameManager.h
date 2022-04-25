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
	//サイズ一覧 その他設定

	static constexpr int SCREEN_W = 960;   //ウィンドウの横幅
	static constexpr int SCREEN_H = 540;   //ウィンドウの縦幅

	static constexpr int FIELD_W = 576;   //フィールドの横幅
	static constexpr int FIELD_H = 400;   //フィールドの縦幅

	static constexpr int TILE_SIZE_W = 32;   //1マスの横幅
	static constexpr int TILE_SIZE_H = 32;   //1マスの縦幅

	static constexpr int TILE_VALUE_W = 40;   //横のマス目の数
	static constexpr int TILE_VALUE_H = 28;   //縦のマス目の数

	static constexpr int TILE_VALUE_W_WALL = 6;   //左右の合計した壁の数
	static constexpr int TILE_VALUE_H_WALL = 6;   //上下の合計した壁の数

	static constexpr bool WINDOW_MODE = false;    //スクリーンモード　true フル　false ウィンドウ


	static constexpr int BULLET_RADIUS = 7;   //弾の半径


	static constexpr int PLAYER_TAG = 1;   //Playerのタグ番号
	static constexpr int ENEMY_TAG = 2;   //Enemyのタグ番号


	static constexpr float START_POSITION_PLAYER_W = 50.0f;   //Playerの初期座標X
	static constexpr float START_POSITION_ENEMY_W = 1050.0f;   //Enemyの初期座標X
	static constexpr float START_POSITION_H = 300.0f;   //両方の初期座標Y

	static constexpr bool DEBUG_MODE = true;   //デバッグモード
	                 bool ENEMY_MODE = true;   //敵の行動するかしないか


	//------------------------------------------------------------------------------------------------

	//コンストラクタ
	GameManager();


	//------------------------------------------------------------------------------------------------
	//関数

	void ChangeScene();

	void Init();

	//------------------------------------------------------------------------------------------------
	//他ソースファイルから使う関数

	//=======================================================
	// 画像呼び出し
	// 1.グラフィックハンドル
	// 
	//  return 画像データ
	//=======================================================
	int loadGraph(std::string str);

	//=======================================================
	// 画像呼び出し
	// ※必ず戻り値のポインタはdeleteすること※
	// 
	// 1. グラフィックハンドル
	// 
	// return 画像データ配列の先頭アドレス
	//=======================================================
	std::vector<int> loadDivGraph(std::vector<std::string> str,int img_value);

	//=======================================================
	// 音源呼び出し
	// 1.ハンドル
	// 
	//  return データ
	//=======================================================
	int loadSoundMem(std::string str);

	//------------------------------------------------------------------------------------------------
	//変数

	std::vector<std::vector<std::string>>datas;
	std::unordered_map<std::string, int> image;
	std::unordered_map<std::string, int> sound;

	bool _init = true;

	int img_aim;
	int img_mouse;

	int scene_sou = 0;


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