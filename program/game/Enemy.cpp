#include <stdlib.h>

#include "Enemy.h"
#include "GameManager.h"
#include "PlayScene.h"
#include "ResultScene.h"

extern GameManager* GMp;

//----------------------------------------------------------------------------------------------------
//�R���X�g���N�^
Enemy::Enemy(int num) {

	_team = false;
	pos = {GameManager::START_POSITION_ENEMY_W,GameManager::START_POSITION_H , 0 };
	r = 16;
	LoadStatus(num);
	origin_sta = sta;

	secconds_AS = 1.0f / sta.attack_speed;

	astar = new tpr::Astar( GMp->SPp->astar_map);
}
//�f�X�g���N�^
Enemy::~Enemy() {

}


//----------------------------------------------------------------------------------------------------
//
void Enemy::Move(float deltatime) {

	//=====================================================================
	//�f�o�b�O�p

	if (!GMp->ENEMY_MODE) { return; }

	//=====================================================================

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

		GMp->SPp->isHit_Wall(pos, prev_pos, (float)r);

		if (_stun) {
			pos = prev_pos;
		}

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

		GMp->SPp->isHit_Wall(pos, prev_pos, (float)r);

		if (_stun) {
			pos = prev_pos;
		}

		prev_pos = pos;
		flame_count++;
	}
}


//----------------------------------------------------------------------------------------------------
//�X�e�[�^�X�ǂݍ���
void Enemy::LoadStatus(int num) {

	int i = 0;

	//���O�ǂݍ���
	for (i = 0; i < name_length; i++) {

		name[i] = GMp->SPp->datas[num][0].c_str()[i];

		if ('\0' == GMp->SPp->datas[num][0].c_str()[i]) {

			break;
		}
	}

	//�X�e�[�^�X�ǂݍ���
	sta = {
		std::atoi(GMp->SPp->datas[num][1].c_str()), //�q�b�g�|�C���g
		0,
		std::atoi(GMp->SPp->datas[num][2].c_str()), //�ړ����x
		std::atoi(GMp->SPp->datas[num][3].c_str()), //�U����
		std::atoi(GMp->SPp->datas[num][4].c_str()), //�h���
		std::atoi(GMp->SPp->datas[num][5].c_str()), //�U�����x
	};

	sta.hp_ = sta.HP;                               //��������HP

	//�摜
	chara_handle = GMp->loadGraph("graphics/Enemy.png");

	ult = new Scroll(rand() % 2, 'u', tpr::Vector2(pos.x, pos.y));

	//�����_���ȏ��ԂɃ\�[�g(�X�L���ԍ�)
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
//�v���C���[�Ƃ̋���
void Enemy::FindPlayer(float deltatime) {

	//=====================================================================
	//�f�o�b�O�p

	if (!GMp->ENEMY_MODE) { return; }

	//=====================================================================

	if (!GMp->SPp->_start_flag || GMp->SRp->_switch) { return; }
	if (_stun) { return; }

	//Player���W���擾
	t2k::Vector3 pos_ = GMp->SPp->Pp->pos;

	//Player�Ƃ̋���
	t2k::Vector3 component = pos_ - pos;

	//�P�ʃx�N�g��
	float magnitude = (float)sqrt(component.x * component.x + component.y * component.y);

	if (search_range_palyer < magnitude|| GMp->SPp->isHit_RayAndWall()) { 
		_fire = false; 
		return; 
	}

	int gap = 100;

	//�p�x�̌v�Z
	bullet_direction_x = (component.x + rand() % gap - gap / 2) / magnitude;
	bullet_direction_y = (component.y + rand() % gap - gap / 2) / magnitude;

	FireBullet(deltatime);
	_fire = true;
}


//----------------------------------------------------------------------------------------------------
//����
void Enemy::FireBullet(float deltatime) {

	if (secconds_AS > timecount) { return; }

	GMp->SPp->MakeBullet(pos, bullet_direction_x, bullet_direction_y, _team);

	timecount = 0;
}


//----------------------------------------------------------------------------------------------------
//���t���[���Ăяo��

void Enemy::Update(float deltatime) {

	timecount += deltatime;

	ult->Update(deltatime, tpr::Vector2(pos.x, pos.y));
	skillA->Update(deltatime, tpr::Vector2(pos.x, pos.y));
	skillB->Update(deltatime, tpr::Vector2(pos.x, pos.y));

	Move(deltatime);
	FindPlayer(deltatime);
}
void Enemy::Render(Camera* cam) {

	t2k::Vector3 pos_ = GMp->SPp->FixPositionVector(pos);

	ult->Render(cam);
	skillA->Render(cam);
	skillB->Render(cam);

	DrawRotaGraph((int)pos_.x, (int)pos_.y, 1.0, 0, chara_handle, 1);

	HP.DrawGauge(tpr::Vector2(pos_.x, pos_.y - 20), 0, (float)sta.HP, (float)sta.hp_);

	//=====================================================================
	//�f�o�b�O�p

	if (!GameManager::DEBUG_MODE) { return; }

	auto p = move_pos.begin();
	int i = 0;
	while (p != move_pos.end()) {

		t2k::Vector3 _pos = GMp->SPp->FixPositionVector(
			t2k::Vector3{ (float)move_pos[i].x ,(float)move_pos[i].y ,0 });

		DrawGraph((int)_pos.x, (int)_pos.y, astar->img, true);

		i++;
		p++;
	}
	//=====================================================================
}

//----------------------------------------------------------------------------------------------------