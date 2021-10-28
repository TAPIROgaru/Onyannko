#include "Player.h"
#include "GameManager.h"

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

	char buff[name_length] = { 0 };
	int status[status_value] = { 0 };

	fopen_s(&fp, "player.bin", "rb");

	//�o�C�i���t�@�C�����Ȃ�������
	if (fp == NULL) {

		std::vector<std::vector<std::string>>datas;
		datas = t2k::loadCsv("Charactor_Status.csv");

		//���O�ǂݍ���
		for (int i = 0; i < name_length; i++) {

			sta.name[i] = datas[0][0].c_str()[i];

			if ('\0' == datas[0][0].c_str()[i]) {
				break;
			}
		}

		//�X�e�[�^�X�ǂݍ���
			

		return;
	}
	
	//���O�ǂݍ���
	fread_s(buff, sizeof(buff), sizeof(buff) * name_length, 1, fp);

	for (int i = 0; i < name_length;i++) {

		sta.name[i] = buff[i];
	}


	fseek(fp, 0, sizeof(buff) * name_length);

	//�X�e�[�^�X�ǂݍ���
	fread_s(status, sizeof(status), sizeof(status) * status_value, 1, fp);

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

	//�E�N���b�N
	if (true == (GetMouseInput() & MOUSE_INPUT_LEFT)) {

		FireBullet(deltatime);
	}
}


//----------------------------------------------------------------------------------------------------
//����
void Player::FireBullet(float deltatime) {

	timecount += deltatime;

	if (sta.attack_speed > timecount) { return; }

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