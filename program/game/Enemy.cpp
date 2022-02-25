#include <stdlib.h>

#include "Enemy.h"
#include "GameManager.h"
#include "PlayScene.h"
#include "ResultScene.h"

extern GameManager* GMp;

//----------------------------------------------------------------------------------------------------
//コンストラクタ
Enemy::Enemy(int num) {

	_team = false;
	pos = { GMp->FIELD_W / 2 + 300, GMp->FIELD_H / 2 , 0 };
	r = 16;
	LoadStatus(num);

	secconds_AS = 1.0f / sta.attack_speed;

	astar = new tpr::Astar( GMp->SPp->astar_map);
}
//デストラクタ
Enemy::~Enemy() {

}


//----------------------------------------------------------------------------------------------------
//
void Enemy::Move(float deltatime) {

	if (!GMp->SPp->_start_flag || GMp->SRp->_switch) { return; }

	if (flame_count % 3 == 0) {

		if (_astar_falg) {

			auto p = move_pos.begin();

			move_pos.clear();
			route.clear();

			tpr::Vector2_int p_pos;
			tpr::Vector2_int e_pos;

			GMp->SPp->MakeVector2(&p_pos, &e_pos);

			route = astar->Astar_Exe(p_pos, e_pos);

			std::list<tpr::Node*>::iterator route_it = route.begin();
			while (route_it != route.end()) {

				move_pos.emplace_back(
					(*route_it)->pos.x * GMp->TILE_SIZE_W,
					(*route_it)->pos.y * GMp->TILE_SIZE_H
				);
				route_it++;
			}
		}
	}

	if (move_pos.empty()) {
		return; 
	}
	else if (move_pos.size() == 1) {
		move_count = 0;
	}

	if (!_fire) {

		t2k::Vector3 _pos = GMp->SPp->FixPositionVector(
			t2k::Vector3{ (float)move_pos[move_count].x + 16 ,(float)move_pos[move_count].y + 16 ,0 });

		t2k::Vector3 my_pos = GMp->SPp->FixPositionVector(pos);

		t2k::Vector3 component = {
			_pos.x - my_pos.x ,
			_pos.y - my_pos.y ,
			0
		};


		float magnitude = (float)sqrt(component.x * component.x + component.y * component.y);

		t2k::Vector3 move_dire = { (component.x / magnitude),(component.y / magnitude),0 };

		pos += {move_dire.x* sta.move_speed, move_dire.y* sta.move_speed, 0};

		GMp->SPp->isHit_Wall(pos, prev_pos, r);

		prev_pos = pos;
		flame_count++;
		move_count = 1;
	}
	else {

		if (flame_count % 10 == 0) {
			tpr::Vector2 v(1, 1);
			int num = rand() % 2;

			if (num == 0) {
				v = tpr::Vector2(1, -1);
			}
			else if (num == 1) {
				v = tpr::Vector2(-1, 1);
			}

			tpr::Vector2 norm = GMp->SPp->Normalize();

			avo_dire = tpr::Vector2(norm.y * v.x, norm.x * v.y);
		}

		pos += {avo_dire.x* sta.move_speed, avo_dire.y* sta.move_speed, 0};

		GMp->SPp->isHit_Wall(pos, prev_pos, r);

		if (_stun) {
			pos = prev_pos;
		}

		prev_pos = pos;
		flame_count++;
	}
}


//----------------------------------------------------------------------------------------------------
//ステータス読み込み
void Enemy::LoadStatus(int num) {

	int i = 0;

	//名前読み込み
	for (i = 0; i < name_length; i++) {

		name[i] = GMp->SPp->datas[num][0].c_str()[i];

		if ('\0' == GMp->SPp->datas[num][0].c_str()[i]) {

			break;
		}
	}

	//ステータス読み込み
	sta = {
		std::atoi(GMp->SPp->datas[num][1].c_str()), //ヒットポイント
		sta.HP,                                     //増減するHP
		std::atoi(GMp->SPp->datas[num][2].c_str()), //移動速度
		std::atoi(GMp->SPp->datas[num][3].c_str()), //攻撃力
		std::atoi(GMp->SPp->datas[num][4].c_str()), //防御力
		std::atoi(GMp->SPp->datas[num][5].c_str()), //攻撃速度
	};

	//画像
	chara_handle = GMp->loadGraph("graphics/Enemy.png");

	ult = new Scroll(rand() % 2, 'u', tpr::Vector2(pos.x, pos.y));

	//ランダムな順番にソート(スキル番号)
	int arry[6] = { 3,4,5,6,7,8 };
	for (int i = 0; i < 10; i++) {

		int numA = rand() % 6;
		int A = arry[numA];

		int numB = rand() % 6;
		arry[numA] = arry[numB];

		arry[numB] = A;
	}

	skillA = new Scroll(arry[0], 'a', tpr::Vector2(pos.x, pos.y));
	skillB = new Scroll(arry[1], 'b', tpr::Vector2(pos.x, pos.y));
}


