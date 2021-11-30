#include "Scroll.h"


namespace tpr {
	//------------------------------------------------------------------------------------------------
	//コンストラクタ
	Scroll::Scroll(int num) {

		my_number = num;

		switch (my_number) {

		case Scroll::ult::BEAM:

			cool_time = 0.0f;
			break;

		case Scroll::ult::AIR_STRIKE:

			cool_time = 0.0f;
			break;

		case Scroll::ult::MADNESS:

			cool_time = 0.0f;
			break;

		case Scroll::skill::BARRIER:

			cool_time = 0.0f;
			break;

		case Scroll::skill::TRACKING:

			cool_time = 0.0f;
			break;

		case Scroll::skill::BLINK:

			cool_time = 0.0f;
			break;

		case Scroll::skill::SHOTGUN:

			cool_time = 0.0f;
			break;

		case Scroll::skill::TURRET:

			cool_time = 0.0f;
			break;

		case Scroll::skill::ARMOR_PIERCING:

			cool_time = 0.0f;
			break;

		default:

			cool_time = 0.0f;
			break;
		}
	}


	//------------------------------------------------------------------------------------------------
	//発動
	bool Scroll::Activate(float count) {

		if (count < cool_time) { return false; }

		switch (my_number) {

		case Scroll::ult::BEAM:

			Beam();
			break;

		case Scroll::ult::AIR_STRIKE:

			AirStrike();
			break;

		case Scroll::ult::MADNESS:

			Madness();
			break;

		case Scroll::skill::BARRIER:

			Barrier();
			break;

		case Scroll::skill::TRACKING:

			Tracking();
			break;

		case Scroll::skill::BLINK:

			Blink();
			break;

		case Scroll::skill::SHOTGUN:

			Shotgun();
			break;

		case Scroll::skill::TURRET:

			Turret();
			break;

		case Scroll::skill::ARMOR_PIERCING:

			ArmorPiercing();
			break;

		default:
			break;
		}
	}


	//------------------------------------------------------------------------------------------------
	//ビーム
	void Scroll::Beam() {

	}


	//------------------------------------------------------------------------------------------------
	//特大空爆
	void Scroll::AirStrike() {

	}


	//------------------------------------------------------------------------------------------------
	//狂乱化
	void Scroll::Madness() {

	}


	//------------------------------------------------------------------------------------------------
	//バリア
	void Scroll::Barrier() {

	}


	//------------------------------------------------------------------------------------------------
	//追跡弾
	void Scroll::Tracking() {

	}


	//------------------------------------------------------------------------------------------------
	//ブリンク
	void Scroll::Blink() {

	}


	//------------------------------------------------------------------------------------------------
	//散弾
	void Scroll::Shotgun() {

	}


	//------------------------------------------------------------------------------------------------
	//タレット
	void Scroll::Turret() {

	}


	//------------------------------------------------------------------------------------------------
	//徹甲弾
	void Scroll::ArmorPiercing() {

	}
}