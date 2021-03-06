#include "Player.h"
#include "GameManager.h"
#include "PlayScene.h"
#include "ResultScene.h"
#include "Skill.h"


#define PI 3.14159265359f

extern GameManager* GMp;

//----------------------------------------------------------------------------------------------------
//コンストラクタ
Player::Player() {

	_team = true;
	pos = { GameManager::START_POSITION_PLAYER_W,GameManager::START_POSITION_H , 0 };
	prev_pos = { 0, 0, 0 };
	LoadStatus();
	r = 16;
	origin_sta = sta;

	secconds_AS = 1.0f / sta.attack_speed;
}


//----------------------------------------------------------------------------------------------------
//デストラクタ
Player::~Player() {

	GMp->SPp->SavePlayer();
}


//----------------------------------------------------------------------------------------------------
//ファイル読み込み
void Player::LoadStatus() {

	FILE* fp = nullptr;

	fopen_s(&fp, "player.bin", "rb");

	//画像読み込み
	chara_handle = GMp->loadGraph("graphics/Player.png");

	//バイナリファイルがなかったら
	if (fp == NULL) {

		int i = 0;

		//名前読み込み
		for (i = 0; i < name_length; i++) {

			name[i] = GMp->SPp->datas[GMp->PLAYER_TAG][0].c_str()[i];

			if ('\0' == GMp->SPp->datas[GMp->PLAYER_TAG][0].c_str()[i]) {

				break;
			}
		}

		//ステータス読み込み
		sta = {
			std::atoi(GMp->SPp->datas[GMp->PLAYER_TAG][1].c_str()), //ヒットポイント
			0,
			std::atoi(GMp->SPp->datas[GMp->PLAYER_TAG][2].c_str()), //移動速度
			std::atoi(GMp->SPp->datas[GMp->PLAYER_TAG][3].c_str()), //攻撃力
			std::atoi(GMp->SPp->datas[GMp->PLAYER_TAG][4].c_str()), //防御力
			std::atoi(GMp->SPp->datas[GMp->PLAYER_TAG][5].c_str()), //攻撃速度
		};

		sta.hp_ = sta.HP;                                           //増減するHP

		//スキル読み込み
		ult    = new Scroll(std::atoi(GMp->SPp->datas[GMp->PLAYER_TAG][6].c_str())
			, 'u', tpr::Vector2(pos.x, pos.y));
		skillA = new Scroll(std::atoi(GMp->SPp->datas[GMp->PLAYER_TAG][7].c_str())
			, 'a', tpr::Vector2(pos.x, pos.y));
		skillB = new Scroll(std::atoi(GMp->SPp->datas[GMp->PLAYER_TAG][8].c_str())
			, 'b', tpr::Vector2(pos.x, pos.y));

		return;
	}
	
	//名前読み込み
	fread_s(name, sizeof(name), sizeof(char) * name_length, 1, fp);


	int status[status_value - 1] = { 0 };

	//ステータス読み込み
	fread_s(status, sizeof(status), sizeof(int) * (status_value - 1), 1, fp);

	sta.HP           = status[0];
	sta.hp_          = sta.HP;
	sta.move_speed   = status[1];
	sta.attack       = status[2];
	sta.defense      = status[3];
	sta.attack_speed = status[4];

	//スキル読み込み
	int num[3];
	fread_s(num, sizeof(num), sizeof(int) * 3, 1, fp);

	ult = new Scroll(num[0], 'u', tpr::Vector2(pos.x, pos.y));
	skillA = new Scroll(num[1], 'a', tpr::Vector2(pos.x, pos.y));
	skillB = new Scroll(num[2], 'b', tpr::Vector2(pos.x, pos.y));

	fclose(fp);
}


