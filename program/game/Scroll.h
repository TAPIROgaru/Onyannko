#pragma once
#include <vector>
#include <iostream>
#include <functional>


//----------------------------------------------------------------------------------------------------
//自作ファイル

#include "Object.h"
#include "TPRlib/tpr_library.h"

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
		Scroll(int num,char c, tpr::Vector2 pos_);
		~Scroll() {};

		bool Activate(tpr::Vector2 pos,float dire_x, float dire_y);

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
		//変数


		int my_number;

		std::function< void (Scroll, tpr::Vector2 pos, float dire_x, float dire_y) > 
			skill_func[9] = {
			Kaginawa,
			Nintou,
			Torinoko,
			Kakuremi,
			Kunai,
			Blink,
			Shotgun,
			Makibisi,
			Teppo
		};

		std::function< void(Scroll,tpr::Vector2 pos, int angle) >
			make_skill_func[9] = {
			make_Kaginawa,
			make_Nintou,
			make_Torinoko,
			make_Kakuremi,
			make_Kunai,
			make_Blink,
			make_Shotgun,
			make_Makibisi,
			make_Teppo
		};

		//--------------------------------------------------------------------------------------
		//装備技一覧
		enum ult {

			KAGINAWA,
			NINTOU,
			TORINOKO,
		};
		enum skill {

			KAKUREMI = 3,
			KUNAI,
			BLINK,
			SHOTGUN,
			MAKIBISI,
			TEPPO,
		};
		
		
		//--------------------------------------------------------------------------------------
		//毎フレーム呼び出し

		void Update(float deltatime, tpr::Vector2 pos_);
		void Render(Camera* cam);
	};
}