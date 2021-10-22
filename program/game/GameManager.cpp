#include"GameManager.h"


//----------------------------------------------------------------------------------------------------
//コンストラクタ
GameManager::GameManager() {


}

//初期化
void GameManager::Init() {

	Pp = new Player();
	Op.emplace_back(Pp);
}

//----------------------------------------------------------------------------------------------------
//消す
void GameManager::Delete() {

	//Bulletポインタ型のリスト
	std::list<Bullet*>::iterator Bpit = Bp.begin();
	while (Bpit != Bp.end()) {
		if (!(*Bpit)->alive_flag) {

			Bpit = Bp.erase(Bpit);
			continue;
		}
		Bpit++;
	}

	//Objectポインタ型のリスト
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
//毎フレーム呼び出し

void GameManager::Update(float deltatime) {

	if (_init) {

		Init();
		_init = false;
	}

	for (auto pointer : Op) {

		pointer->Update(deltatime);
	}
}
void GameManager::Render(float deltatime) {

	for (auto pointer : Op) {

		pointer->Render(&cam);
	}
}
//----------------------------------------------------------------------------------------------------