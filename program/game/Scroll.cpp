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

			std::vector<std::string> str;

			str.emplace_back("graphics/NINGU/NINTOU1.png");
			str.emplace_back("graphics/NINGU/NINTOU2.png");
			str.emplace_back("graphics/NINGU/NINTOU3.png");
			str.emplace_back("graphics/NINGU/NINTOU4.png");

			skill_img = GMp->loadDivGraph(str, 4);

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
	bool Scroll::Activate(tpr::Vector2 pos,float dire_x, float dire_y) {

		if (count < cool_time) { return false; }

		switch (my_number) {

		case Scroll::ult::KAGINAWA:

			Kaginawa();
			break;

		case Scroll::ult::NINTOU:

			Nintou(pos, dire_x, dire_y);
			break;

		case Scroll::ult::TORINOKO:

			Torinoko();
			break;

		case Scroll::skill::KAKUREMI:

			Kakuremi();
			break;

		case Scroll::skill::KUNAI:

			Kunai();
			break;

		case Scroll::skill::BLINK:

			Blink();
			break;

		case Scroll::skill::SHOTGUN:

			Shotgun();
			break;

		case Scroll::skill::MAKIBISI:

			Makibisi();
			break;

		case Scroll::skill::TEPPO:

			Teppo();
			break;

		default:
			break;
		}
	}


	//------------------------------------------------------------------------------------------------
	//かぎなわ　(引っ張る)
	void Scroll::Kaginawa() {

	}


	//------------------------------------------------------------------------------------------------
	//にんとう　(三回)
	void Scroll::Nintou(tpr::Vector2 pos, float dire_x, float dire_y) {

		int i = 0;
		DrawGraph(pos.x+dire_x*100, pos.y + dire_y * 100, skill_img[i], true);
		i++;
		_active = true;
		if (i > skill_img.size()) { _active = false; }
	}


	//------------------------------------------------------------------------------------------------
	//とりのこ　(ばくだん)
	void Scroll::Torinoko() {

	}


	//------------------------------------------------------------------------------------------------
	//かくれみ　(半透明にする)
	void Scroll::Kakuremi() {

	}


	//------------------------------------------------------------------------------------------------
	//くない　ついせき(相殺あり)
	void Scroll::Kunai() {

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
	//まきびし　(トラップ)
	void Scroll::Makibisi() {

	}


	//------------------------------------------------------------------------------------------------
	//徹甲弾
	void Scroll::Teppo() {

	}


	//----------------------------------------------------------------------------------------------------
	//毎フレーム呼び出し

	void Scroll::Update(float deltatime, tpr::Vector2 pos_) {

		tpr::Vector2 v(pos_.x, pos_.y - 50);

		tpr::Vector2 v2 = Rotation::RotaVec2(v, pos_, Angle::DegChangeRad(angle));
		pos = t2k::Vector3(v2.x, v2.y, 0);

		angle++;
		count += deltatime;
	}
	void Scroll::Render(Camera* cam) {

		t2k::Vector3 pos_ = GMp->SPp->FixPositionVector(pos);
		DrawRotaGraph(pos_.x, pos_.y, 0.5, 0, scroll_img_open, true);
	}
}