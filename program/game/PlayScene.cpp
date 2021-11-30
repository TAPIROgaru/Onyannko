#include "PlayScene.h"
#include "Camera.h"
#include "GameManager.h"
#include "Player.h"
#include "Square.h"


extern GameManager* GMp;

//----------------------------------------------------------------------------------------------------
//コンストラクタ
PlayScene::PlayScene() {

	datas = GMp->datas;

	map = t2k::loadCsv("BackGround.csv");
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

	//Squareポインタ型のリスト
	std::list<Square*>::iterator Spit = Sp.begin();
	while (Spit != Sp.end()) {
		if (!(*Spit)->alive_flag) {

			Spit = Sp.erase(Spit);
			continue;
		}
		Spit++;
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

	//Playerポインタ
	if (!Pp->alive_flag) {

		delete (Pp);
		Pp = nullptr;
	}

	//Enemyポインタ
	if (!Ep->alive_flag) {

		delete (Ep);
		Ep = nullptr;
	}
}


//----------------------------------------------------------------------------------------------------
//背景
void PlayScene::DrawBuckGround() {



	float x = -GMp->FIELD_W - 16 * 3;
	float y = -GMp->FIELD_H - 16 * 2;

	for (auto i : map) {
		x = -GMp->FIELD_W - 16 * 3;
		for (auto k : i) {

			int img = 0, type = 0;
			int num = std::atoi(k.c_str());

			switch (num) {

			case FLOOR:
				img = GMp->loadGraph("graphics/kusa.png");
				type = 2;

				break;

			case OUTSIDE_WALL:
			case INSIDE_WALL:
				img = GMp->loadGraph("graphics/shasen.png");
				type = 3;

				break;

			case ROCK:
				img = GMp->loadGraph("graphics/isi.png");
				type = 3;

				break;

			default:
				break;
			}

			Square* sp = new Square(
				t2k::Vector3(x, y, 0),
				img,
				type
			);

			Op.emplace_back(sp);
			Sp.emplace_back(sp);

			if (num == (ROCK || INSIDE_WALL)) {
				Sp_wall.emplace_back(sp);
			}

			x += 16;
		}
		y += 16;
	}
}


//----------------------------------------------------------------------------------------------------
//スタート
void PlayScene::Start(float deltatime) {

	if (!_switch || count >= 5) { return; }

	count += deltatime;

	if (count < 3) {

		DrawFormatString(0, 0, -1, "よーい　%f", count);
		return;
	}

	if (count < 5) {
		DrawString(0, 0, "スタート", -1);
		_start_flag = true;
		return;
	}
}


//----------------------------------------------------------------------------------------------------
//セーブ
void PlayScene::SavePlayer() {

	FILE* fp = nullptr;

	fopen_s(&fp, "player.bin", "wb");

	fwrite(Pp->name, sizeof(Pp->name), 1, fp);
	fwrite(&Pp->sta, sizeof(CharaObj::Status), 1, fp);
	fwrite(&Pp->ult->my_number, sizeof(int), 1, fp);
	fwrite(&Pp->skillA->my_number, sizeof(int), 1, fp);
	fwrite(&Pp->skillB->my_number, sizeof(int), 1, fp);

	fclose(fp);
}


//----------------------------------------------------------------------------------------------------
//ゲームオーバー
void PlayScene::isOver() {

	if (Pp->_hp == 0 || Ep->sta.HP == 0) {

		GMp->SRp->_switch = true;
	}
}


//----------------------------------------------------------------------------------------------------
//当たり判定

//弾
void PlayScene::isHit_bullet() {

	for (auto p : Bp) {
		if (p->_team) {
			if (CircleHit(Ep->pos.x, Ep->pos.y, Ep->r, p->pos.x, p->pos.y, p->r)) {
				Ep->sta.HP--;
				p->alive_flag = false;
			}
		}
		else if (!p->_team) {
			if (CircleHit(Pp->pos.x, Pp->pos.y, Pp->r, p->pos.x, p->pos.y, p->r)) {
				Pp->_hp--;
				p->alive_flag = false;
			}
		}
	}
}

//壁の当たり判定
int PlayScene::isHit_wall(t2k::Vector3 pos, float r) {

	//posに近い順にソート
	Sp_wall.sort([&](Square* l, Square* r) {
		float ld = (pos - l->pos).length();
		float rd = (pos - r->pos).length();
		return (ld < rd);
	});

	for (auto p : Sp_wall) {

		float x = p->pos.x + (p->size_w_ >> 1);
		float y = p->pos.y + (p->size_h_ >> 1);

		t2k::Vector3 pos_ = t2k::getNearestRectPoint(
			t2k::Vector3(x, y, 0),
			p->size_w_,
			p->size_h_,
			pos
		);

		if (isHit_DotAndCircle(pos_, pos, r)) {

			int num = t2k::getRegionPointAndRect(pos_, t2k::Vector3(x, y, 0), p->size_w_, p->size_h_);

			return num;
		}
	}

	return 4;
}

//点と円の当たり判定
bool PlayScene::isHit_DotAndCircle(t2k::Vector3 dot_pos, t2k::Vector3 cir_pos, float r) {

	float x = dot_pos.x - cir_pos.x;
	float y = dot_pos.y + cir_pos.y;

	if (x * x + y * y <= r * r) {

		return true;
	}

	return false;
}

//壁や障害物の当たり判定(座標補正もする)　※円と点のみ
void PlayScene::ActionCorrectionPosition(t2k::Vector3& pos, t2k::Vector3 prev_pos, float r) {

	const int HIT_UP = 2;
	const int HIT_DOWN = 0;
	const int HIT_RIGHT = 3;
	const int HIT_LEFT = 1;
	const int NO_HIT = 4;

	int num = isHit_wall(pos, r);

	//当たってない
	if (num == NO_HIT) { return; }

	//上
	if (num == HIT_UP) {

		float y = (prev_pos - pos).y;

		if (y < 0) {

			pos.y = prev_pos.y;
		}
	}
	//下
	if (num == HIT_DOWN) {

		float y = (prev_pos - pos).y;

		if (y > 0) {

			pos.y = prev_pos.y;
		}

	}
	//右
	if (num == HIT_RIGHT) {

		float x = (prev_pos - pos).x;

		if (x < 0) {

			pos.x = prev_pos.x;
		}
	}
	//左
	if (num == HIT_LEFT) {

		float x = (prev_pos - pos).x;

		if (x > 0) {

			pos.x = prev_pos.x;
		}
	}
}


//----------------------------------------------------------------------------------------------------
//弾作成
void PlayScene::MakeBullet(t2k::Vector3 pos, float direction_x, float direction_y, bool t) {

	Bullet* bp = new Bullet(pos.x, pos.y, direction_x, direction_y, t);
	Bp.emplace_back(bp);
	Op.emplace_back(bp);
}


//----------------------------------------------------------------------------------------------------
//カメラを考慮したマウス座標の取得
t2k::Vector3 PlayScene::GetMousePosition() {

	int x, y;
	GetMousePoint(&x, &y);

	t2k::Vector3 pos = { 0,0,0 };

	//カメラを考慮
	pos.x = x + cam.pos.x - (GameManager::SCREEN_W >> 1);
	pos.y = y + cam.pos.y - (GameManager::SCREEN_H >> 1);

	return pos;
}

//カメラを考慮した座標の取得
t2k::Vector3 PlayScene::FixPositionVector(t2k::Vector3 pos) {

	t2k::Vector3 pos_ = {
		pos.x - cam.pos.x + (GameManager::SCREEN_W >> 1),
		pos.y - cam.pos.y + (GameManager::SCREEN_H >> 1),
		0
	};

	return pos_;
}


//----------------------------------------------------------------------------------------------------
//初期化
void PlayScene::Init() {

	if (!_init) { return; }

	DrawBuckGround();

	Pp = new Player();
	Op.emplace_back(Pp);

	Ep = new Enemy(1);
	Op.emplace_back(Ep);

	count = 0;
	_start_flag = false;

	_init = false;
}


//----------------------------------------------------------------------------------------------------
//毎フレーム呼び出し
void PlayScene::Update(float deltatime) {

	Start(deltatime);

	Init();

	for (auto p : Op) {

		if (p->alive_flag) { p->Update(deltatime); }
	}

	cam.update(deltatime, Pp->pos);

	isHit_bullet();

	Delete();

	isOver();
}
void PlayScene::Render(float deltatime) {

	for (auto p : Op) {

		if (p->alive_flag) { p->Render(&cam); }
	}

	cam.render();
}

//----------------------------------------------------------------------------------------------------