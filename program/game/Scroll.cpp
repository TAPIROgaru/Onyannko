#include "Scroll.h"
#include "GameManager.h"
#include "PlayScene.h"

extern GameManager *GMp;


namespace tpr {
	//------------------------------------------------------------------------------------------------
	//コンストラクタ
	Scroll::Scroll(int num, char c, tpr::Vector2 pos_) {

		my_number = num;
		

		switch (my_number) {

		case Scroll::ult::KAGINAWA:

			scroll_img_close = GMp->loadGraph("graphics/scroll/KAGINAWA_close.png");
			scroll_img_open = GMp->loadGraph("graphics/scroll/KAGINAWA_open.png");

			skill_img.emplace_back(GMp->loadGraph("graphics/NINGU/.png"));

			cool_time = 0.0f;
			break;

		case Scroll::ult::NINTOU:
		{
			std::string str[4]{
				"graphics/NINGU/NINTOU1.png",
				"graphics/NINGU/NINTOU2.png",
				"graphics/NINGU/NINTOU3.png",
				"graphics/NINGU/NINTOU4.png",
			};

			int* p = GMp->loadDivGraph(&str[0]);

			for (int i = 0; i < 4; i++, p++) {
				skill_img.emplace_back(p[i]);
			}

			scroll_img_close = GMp->loadGraph("graphics/scroll/NINTOU_close.png");
			scroll_img_open = GMp->loadGraph("graphics/scroll/NINTOU_open.png");
		}

		cool_time = 0.0f;
		break;

		case Scroll::ult::TORINOKO:

			scroll_img_close = GMp->loadGraph("graphics/scroll/TORINOKO_close.png");
			scroll_img_open = GMp->loadGraph("graphics/scroll/TORINOKO_open.png");

			skill_img.emplace_back(GMp->loadGraph("graphics/NINGU/.png"));

			cool_time = 0.0f;
			break;

		case Scroll::skill::KAKUREMI:

			scroll_img_close = GMp->loadGraph("graphics/scroll/KAKUREMI_close.png");
			scroll_img_open = GMp->loadGraph("graphics/scroll/KAKUREMI_open.png");

			skill_img.emplace_back(GMp->loadGraph("graphics/NINGU/.png"));

			cool_time = 0.0f;
			break;

		case Scroll::skill::KUNAI:

			scroll_img_close = GMp->loadGraph("graphics/scroll/KUNAI_close.png");
			scroll_img_open = GMp->loadGraph("graphics/scroll/KUNAI_open.png");

			skill_img.emplace_back(GMp->loadGraph("graphics/NINGU/KUNAI.png"));

			cool_time = 0.0f;
			break;

		case Scroll::skill::BLINK:

			scroll_img_close = GMp->loadGraph("graphics/scroll/BLINK_close.png");
			scroll_img_open = GMp->loadGraph("graphics/scroll/BLINK_open.png");

			skill_img.emplace_back(GMp->loadGraph("graphics/NINGU/.png"));

			cool_time = 0.0f;
			break;

		case Scroll::skill::SHOTGUN:

			scroll_img_close = GMp->loadGraph("graphics/scroll/SHOTGUN_close.png");
			scroll_img_open = GMp->loadGraph("graphics/scroll/SHOTGUN_open.png");

			skill_img.emplace_back(GMp->loadGraph("graphics/NINGU/.png"));

			cool_time = 0.0f;
			break;

		case Scroll::skill::MAKIBISI:

			scroll_img_close = GMp->loadGraph("graphics/scroll/MAKIBISI_close.png");
			scroll_img_open = GMp->loadGraph("graphics/scroll/MAKIBISI_open.png");

			skill_img.emplace_back(GMp->loadGraph("graphics/NINGU/.png"));

			cool_time = 0.0f;
			break;

		case Scroll::skill::TEPPO:

			scroll_img_close = GMp->loadGraph("graphics/scroll/TEPPO_close.png");
			scroll_img_open = GMp->loadGraph("graphics/scroll/TEPPO_open.png");

			skill_img.emplace_back(GMp->loadGraph("graphics/NINGU/.png"));

			cool_time = 0.0f;
			break;

		default:

			cool_time = 0.0f;
			break;
		}

		tpr::Vector2 v(pos_.x, pos_.y - 50);

		if (c == 'u') {
			pos = t2k::Vector3(v.x, v.y, 0);
			angle = 0;
		}
		else if (c == 'a') {

			angle = 120;
			tpr::Vector2 v2 = Rotation::RotaVec2(v, pos_, Angle::DegChangeRad(angle));
			pos = t2k::Vector3(v2.x, v2.y, 0);
		}
		else if (c == 'b') {

			angle = 240;
			tpr::Vector2 v2 = Rotation::RotaVec2(v, pos_, Angle::DegChangeRad(angle));
			pos = t2k::Vector3(v2.x, v2.y, 0);
		}
	}


	//------------------------------------------------------------------------------------------------
	//発動
	bool Scroll::Activate(float count) {

		if (count < cool_time) { return false; }

		switch (my_number) {

		case Scroll::ult::KAGINAWA:

			KAGINAWA();
			break;

		case Scroll::ult::NINTOU:

			NINTOU();
			break;

		case Scroll::ult::TORINOKO:

			TORINOKO();
			break;

		case Scroll::skill::KAKUREMI:

			KAKUREMI();
			break;

		case Scroll::skill::KUNAI:

			KUNAI();
			break;

		case Scroll::skill::BLINK:

			BLINK();
			break;

		case Scroll::skill::SHOTGUN:

			SHOTGUN();
			break;

		case Scroll::skill::MAKIBISI:

			MAKIBISI();
			break;

		case Scroll::skill::TEPPO:

			TEPPO();
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
	void Scroll::TEPPO() {

	}


	//----------------------------------------------------------------------------------------------------
	//毎フレーム呼び出し

	void Scroll::Update(float deltatime, tpr::Vector2 pos_) {

		tpr::Vector2 v(pos_.x, pos_.y - 50);

		tpr::Vector2 v2 = Rotation::RotaVec2(v, pos_, Angle::DegChangeRad(angle));
		pos = t2k::Vector3(v2.x, v2.y, 0);

		angle++;
	}
	void Scroll::Render(Camera* cam) {

		t2k::Vector3 pos_ = GMp->SPp->FixPositionVector(pos);
		DrawRotaGraph(pos_.x, pos_.y, 0.5, 0, scroll_img_open, true);
	}
}