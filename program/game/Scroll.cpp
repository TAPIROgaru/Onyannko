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
	void Scroll::Activate(tpr::Vector2 pos, float dire_x, float dire_y, bool _team_) {

		if (count < cool_time || _active) { return; }

		switch (my_number) {

		case Scroll::ult::KAGINAWA:

			Kaginawa(pos, dire_x, dire_y, _team_);
			break;

		case Scroll::ult::NINTOU:

			Nintou(pos, dire_x, dire_y, _team_);
			break;

		case Scroll::ult::TORINOKO:

			Torinoko(pos, dire_x, dire_y, _team_);
			break;

		case Scroll::skill::KAKUREMI:

			Kakuremi(pos, dire_x, dire_y, _team_);
			break;

		case Scroll::skill::KUNAI:

			Kunai(pos, dire_x, dire_y, _team_);
			break;

		case Scroll::skill::BLINK:

			Blink(pos, dire_x, dire_y, _team_);
			break;

		case Scroll::skill::SHOTGUN:

			Shotgun(pos, dire_x, dire_y, _team_);
			break;

		case Scroll::skill::MAKIBISI:

			Makibisi(pos, _team_);
			break;

		case Scroll::skill::TEPPO:

			Teppo(pos, dire_x, dire_y, _team_);
			break;

		default:
			break;
		}
	}


	//------------------------------------------------------------------------------------------------
	//かぎなわ　(引っ張る)
	void Scroll::Kaginawa(tpr::Vector2 pos, float dire_x, float dire_y, bool _team_) {

		kagi = new class KAGINAWA(pos, tpr::Vector2(dire_x, dire_y), _team_);

		_active = true;
	}


	//------------------------------------------------------------------------------------------------
	//にんとう　(三回)
	void Scroll::Nintou(tpr::Vector2 pos, float dire_x, float dire_y, bool _team_) {

		if (!_active) {
			nint = new class NINTOU(pos, tpr::Vector2(dire_x, dire_y), _team_);
		}

		skill_img_num = 0;
		skill_img_pos.x = pos.x + dire_x * 32;
		skill_img_pos.y = pos.y + dire_y * 32;
		skill_img_rad = tpr::Angle::RadCalc(tpr::Vector2(), tpr::Vector2(dire_x, dire_y));
		if (dire_x < 0) {
			skill_img_rad += tpr::Angle::DegChangeRad(-90);
		}
		else if (dire_x > 0) {
			skill_img_rad += tpr::Angle::DegChangeRad(90);
		}

		if (skill_img_num >= skill_img.size() - 1) { _active = false; skill_img_num = 0; }

		if (flame_count == 2) {
			skill_img_num++;
			flame_count = 0;
		}
		flame_count++;

		_active = true;
	}


	//------------------------------------------------------------------------------------------------
	//とりのこ　(ばくだん)
	void Scroll::Torinoko(tpr::Vector2 pos, float dire_x, float dire_y, bool _team_) {

		if (!_active) {
			tori = new class TORINOKO(pos, tpr::Vector2(dire_x, dire_y), _team_);
		}

		_active = true;
	}


	//------------------------------------------------------------------------------------------------
	//かくれみ　(半透明にする)
	void Scroll::Kakuremi(tpr::Vector2 pos, float dire_x, float dire_y, bool _team_) {



		_active = true;
	}


	//------------------------------------------------------------------------------------------------
	//くない　ついせき(相殺あり)
	void Scroll::Kunai(tpr::Vector2 pos, float dire_x, float dire_y, bool _team_) {

		if (!_active) {
			kuna = new class KUNAI(pos, tpr::Vector2(dire_x, dire_y), _team_);
		}

		_active = true;
	}


	//------------------------------------------------------------------------------------------------
	//ブリンク
	void Scroll::Blink(tpr::Vector2 pos, float dire_x, float dire_y, bool _team_) {

		tpr::Vector2 pos_ = GMp->SPp->GetCharaPosition(_team_);

		if (_team_) {
			

		}

		_active = true;
	}


	//------------------------------------------------------------------------------------------------
	//散弾
	void Scroll::Shotgun(tpr::Vector2 pos, float dire_x, float dire_y, bool _team_) {

		if (!_active) {
			shot = new class SHOTGUN(pos, tpr::Vector2(dire_x, dire_y), _team_);
		}
	}


	//------------------------------------------------------------------------------------------------
	//まきびし　(トラップ)
	void Scroll::Makibisi(tpr::Vector2 pos, bool _team_) {

		if (!_active) {
			maki = new class MAKIBISI(t2k::Vector3(pos.x, pos.y, 0), _team_);
			GMp->SPp->Op.emplace_back(maki);
		}
	}


	//------------------------------------------------------------------------------------------------
	//徹甲弾
	void Scroll::Teppo(tpr::Vector2 pos, float dire_x, float dire_y, bool _team_) {

		if (!_active) {
			tepp = new class TEPPO(pos, tpr::Vector2(dire_x, dire_y), _team_);
		}
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

		if (!_active) { return; }

		tpr::Vector2 pos__ = GMp->SPp->FixPositionVector(skill_img_pos);

		DrawRotaGraph(pos__.x, pos__.y, 1.0, skill_img_rad, skill_img[skill_img_num], true);

		if (skill_img_num >= skill_img.size() - 1) { _active = false; skill_img_num = 0; }

		if (flame_count == 2) {
			skill_img_num++;
			flame_count = 0;
		}
		flame_count++;
	}
}