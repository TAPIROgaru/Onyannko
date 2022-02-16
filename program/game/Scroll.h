#pragma once
#include <vector>
#include <iostream>
#include <functional>


//----------------------------------------------------------------------------------------------------
//自作ファイル

#include "Object.h"
#include "TPRlib/tpr_library.h"

class BLINK;
class KAGINAWA;
class KAKUREMI;
class KUNAI;
class MAKIBISI;
class NINTOU;
class SHOTGUN;
class TEPPO;
class TORINOKO;


namespace tpr {

	//装備技
	class Scroll final  {
	//finalは継承させない

	public:


		//------------------------------------------------------------------------------------------------
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

		void Activate(tpr::Vector2 pos,float dire_x, float dire_y);

		void Kaginawa(tpr::Vector2 pos, float dire_x, float dire_y);
		void Nintou(tpr::Vector2 pos, float dire_x, float dire_y);
		void Torinoko(tpr::Vector2 pos, float dire_x, float dire_y);
		void Kakuremi(tpr::Vector2 pos, float dire_x, float dire_y);
		void Kunai(tpr::Vector2 pos, float dire_x, float dire_y);
		void Blink(tpr::Vector2 pos, float dire_x, float dire_y);
		void Shotgun(tpr::Vector2 pos, float dire_x, float dire_y);
		void Makibisi(tpr::Vector2 pos, float dire_x, float dire_y);
		void Teppo(tpr::Vector2 pos, float dire_x, float dire_y);

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
			E_KAGINAWA,
			E_NINTOU,
			E_TORINOKO,
			E_ULT_MAX
		};
		enum skill {

			E_KAKUREMI = E_ULT_MAX,
			E_KUNAI,
			E_BLINK,
			E_SHOTGUN,
			E_MAKIBISI,
			E_TEPPO,
			E_SKILL_MAX
		};


		//--------------------------------------------------------------------------------------
		//変数


		int my_number;


		std::function< void (Scroll*, tpr::Vector2 pos, float dire_x, float dire_y) >
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

		BLINK* blink;
		KAGINAWA* kaginawa;
		KAKUREMI* kakuremi;
		KUNAI* kunai;
		MAKIBISI* makibisi;
		NINTOU* nintou;
		SHOTGUN* shotgun;
		TEPPO* teppo;
		TORINOKO* torinoko;

		
		//--------------------------------------------------------------------------------------
		//毎フレーム呼び出し

		void Update(float deltatime, tpr::Vector2 pos_);
		void Render(Camera* cam);
	};
}