//----------------------------------------------------------------------------------------------------
//動かす
void Player::Move(float deltatime) {

	if (!GMp->SPp->_start_flag || GMp->SRp->_switch) { return; }

	//上
	if (t2k::Input::isKeyDown(t2k::Input::KEYBORD_W)) {

		pos.y -= sta.move_speed;
	}

	//左
	if (t2k::Input::isKeyDown(t2k::Input::KEYBORD_A)) {

		pos.x -= sta.move_speed;
	}

	//下
	if (t2k::Input::isKeyDown(t2k::Input::KEYBORD_S)) {

		pos.y += sta.move_speed;
	}

	//右
	if (t2k::Input::isKeyDown(t2k::Input::KEYBORD_D)) {

		pos.x += sta.move_speed;
	}

	//左クリック
	if (true == (GetMouseInput() & MOUSE_INPUT_LEFT)) {

		FireBullet(deltatime);
	}

	//ult
	if (t2k::Input::isKeyReleaseTrigger(t2k::Input::KEYBORD_SPACE)) {

		for (auto p : ult->skill_p) {
			if (!p->_active) {

				ShootDirection();
				ult->Activate(tpr::Vector2(pos.x, pos.y), bullet_direction_x,
					bullet_direction_y, this);
			}
		}
	}

	//skillA
	if (t2k::Input::isKeyReleaseTrigger(t2k::Input::KEYBORD_C)) {

		for (auto p : skillA->skill_p) {
			if (!p->_active) {

				ShootDirection();
				skillA->Activate(tpr::Vector2(pos.x, pos.y), bullet_direction_x,
					bullet_direction_y, this);
			}
		}
	}

	//skillB
	if (t2k::Input::isKeyReleaseTrigger(t2k::Input::KEYBORD_V)) {

		for (auto p : skillB->skill_p) {
			if (!p->_active) {

				ShootDirection();
				skillB->Activate(tpr::Vector2(pos.x, pos.y), bullet_direction_x,
					bullet_direction_y, this);
			}
		}
	}

	GMp->SPp->isHit_Wall(pos, prev_pos, (float)r);

	if (_stun) {
		pos = prev_pos;
	}

	prev_pos = pos;
}


//----------------------------------------------------------------------------------------------------
//撃つ
void Player::FireBullet(float deltatime) {

	if (secconds_AS > timecount) { return; }
	if (_stun) { return; }

	ShootDirection();

	GMp->SPp->MakeBullet(pos, bullet_direction_x, bullet_direction_y, true);

	timecount = 0;
}


//----------------------------------------------------------------------------------------------------
//発射する向き
void Player::ShootDirection() {

	//カメラ座標を考慮したマウス座標を取得
	t2k::Vector3 mouse_pos = GMp->SPp->GetMousePosition();

	//Playerとマウスの距離
	t2k::Vector3 component = pos - mouse_pos;

	//単位ベクトル
	magnitude = (float)sqrt(component.x * component.x + component.y * component.y);

	//角度の計算
	bullet_direction_x = component.x / magnitude * -1;
	bullet_direction_y = component.y / magnitude * -1;

	//画像角度の計算
	angle = atan2f(bullet_direction_x, bullet_direction_y) + PI * 2;
}

//----------------------------------------------------------------------------------------------------
//毎フレーム呼び出し

void Player::Update(float deltatime) {

	timecount += deltatime;

	Move(deltatime);

	ult->Update(deltatime, tpr::Vector2(pos.x, pos.y));
	skillA->Update(deltatime, tpr::Vector2(pos.x, pos.y));
	skillB->Update(deltatime, tpr::Vector2(pos.x, pos.y));

	if (GMp->SRp->_switch) {

		GMp->SPp->SavePlayer();
	}
}
void Player::Render(Camera* cam) {

	t2k::Vector3 pos_ = GMp->SPp->FixPositionVector(pos);

	DrawRotaGraph((int)pos_.x, (int)pos_.y, 1.0, 0, chara_handle, 1);

	ult->Render(cam);
	skillA->Render(cam);
	skillB->Render(cam);

	HP.DrawGauge(tpr::Vector2(pos_.x, pos_.y - 20.0f), 0, (float)sta.HP, (float)sta.hp_);
}

//----------------------------------------------------------------------------------------------------