//----------------------------------------------------------------------------------------------------
//プレイヤーとの距離
void Enemy::FindPlayer(float deltatime) {

	if (!GMp->SPp->_start_flag || GMp->SRp->_switch) { return; }

	//Player座標を取得
	t2k::Vector3 pos_ = GMp->SPp->Pp->pos;

	//Playerとの距離
	t2k::Vector3 component = pos_ - pos;

	//単位ベクトル
	float magnitude = (float)sqrt(component.x * component.x + component.y * component.y);

	if (search_range_palyer < magnitude|| GMp->SPp->isHit_RayAndWall()) { 
		_fire = false; 
		return; 
	}

	int gap = 100;

	//角度の計算
	bullet_direction_x = (component.x + rand() % gap - gap / 2) / magnitude;
	bullet_direction_y = (component.y + rand() % gap - gap / 2) / magnitude;

	FireBullet(deltatime);
	_fire = true;
}


//----------------------------------------------------------------------------------------------------
//撃つ
void Enemy::FireBullet(float deltatime) {

	if (secconds_AS > timecount) { return; }

	GMp->SPp->MakeBullet(pos, bullet_direction_x, bullet_direction_y, _team);

	timecount = 0;
}


//----------------------------------------------------------------------------------------------------
//毎フレーム呼び出し

void Enemy::Update(float deltatime) {

	timecount += deltatime;

	Move(deltatime);
	FindPlayer(deltatime);

	ult->Update(deltatime, tpr::Vector2(pos.x, pos.y));
	skillA->Update(deltatime, tpr::Vector2(pos.x, pos.y));
	skillB->Update(deltatime, tpr::Vector2(pos.x, pos.y));
}
void Enemy::Render(Camera* cam) {

	t2k::Vector3 pos_ = GMp->SPp->FixPositionVector(pos);

	//=====================================================================
	//Astarデバッグ用
	auto p = move_pos.begin();
	int i = 0;
	while (p != move_pos.end()) {

		t2k::Vector3 _pos = GMp->SPp->FixPositionVector(
			t2k::Vector3{ (float)move_pos[i].x ,(float)move_pos[i].y ,0 });

		DrawGraph(_pos.x, _pos.y, astar->img, true);

		i++;
		p++;
	}
	//=====================================================================

	ult->Render(cam);
	skillA->Render(cam);
	skillB->Render(cam);

	DrawRotaGraph(pos_.x, pos_.y, 1.0, 0, chara_handle, 1);

	//DrawFormatString(600, 100, -1, "x:%f y:%f"  , pos.x, pos.y);
	//DrawFormatString(600, 120, -1, "名前    :%s"    , name);
	//DrawFormatString(600, 140, -1, "HP      :%d"      , sta.hp_);
	//DrawFormatString(600, 160, -1, "移動速度:%d", sta.move_speed);
	//DrawFormatString(600, 180, -1, "攻撃力  :%d"  , sta.attack);
	//DrawFormatString(600, 200, -1, "防御力  :%d"  , sta.defense);
	//DrawFormatString(600, 220, -1, "攻撃速度:%d", sta.attack_speed);
	//DrawFormatString(600, 240, -1, "ult     :%d", ult->my_number);
	//DrawFormatString(600, 260, -1, "skillA  :%d", skillA->my_number);
	//DrawFormatString(600, 280, -1, "skillB  :%d", skillB->my_number);
}

//----------------------------------------------------------------------------------------------------