#include "Player.h"
#include "GameManager.h"
#include "PlayScene.h"
#include "ResultScene.h"


#define PI 3.14159265359f

extern GameManager* GMp;

//----------------------------------------------------------------------------------------------------
//�R���X�g���N�^
Player::Player() {

	_team = true;
	pos = { GMp->FIELD_W / 2 - 200, GMp->FIELD_H / 2 , 0 };
	prev_pos = { -200, 0, 0 };
	LoadStatus();
	r = 16;

	secconds_AS = 1.0f / sta.attack_speed;
}


//----------------------------------------------------------------------------------------------------
//�f�X�g���N�^
Player::~Player() {

	GMp->SPp->SavePlayer();
}


//----------------------------------------------------------------------------------------------------
//�t�@�C���ǂݍ���
void Player::LoadStatus() {

	FILE* fp = nullptr;

	fopen_s(&fp, "player.bin", "rb");

	//�摜�ǂݍ���
	chara_handle = GMp->loadGraph("graphics/Player.png");

	//�o�C�i���t�@�C�����Ȃ�������
	if (fp == NULL) {

		int i = 0;

		//���O�ǂݍ���
		for (i = 0; i < name_length; i++) {

			name[i] = GMp->SPp->datas[0][0].c_str()[i];

			if ('\0' == GMp->SPp->datas[0][0].c_str()[i]) {

				break;
			}
		}

		//�X�e�[�^�X�ǂݍ���
		sta = {
			std::atoi(GMp->SPp->datas[0][0].c_str()), //�q�b�g�|�C���g
			sta.HP,                                   //��������HP
			std::atoi(GMp->SPp->datas[0][2].c_str()), //�ړ����x
			std::atoi(GMp->SPp->datas[0][3].c_str()), //�U����
			std::atoi(GMp->SPp->datas[0][4].c_str()), //�h���
			std::atoi(GMp->SPp->datas[0][5].c_str()), //�U�����x
		};

		//�X�L���ǂݍ���
		ult    = new Scroll(std::atoi(GMp->SPp->datas[0][6].c_str())
			, 'u', tpr::Vector2(pos.x, pos.y));
		skillA = new Scroll(std::atoi(GMp->SPp->datas[0][7].c_str())
			, 'a', tpr::Vector2(pos.x, pos.y));
		skillB = new Scroll(std::atoi(GMp->SPp->datas[0][8].c_str())
			, 'b', tpr::Vector2(pos.x, pos.y));

		return;
	}
	
	//���O�ǂݍ���
	fread_s(name, sizeof(name), sizeof(char) * name_length, 1, fp);


	int status[status_value - 1] = { 0 };

	//�X�e�[�^�X�ǂݍ���
	fread_s(status, sizeof(status), sizeof(int) * (status_value - 1), 1, fp);

	sta.HP           = status[0];
	sta.hp_          = sta.HP;
	sta.move_speed   = status[1];
	sta.attack       = status[2];
	sta.defense      = status[3];
	sta.attack_speed = status[4];

	//�X�L���ǂݍ���
	int num[3];
	fread_s(num, sizeof(num), sizeof(int) * 3, 1, fp);

	ult = new Scroll(num[0], 'u', tpr::Vector2(pos.x, pos.y));
	skillA = new Scroll(num[1], 'a', tpr::Vector2(pos.x, pos.y));
	skillB = new Scroll(num[2], 'b', tpr::Vector2(pos.x, pos.y));

	fclose(fp);
}


//----------------------------------------------------------------------------------------------------
//������
void Player::Move(float deltatime) {

	if (!GMp->SPp->_start_flag || GMp->SRp->_switch) { return; }

	//��
	if (t2k::Input::isKeyDown(t2k::Input::KEYBORD_W)) {

		pos.y -= sta.move_speed;
	}

	//��
	if (t2k::Input::isKeyDown(t2k::Input::KEYBORD_A)) {

		pos.x -= sta.move_speed;
	}

	//��
	if (t2k::Input::isKeyDown(t2k::Input::KEYBORD_S)) {

		pos.y += sta.move_speed;
	}

	//�E
	if (t2k::Input::isKeyDown(t2k::Input::KEYBORD_D)) {

		pos.x += sta.move_speed;
	}

	//���N���b�N
	if (true == (GetMouseInput() & MOUSE_INPUT_LEFT)) {

		FireBullet(deltatime);
	}

	//ult
	if (t2k::Input::isKeyReleaseTrigger(t2k::Input::KEYBORD_SPACE)) {

		ShootDirection();
		ult->Activate(tpr::Vector2(pos.x, pos.y), bullet_direction_x, bullet_direction_y, this);
	}

	//skillA
	if ( t2k::Input::isKeyReleaseTrigger(t2k::Input::KEYBORD_C)) {
		ShootDirection();
		skillA->Activate(tpr::Vector2(pos.x, pos.y), bullet_direction_x, bullet_direction_y, this);
	}

	//skillB
	if (t2k::Input::isKeyReleaseTrigger(t2k::Input::KEYBORD_V)) {
		ShootDirection();
		skillB->Activate(tpr::Vector2(pos.x, pos.y), bullet_direction_x, bullet_direction_y, this);
	}

	GMp->SPp->isHit_Wall(pos, prev_pos, r);

	if (_stun) {
		pos = prev_pos;
	}

	prev_pos = pos;
}


//----------------------------------------------------------------------------------------------------
//����
void Player::FireBullet(float deltatime) {

	if (secconds_AS > timecount) { return; }

	ShootDirection();

	GMp->SPp->MakeBullet(pos, bullet_direction_x, bullet_direction_y, true);

	timecount = 0;
}


//----------------------------------------------------------------------------------------------------
//���˂������
void Player::ShootDirection() {

	//�J�������W���l�������}�E�X���W���擾
	t2k::Vector3 mouse_pos = GMp->SPp->GetMousePosition();

	//Player�ƃ}�E�X�̋���
	t2k::Vector3 component = pos - mouse_pos;

	//�P�ʃx�N�g��
	magnitude = (float)sqrt(component.x * component.x + component.y * component.y);

	//�p�x�̌v�Z
	bullet_direction_x = component.x / magnitude * -1;
	bullet_direction_y = component.y / magnitude * -1;

	//�摜�p�x�̌v�Z
	angle = atan2f(bullet_direction_x, bullet_direction_y) + PI * 2;
}

//----------------------------------------------------------------------------------------------------
//���t���[���Ăяo��

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

	DrawRotaGraph(pos_.x, pos_.y, 1.0, 0, chara_handle, 1);

	ult->Render(cam);
	skillA->Render(cam);
	skillB->Render(cam);

	DrawFormatString(100, 100, -1, "x:%f y:%f", pos.x, pos.y);
	DrawFormatString(100, 120, -1, "���O    :%s", name);
	DrawFormatString(100, 140, -1, "HP      :%d", sta.hp_);
	DrawFormatString(100, 160, -1, "�ړ����x:%d", sta.move_speed);
	DrawFormatString(100, 180, -1, "�U����  :%d", sta.attack);
	DrawFormatString(100, 200, -1, "�h���  :%d", sta.defense);
	DrawFormatString(100, 220, -1, "�U�����x:%d", sta.attack_speed);
	DrawFormatString(100, 240, -1, "ult     :%d", ult->my_number);
	DrawFormatString(100, 260, -1, "skillA  :%d", skillA->my_number);
	DrawFormatString(100, 280, -1, "skillB  :%d", skillB->my_number);
}

//----------------------------------------------------------------------------------------------------