#include "PlayScene.h"
#include "Camera.h"
#include "GameManager.h"
#include "Player.h"


extern GameManager* GMp;

//----------------------------------------------------------------------------------------------------
//コンストラクタ
PlayScene::PlayScene() {

	Pp = new Player();
	Op.emplace_back(Pp);
}


//----------------------------------------------------------------------------------------------------
//消す
void PlayScene::Delete() {

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
//セーブ
void PlayScene::SavePlayer() {

	FILE* fp = nullptr;

	fopen_s(&fp, "player.bin", "wb");

	fwrite(Pp->name, sizeof(Pp->name), 1, fp);
	fwrite(&Pp->sta, sizeof(CharaObj::Status), 1, fp);

	fclose(fp);
}


//----------------------------------------------------------------------------------------------------
//弾作成
void PlayScene::MakeBullet(t2k::Vector3 pos, float direction_x, float direction_y, float a) {

	Bullet* bp = new Bullet(pos.x, pos.y, direction_x, direction_y, a);
	Bp.emplace_back(bp);
	Op.emplace_back(bp);
}


//----------------------------------------------------------------------------------------------------
//毎フレーム呼び出し

void PlayScene::Update(float deltatime) {

	cam.pos += (Pp->pos - cam.pos) * 0.1f;
}
void PlayScene::Render(Camera* cam) {


}

//----------------------------------------------------------------------------------------------------