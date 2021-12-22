#pragma once
#include <vector>


//----------------------------------------------------------------------------------------------------
//自作ファイル

#include "Object.h"
#include "TPRlib/tpr_library.h"

namespace tpr {

	//装備技
	class Scroll final :public Object  {
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

		void Kaginawa();
		void Nintou(tpr::Vector2 pos, float dire_x, float dire_y);
		void Torinoko();
		void Kakuremi();
		void Kunai();
		void Blink();
		void Shotgun();
		void Makibisi();
		void Teppo();


		//--------------------------------------------------------------------------------------
		//変数

		int my_number;
		float count = 0;
		float cool_time;
		bool _active = false;

		std::vector<int> skill_img;
		int scroll_img_close;
		int scroll_img_open;

		int angle;

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