#include"GameManager.h"


//----------------------------------------------------------------------------------------------------
//�R���X�g���N�^
GameManager::GameManager() {


}

//������
void GameManager::Init() {

	Pp = new Player();
	Op.emplace_back(Pp);
}

//----------------------------------------------------------------------------------------------------
//����
void GameManager::Delete() {

	//Bullet�|�C���^�^�̃��X�g
	std::list<Bullet*>::iterator Bpit = Bp.begin();
	while (Bpit != Bp.end()) {
		if (!(*Bpit)->alive_flag) {

			Bpit = Bp.erase(Bpit);
			continue;
		}
		Bpit++;
	}

	//Object�|�C���^�^�̃��X�g
	std::list<Object*>::iterator Opit = Op.begin();
	while (Opit != Op.end()) {
		if (!(*Opit)->alive_flag) {

			delete (*Opit);
			Opit = Op.erase(Opit);
			continue;
		}
		Opit++;
	}
}


//----------------------------------------------------------------------------------------------------
//�e�쐬
void GameManager::MakeBullet(t2k::Vector3 pos) {

}


//----------------------------------------------------------------------------------------------------
//�Z�[�u
void GameManager::SavePlayer() {

	FILE* fp = nullptr;

	fopen_s(&fp, "player.bin", "wb");

	//fwrite(Pp->name, sizeof(Pp->name), 1, fp);

	//int status[5] = {
	//	Pp->HP,

	//};

	//fwrite(status, sizeof(status), 1, fp);

	fwrite(&Pp->sta, sizeof(CharaObj::Status), 1, fp);

	fclose(fp);
}


//----------------------------------------------------------------------------------------------------
//���t���[���Ăяo��

void GameManager::Update(float deltatime) {

	if (_init) {

		Init();
		_init = false;
	}

	for (auto pointer : Op) {

		pointer->Update(deltatime);
	}

	Delete();
}
void GameManager::Render(float deltatime) {

	for (auto pointer : Op) {

		pointer->Render(&cam);
	}

	DrawFormatString(100, 100, -1, "x:%f y:%f", Pp->pos.x, Pp->pos.y);
}
//----------------------------------------------------------------------------------------------------