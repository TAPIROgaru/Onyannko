#include "Player.h"
#include "GameManager.h"


#define PI 3.14159265359f

extern GameManager* GMp;

//----------------------------------------------------------------------------------------------------
//�R���X�g���N�^
Player::Player() {

	_team = true;
	pos = { -200, 0, 0 };
	LoadStatus();
	r = 18;
	_hp = sta.HP;

	secconds_AS = 1.0f / sta.attack_speed;
}


//----------------------------------------------------------------------------------------------------
//�f�X�g���N�^
Player::~Player() {
}


//----------------------------------------------------------------------------------------------------
//�t�@�C���ǂݍ���
void Player::LoadStatus() {

	FILE* fp = nullptr;

	int status[status_value] = { 0 };

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
			std::atoi(GMp->SPp->datas[0][1].c_str()), //�q�b�g�|�C���g
			std::atoi(GMp->SPp->datas[0][2].c_str()), //�ړ����x
			std::atoi(GMp->SPp->datas[0][3].c_str()), //�U����
			std::atoi(GMp->SPp->datas[0][4].c_str()), //�h���
			std::atoi(GMp->SPp->datas[0][5].c_str()), //�U�����x
		};

		return;
	}
	
	//���O�ǂݍ���
	fread_s(name, sizeof(name), sizeof(char) * name_length, 1, fp);

	//�X�e�[�^�X�ǂݍ���
	fread_s(status, sizeof(status), sizeof(int) * status_value, 1, fp);

	sta.HP           = status[0];
	sta.move_speed   = status[1];
	sta.attack       = status[2];
	sta.defense      = status[3];
	sta.attack_speed = status[4];

	fclose(fp);
}


//�폜
void Player::isDelete() {

	if (sta.HP <= 0) { alive_flag = false; }

}


//----------------------------------------------------------------------------------------------------
//������
void Player::Move(float deltatime) {

	if (!GMp->SPp->_start_flag || GMp->SRp->_switch) { return; }

	//��
	if (t2k::Input::isKeyDown(t2k::Input::KEYBORD_W)) {

		pos.y -= sta.move_speed;
		if (GMp->SPp->isHit_wall(pos.y,true)) {

		}
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

	if (GMp->SRp->_switch) {

		GMp->SPp->SavePlayer(); 
		alive_flag = false; 
	}
}
void Player::Render(Camera* cam) {

	t2k::Vector3 pos_ = GMp->SPp->FixPositionVector(pos);

	DrawRotaGraph(pos_.x, pos_.y, 1.0, 0, chara_handle, 1);

	DrawFormatString(100, 100, -1, "x:%f y:%f", pos.x, pos.y);
	DrawFormatString(100, 120, -1, "���O:%s", name);
	DrawFormatString(100, 140, -1, "HP:%d", _hp);
	DrawFormatString(100, 160, -1, "�ړ����x:%d", sta.move_speed);
	DrawFormatString(100, 180, -1, "�U����:%d", sta.attack);
	DrawFormatString(100, 200, -1, "�h���:%d", sta.defense);
	DrawFormatString(100, 220, -1, "�U�����x:%d", sta.attack_speed);
}

//----------------------------------------------------------------------------------------------------