#include "Player.h"


extern GameManager* GMp;

//----------------------------------------------------------------------------------------------------
//�R���X�g���N�^
Player::Player() {

	pos = t2k::Vector3(100, 100, 0);
	LoadStatus();
}

//----------------------------------------------------------------------------------------------------
//�t�@�C���ǂݍ���
void Player::LoadStatus() {

	FILE* fp = nullptr;
	char buff[256];

	fopen_s(&fp, "player.txt", "r");

	if (fp == NULL) { exit(1); }

	fseek(fp, 0, SEEK_END);
	int file_size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	//fread_s(&buff, sizeof(buff), file_size, 1, fp);

	fclose(fp);
}


//----------------------------------------------------------------------------------------------------
//������
void Player::Move(float deltatime) {

	//��
	if (t2k::Input::isKeyDown(t2k::Input::KEYBORD_W)) {

		pos.y -= move_speed;
	}

	//��
	if (t2k::Input::isKeyDown(t2k::Input::KEYBORD_A)) {

		pos.x -= move_speed;
	}

	//��
	if (t2k::Input::isKeyDown(t2k::Input::KEYBORD_S)) {

		pos.y += move_speed;
	}

	//�E
	if (t2k::Input::isKeyDown(t2k::Input::KEYBORD_D)) {

		pos.x += move_speed;
	}

	//�E�N���b�N
	if (true == (GetMouseInput() & MOUSE_INPUT_LEFT)) {

		FireBullet(deltatime);
	}
}


//----------------------------------------------------------------------------------------------------
//����
void Player::FireBullet(float deltatime) {

	timecount += deltatime;

	if (attack_speed > timecount) { return; }

	timecount = 0;

	GMp->MakeBullet(pos);
}

//----------------------------------------------------------------------------------------------------
//���t���[���Ăяo��

void Player::Update(float deltatime) {

	Move(deltatime);
}
void Player::Render(Camera* cam) {

	DrawCircle(pos.x, pos.y, 20, -1, true);
}

//----------------------------------------------------------------------------------------------------