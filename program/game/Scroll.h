#pragma once
#include <vector>
#include <iostream>
#include <functional>


//------------------------------------------------------------------------------------------
//自作ファイル

#include "Object.h"
#include "TPRlib/tpr_library.h"

class CharaObj;
class Skill;
class BLINK;
class KAGINAWA;
class KAKUREMI;
class KUNAI;
class MAKIBISI;
class NINTOU;
class SHOTGUN;
class TEPPO;
class TORINOKO;


//装備技
class Scroll final {
	//finalは継承させない

public:


	//--------------------------------------------------------------------------------------
	//関数

	//=======================================================
	// スキルの生成(コンストラクタ)
	// 1. 生成するスキルの番号
	//    ヘッダー内の装備技一覧(enum)参照
	// 2. ultならu skillAならa skillBならb
	// 3. スキル所有者の座標
	//======================================================
	Scroll() {}
	Scroll(int num, char c, tpr::Vector2 pos_);
	~Scroll() {};

	void Activate(tpr::Vector2 pos, float dire_x, float dire_y, CharaObj* p);

	void Kaginawa(tpr::Vector2 pos, float dire_x, float dire_y, CharaObj* p);
	void Nintou(tpr::Vector2 pos, float dire_x, float dire_y, CharaObj* p);
	void Torinoko(tpr::Vector2 pos, float dire_x, float dire_y, CharaObj* p);
	void Kakuremi(tpr::Vector2 pos, float dire_x, float dire_y, CharaObj* p);
	void Kunai(tpr::Vector2 pos, float dire_x, float dire_y, CharaObj* p);
	void Blink(tpr::Vector2 pos, float dire_x, float dire_y, CharaObj* p);
	void Shotgun(tpr::Vector2 pos, float dire_x, float dire_y, CharaObj* p);
	void Makibisi(tpr::Vector2 pos, float dire_x, float dire_y, CharaObj* p);
	void Teppo(tpr::Vector2 pos, float dire_x, float dire_y, CharaObj* p);

	void make_Kaginawa(tpr::Vector2 pos, int angle);
	void make_Nintou(tpr::Vector2 pos, int angle);
	void make_Torinoko(tpr::Vector2 pos, int angle);
	void make_Kakuremi(tpr::Vector2 pos, int angle);
	void make_Kunai(tpr::Vector2 pos, int angle);
	void make_Blink(tpr::Vector2 pos, int angle);
	void make_Shotgun(tpr::Vector2 pos, int angle);
	void make_Makibisi(tpr::Vector2 pos, int angle);
	void make_Teppo(tpr::Vector2 pos, int angle);



	//--------------------------------------------------------------------------------------
	//装備技一覧
	enum ult {
		E_KAGINAWA,              //0
		E_NINTOU,                //1
		E_TORINOKO,              //2
		E_ULT_MAX
	};
	enum skill {

		E_KAKUREMI = E_ULT_MAX,  //3
		E_KUNAI,                 //4
		E_BLINK,                 //5
		E_SHOTGUN,               //6
		E_MAKIBISI,              //7
		E_TEPPO,                 //8
		E_SKILL_MAX              //9
	};


	//--------------------------------------------------------------------------------------
	//変数


	int my_number = -1;


	std::function< void(Scroll*, tpr::Vector2 pos, float dire_x, float dire_y, CharaObj* p) >
		skill_func[E_SKILL_MAX] = {
		&Scroll::Kaginawa,
		&Scroll::Nintou,
		&Scroll::Torinoko,
		&Scroll::Kakuremi,
		&Scroll::Kunai,
		&Scroll::Blink,
		&Scroll::Shotgun,
		&Scroll::Makibisi,
		&Scroll::Teppo
	};

	std::function< void(Scroll*, tpr::Vector2 pos, int angle) >
		make_skill_func[E_SKILL_MAX] = {
		&Scroll::make_Kaginawa,
		&Scroll::make_Nintou,
		&Scroll::make_Torinoko,
		&Scroll::make_Kakuremi,
		&Scroll::make_Kunai,
		&Scroll::make_Blink,
		&Scroll::make_Shotgun,
		&Scroll::make_Makibisi,
		&Scroll::make_Teppo
	};

	BLINK* blink = nullptr;
	KAGINAWA* kaginawa = nullptr;
	KAKUREMI* kakuremi = nullptr;
	KUNAI* kunai = nullptr;
	MAKIBISI* makibisi = nullptr;
	NINTOU* nintou = nullptr;
	SHOTGUN* shotgun = nullptr;
	TEPPO* teppo = nullptr;
	TORINOKO* torinoko = nullptr;

	std::list <Skill*> skill_p;


	//--------------------------------------------------------------------------------------
	//毎フレーム呼び出し

	void Update(float deltatime, tpr::Vector2 pos_);
	void Render(Camera* cam);
};