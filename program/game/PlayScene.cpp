#include "PlayScene.h"
#include "Camera.h"
#include "GameManager.h"
#include "Player.h"


extern GameManager* GMp;

//----------------------------------------------------------------------------------------------------
//�R���X�g���N�^
PlayScene::PlayScene() {

	Pp = new Player();
	Op.emplace_back(Pp);
}


//----------------------------------------------------------------------------------------------------
//����
void PlayScene::Delete() {

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
//�Z�[�u
void PlayScene::SavePlayer() {

	FILE* fp = nullptr;

	fopen_s(&fp, "player.bin", "wb");

	fwrite(Pp->name, sizeof(Pp->name), 1, fp);
	fwrite(&Pp->sta, sizeof(CharaObj::Status), 1, fp);

	fclose(fp);
}


//----------------------------------------------------------------------------------------------------
//�e�쐬
void PlayScene::MakeBullet(t2k::Vector3 pos, float direction_x, float direction_y, float a) {

	Bullet* bp = new Bullet(pos.x, pos.y, direction_x, direction_y, a);
	Bp.emplace_back(bp);
	Op.emplace_back(bp);
}


//----------------------------------------------------------------------------------------------------
//���t���[���Ăяo��

void PlayScene::Update(float deltatime) {

	cam.pos += (Pp->pos - cam.pos) * 0.1f;
}
void PlayScene::Render(Camera* cam) {


}

//----------------------------------------------------------------------------------------------------