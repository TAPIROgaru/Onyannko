#include "Enemy.h"

#include "GameManager.h"

extern GameManager* GMp;

//----------------------------------------------------------------------------------------------------
//�R���X�g���N�^
Enemy::Enemy(int num) {

	_team = false;
	pos = { 200, 0, 0 };
	r = 18;
	LoadStatus(num);

	secconds_AS = 1.0f / sta.attack_speed;
}
//�f�X�g���N�^
Enemy::~Enemy() {

}


//----------------------------------------------------------------------------------------------------
//
void Enemy::Move(float deltatime) {

	if (!GMp->SPp->_start_flag || GMp->SRp->_switch) { return; }

}


//----------------------------------------------------------------------------------------------------
//
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
		std::atoi(GMp->SPp->datas[num][2].c_str()), //�ړ����x
		std::atoi(GMp->SPp->datas[num][3].c_str()), //�U����
		std::atoi(GMp->SPp->datas[num][4].c_str()), //�h���
		std::atoi(GMp->SPp->datas[num][5].c_str()), //�U�����x
	};

	//�摜
	chara_handle = LoadGraph(GMp->SPp->datas[num][6].c_str());
}


//----------------------------------------------------------------------------------------------------
//���t���[���Ăяo��

void Enemy::Update(float deltatime) {

	if (GMp->SRp->_switch) { alive_flag = false; }
}
void Enemy::Render(Camera* cam) {

	t2k::Vector3 pos_ = GMp->SPp->FixPositionVector(pos);

	DrawRotaGraph(pos_.x, pos_.y, 1.0, 0, chara_handle, 1);

	DrawFormatString(600, 100, -1, "x:%f y:%f"  , pos.x, pos.y);
	DrawFormatString(600, 120, -1, "���O:%s"    , name);
	DrawFormatString(600, 140, -1, "HP:%d"      , sta.HP);
	DrawFormatString(600, 160, -1, "�ړ����x:%d", sta.move_speed);
	DrawFormatString(600, 180, -1, "�U����:%d"  , sta.attack);
	DrawFormatString(600, 200, -1, "�h���:%d"  , sta.defense);
	DrawFormatString(600, 220, -1, "�U�����x:%d", sta.attack_speed);
}

//----------------------------------------------------------------------------------------------------