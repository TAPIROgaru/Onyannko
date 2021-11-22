#include "Player.h"
#include "GameManager.h"


#define PI 3.14159265359f

extern GameManager* GMp;

//----------------------------------------------------------------------------------------------------
//コンストラクタ
Player::Player() {

	_team = true;
	pos = { -200, 0, 0 };
	LoadStatus();
	r = 18;
	_hp = sta.HP;

	secconds_AS = 1.0f / sta.attack_speed;
}


//----------------------------------------------------------------------------------------------------
//デストラクタ
Player::~Player() {
}


//----------------------------------------------------------------------------------------------------
//ファイル読み込み
void Player::LoadStatus() {

	FILE* fp = nullptr;

	int status[status_value] = { 0 };

	fopen_s(&fp, "player.bin", "rb");

	//画像読み込み
	chara_handle = GMp->loadGraph("graphics/Player.png");

	//バイナリファイルがなかったら
	if (fp == NULL) {

		int i = 0;

		//名前読み込み
		for (i = 0; i < name_length; i++) {

			name[i] = GMp->SPp->datas[0][0].c_str()[i];

			if ('\0' == GMp->SPp->datas[0][0].c_str()[i]) {

				break;
			}
		}

		//ステータス読み込み
		sta = {
			std::atoi(GMp->SPp->datas[0][1].c_str()), //ヒットポイント
			std::atoi(GMp->SPp->datas[0][2].c_str()), //移動速度
			std::atoi(GMp->SPp->datas[0][3].c_str()), //攻撃力
			std::atoi(GMp->SPp->datas[0][4].c_str()), //防御力
			std::atoi(GMp->SPp->datas[0][5].c_str()), //攻撃速度
		};

		return;
	}
	
	//名前読み込み
	fread_s(name, sizeof(name), sizeof(char) * name_length, 1, fp);

	//ステータス読み込み
	fread_s(status, sizeof(status), sizeof(int) * status_value, 1, fp);

	sta.HP           = status[0];
	sta.move_speed   = status[1];
	sta.attack       = status[2];
	sta.defense      = status[3];
	sta.attack_speed = status[4];

	fclose(fp);
}


//削除
void Player::isDelete() {

	if (sta.HP <= 0) { alive_flag = false; }

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
}


//----------------------------------------------------------------------------------------------------
//撃つ
void Player::FireBullet(float deltatime) {

	if (secconds_AS > timecount) { return; }

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

	if (GMp->SRp->_switch) {

		GMp->SPp->SavePlayer(); 
		alive_flag = false; 
	}
}
void Player::Render(Camera* cam) {

	t2k::Vector3 pos_ = GMp->SPp->FixPositionVector(pos);

	DrawRotaGraph(pos_.x, pos_.y, 1.0, 0, chara_handle, 1);

	DrawFormatString(100, 100, -1, "x:%f y:%f", pos.x, pos.y);
	DrawFormatString(100, 120, -1, "名前:%s", name);
	DrawFormatString(100, 140, -1, "HP:%d", _hp);
	DrawFormatString(100, 160, -1, "移動速度:%d", sta.move_speed);
	DrawFormatString(100, 180, -1, "攻撃力:%d", sta.attack);
	DrawFormatString(100, 200, -1, "防御力:%d", sta.defense);
	DrawFormatString(100, 220, -1, "攻撃速度:%d", sta.attack_speed);
}

//----------------------------------------------------------------------------------------------------