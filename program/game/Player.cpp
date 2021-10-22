#include "Player.h"

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

	fopen_s(&fp, "player.txt", "r");

	if (fp == NULL) {

		fopen_s(&fp, "player.txt", "w");
	}

	fclose(fp);
}

//----------------------------------------------------------------------------------------------------
//������
void Player::Move() {

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
}

//----------------------------------------------------------------------------------------------------
//

//----------------------------------------------------------------------------------------------------
//���t���[���Ăяo��

void Player::Update(float deltatime) {

	Move();
}
void Player::Render(Camera* cam) {

	DrawCircle(pos.x, pos.y, 20, -1, true);
}

//----------------------------------------------------------------------------------------------------