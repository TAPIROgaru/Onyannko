#include "Enemy.h"

#include "GameManager.h"

extern GameManager* GMp;

//----------------------------------------------------------------------------------------------------
//コンストラクタ
Enemy::Enemy(int num) {

	pos = { 200, 0, 0 };

	LoadStatus(num);

}
//デストラクタ
Enemy::~Enemy() {

}


//----------------------------------------------------------------------------------------------------
//
void Enemy::Move(float deltatime) {


}


//----------------------------------------------------------------------------------------------------
//
void Enemy::LoadStatus(int num) {

	std::vector<std::vector<std::string>>datas;
	datas = t2k::loadCsv("Charactor_Status.csv");

	int i = 0;

	//名前読み込み
	for (i = 0; i < name_length; i++) {

		name[i] = datas[num][0].c_str()[i];

		if ('\0' == datas[num][0].c_str()[i]) {

			break;
		}
	}

	//ステータス読み込み
	sta = {
		std::atoi(datas[num][1].c_str()), //ヒットポイント
		std::atoi(datas[num][2].c_str()), //移動速度
		std::atoi(datas[num][3].c_str()), //攻撃力
		std::atoi(datas[num][4].c_str()), //防御力
		std::atoi(datas[num][5].c_str()), //攻撃速度
	};
}


//----------------------------------------------------------------------------------------------------
//毎フレーム呼び出し

void Enemy::Update(float deltatime) {


}
void Enemy::Render(Camera* cam) {

	t2k::Vector3 pos_ = GMp->SPp->FixPositionVector(pos);

	DrawCircle(pos_.x, pos_.y, 20, -1, true);

	DrawFormatString(600, 100, -1, "x:%f y:%f", pos.x, pos.y);
	DrawFormatString(600, 120, -1, "名前:%s", name);
	DrawFormatString(600, 140, -1, "HP:%d", sta.HP);
	DrawFormatString(600, 160, -1, "移動速度:%d", sta.move_speed);
	DrawFormatString(600, 180, -1, "攻撃力:%d", sta.attack);
	DrawFormatString(600, 200, -1, "防御力:%d", sta.defense);
	DrawFormatString(600, 220, -1, "攻撃速度:%d", sta.attack_speed);
}

//----------------------------------------------------------------------------------------------------