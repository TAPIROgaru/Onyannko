#include "Player.h"
#include "GameManager.h"


#define PI 3.14159265359f

extern GameManager* GMp;

//----------------------------------------------------------------------------------------------------
//�R���X�g���N�^
Player::Player() {

	pos = t2k::Vector3(0, 0, 0);
	LoadStatus();

	secconds_AS = 1.0f / sta.attack_speed;
	img = LoadGraph("graphics/AIM.png");
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

	char buff[name_length] = { 0 };
	int status[status_value] = { 0 };

	fopen_s(&fp, "player.bin", "rb");

	//�o�C�i���t�@�C�����Ȃ�������
	if (fp == NULL) {

		std::vector<std::vector<std::string>>datas;
		datas = t2k::loadCsv("Charactor_Status.csv");

		int i = 0;

		//���O�ǂݍ���
		for (i = 0; i < name_length; i++) {

			name[i] = datas[0][0].c_str()[i];

			if ('\0' == datas[0][0].c_str()[i]) {

				break;
			}
		}

		//�X�e�[�^�X�ǂݍ���
		sta = {
			std::atoi(datas[0][1].c_str()), //�q�b�g�|�C���g
			std::atoi(datas[0][2].c_str()), //�ړ����x
			std::atoi(datas[0][3].c_str()), //�U����
			std::atoi(datas[0][4].c_str()), //�h���
			std::atoi(datas[0][5].c_str()), //�U�����x
		};

		return;
	}
	
	//���O�ǂݍ���
	fread_s(name, sizeof(name), sizeof(char) * name_length, 1, fp);

	//�X�e�[�^�X�ǂݍ���
	fread_s(status, sizeof(status), sizeof(int) * status_value, 1, fp);
	//memcpy( &sta, status, sizeof(status) );

	sta.HP           = status[0];
	sta.move_speed   = status[1];
	sta.attack       = status[2];
	sta.defense      = status[3];
	sta.attack_speed = status[4];

	fclose(fp);
}


//----------------------------------------------------------------------------------------------------
//������
void Player::Move(float deltatime) {

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
}


//----------------------------------------------------------------------------------------------------
//����
void Player::FireBullet(float deltatime) {

	if (secconds_AS > timecount) { return; }

	ShootDirection();

	GMp->SPp->MakeBullet(pos, bullet_direction_x, bullet_direction_y, angle);

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

}
void Player::Render(Camera* cam) {

	t2k::Vector3 pos_ = GMp->SPp->FixPositionVector(pos);

	int x, y;
	GetMousePoint(&x, &y);

	DrawRotaGraph(x, y, 0.05f, 0, img, true);

	DrawCircle(pos_.x, pos_.y, 20, -1, true);

	DrawFormatString(100, 100, -1, "x:%f y:%f", pos.x, pos.y);
	DrawFormatString(100, 120, -1, "���O:%s", name);
	DrawFormatString(100, 140, -1, "HP:%d", sta.HP);
	DrawFormatString(100, 160, -1, "�ړ����x:%d", sta.move_speed);
	DrawFormatString(100, 180, -1, "�U����:%d", sta.attack);
	DrawFormatString(100, 200, -1, "�h���:%d", sta.defense);
	DrawFormatString(100, 220, -1, "�U�����x:%d", sta.attack_speed);
}

//----------------------------------------------------------------------------------------------------