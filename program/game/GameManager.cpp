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
}
//----------------------------------------------------------------------------------------------------