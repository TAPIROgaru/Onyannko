#include "PlayScene.h"
#include "Camera.h"
#include "GameManager.h"
#include "Player.h"
#include "Square.h"
#include "ResultScene.h"
#include "TPRlib/tpr_library.h"


extern GameManager* GMp;

//----------------------------------------------------------------------------------------------------
//�R���X�g���N�^
PlayScene::PlayScene() {

	datas = GMp->datas;

	map = t2k::loadCsv("BackGround.csv");
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

	//Square�|�C���^�^�̃��X�g
	std::list<Square*>::iterator Spit = Sp.begin();
	while (Spit != Sp.end()) {
		if (!(*Spit)->alive_flag) {

			Spit = Sp.erase(Spit);
			continue;
		}
		Spit++;
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

	//Player�|�C���^
	if (!Pp->alive_flag) {

		delete (Pp);
		Pp = nullptr;
	}

	//Enemy�|�C���^
	if (!Ep->alive_flag) {

		delete (Ep);
		Ep = nullptr;
	}
}


//----------------------------------------------------------------------------------------------------
//�w�i
void PlayScene::LoadBuckGround() {

	float x = -GMp->TILE_SIZE_W * 3;
	float y = -GMp->TILE_SIZE_H * 3;

	int _y = 0;

	for (auto i : map) {
		x = -GMp->TILE_SIZE_W * 3;

		std::vector<int> map_y;

		for (auto k : i) {

			int img = 0;
			int num = std::atoi(k.c_str());

			switch (num) {

			case FLOOR:
				img = GMp->loadGraph("graphics/kusa.png");

				map_y.emplace_back(2);

				break;

			case OUTSIDE_WALL:
			case INSIDE_WALL:
				img = GMp->loadGraph("graphics/shasen.png");

				break;

			case ROCK:
				img = GMp->loadGraph("graphics/isi.png");

				map_y.emplace_back(3);

				break;

			default:
				break;
			}

			Square* sp = new Square(
				t2k::Vector3(x, y, 0),
				img
			);

			Op.emplace_back(sp);
			Sp.emplace_back(sp);

			if (num == ROCK || num == INSIDE_WALL) {
				Sp_wall.emplace_back(sp);
			}

			x += GMp->TILE_SIZE_W;
		}
		y += GMp->TILE_SIZE_H;

		if (!map_y.empty()) {
			astar_map.emplace_back(map_y);
		}
	}
}


//----------------------------------------------------------------------------------------------------
//�X�^�[�g
void PlayScene::Start(float deltatime) {

	if (!_switch || count >= 5) { return; }

	count += deltatime;

	if (count < 3) { return; }

	if (count < 5) { _start_flag = true; return; }
}


//----------------------------------------------------------------------------------------------------
//�Z�[�u
void PlayScene::SavePlayer() {

	FILE* fp = nullptr;

	fopen_s(&fp, "player.bin", "wb");

	fwrite(Pp->name, sizeof(Pp->name), 1, fp);
	fwrite(&Pp->sta.HP, sizeof(int), 1, fp);
	fwrite(&Pp->sta.move_speed, sizeof(int), 1, fp);
	fwrite(&Pp->sta.attack, sizeof(int), 1, fp);
	fwrite(&Pp->sta.defense, sizeof(int), 1, fp);
	fwrite(&Pp->sta.attack_speed, sizeof(int), 1, fp);
	fwrite(&Pp->ult->my_number, sizeof(int), 1, fp);
	fwrite(&Pp->skillA->my_number, sizeof(int), 1, fp);
	fwrite(&Pp->skillB->my_number, sizeof(int), 1, fp);

	fclose(fp);
}


//----------------------------------------------------------------------------------------------------
//�Q�[���I�[�o�[
void PlayScene::isOver() {

	if (Pp->sta.hp_ == 0 || Ep->sta.hp_ == 0) {

		GMp->SRp->_switch = true;
	}
}


//----------------------------------------------------------------------------------------------------
//�����蔻��

void PlayScene::isHit_bullet() {

	for (auto p : Bp) {
		if (p->_team) {
			if (tpr::isHit_CircleAndCircle(
				tpr::Vector2(Ep->pos.x, Ep->pos.y),Ep->r,
				tpr::Vector2(p->pos.x, p->pos.y), p->r)) {

				Ep->sta.hp_--;
				p->alive_flag = false;
			}
		}
		else if (!p->_team) {
			if (tpr::isHit_CircleAndCircle(
				tpr::Vector2(Pp->pos.x, Pp->pos.y), Pp->r,
				tpr::Vector2(p->pos.x, p->pos.y), p->r)) {

				Pp->sta.hp_--;
				p->alive_flag = false;
			}
		}
	}
}

bool PlayScene::isHit_Wall(t2k::Vector3 pos, float r) {

	for (auto p : Sp_wall) {

		float x = p->pos.x + (p->size_w_ >> 1);
		float y = p->pos.y + (p->size_h_ >> 1);
		t2k::Vector3 box_pos = { x, y, 0 };

		t2k::Vector3 pos_ = t2k::getNearestRectPoint(
			box_pos,
			p->size_w_,
			p->size_h_,
			pos
		);

		if (isHit_DotAndCircle(pos_, pos, r)) { return true; }
	}

	return false;
}

void PlayScene::isHit_Wall(t2k::Vector3& pos, t2k::Vector3 prev_pos, float r) {

	//pos�ɋ߂����Ƀ\�[�g
	Sp_wall.sort([&](Square* l, Square* r) {
		float ld = (pos - l->pos).length();
		float rd = (pos - r->pos).length();
		return (ld < rd);
	});

	for (auto p : Sp_wall) {

		float x = p->pos.x + (p->size_w_ >> 1);
		float y = p->pos.y + (p->size_h_ >> 1);
		t2k::Vector3 box_pos = { x, y, 0 };

		t2k::Vector3 pos_ = t2k::getNearestRectPoint(
			box_pos,
			p->size_w_,
			p->size_h_,
			pos
		);

		if (isHit_DotAndCircle(pos_, pos, r)){

			int num = t2k::getRegionPointAndRect(prev_pos, t2k::Vector3(x, y, 0), p->size_w_, p->size_h_);

			isHit_ActionCorrectionPosition(pos, r, pos_, num);
		}
	}
}

inline bool PlayScene::isHit_DotAndCircle(t2k::Vector3 dot_pos, t2k::Vector3 cir_pos, float r) {

	float x = dot_pos.x - cir_pos.x;
	float y = dot_pos.y - cir_pos.y;

	if (x * x + y * y <= r * r) {

		return true;
	}

	return false;
}

inline void PlayScene::isHit_ActionCorrectionPosition(t2k::Vector3& pos, float r, t2k::Vector3 dot_pos, int num) {

	const int HIT_UP = 2;     //��ɓ�������
	const int HIT_DOWN = 0;   //���ɓ�������
	const int HIT_RIGHT = 3;  //�E�ɓ�������
	const int HIT_LEFT = 1;   //���ɓ�������

	//���ɕ␳
	if (num == HIT_UP) {

		pos.y = (dot_pos.y + 1 + r);
	}
	//��ɕ␳
	if (num == HIT_DOWN) {

		pos.y = (dot_pos.y - 1 - r);
	}
	//���ɕ␳
	if (num == HIT_RIGHT) {

		pos.x = (dot_pos.x - 1 - r);
	}
	//�E�̕␳
	if (num == HIT_LEFT) {

		pos.x = (dot_pos.x + 1 + r);
	}
}

bool PlayScene::isHit_RayAndWall() {

	tpr::Vector2 e_pos = FixPositionVector(tpr::Vector2(Ep->pos.x, Ep->pos.y));
	tpr::Vector2 p_pos = FixPositionVector(tpr::Vector2(Pp->pos.x, Pp->pos.y));

	//Player��Enemy���Ȃ���`
	tpr::Quadrilateral ray_quad(e_pos, p_pos, GMp->BULLET_RADIUS * 2);

	auto p = Sp_wall.begin();
	while (p != Sp_wall.end()) {

		//Square�̍��W�f�[�^���l�ӌ`�ɂ���

		t2k::Vector3 pos = FixPositionVector((*p)->pos);
		tpr::Vector2 pos_(pos.x + (GMp->TILE_SIZE_W >> 1), pos.y + (GMp->TILE_SIZE_H >> 1));
		tpr::Quadrilateral quad(pos_, (*p)->size_w_, (*p)->size_h_);

		if (tpr::isHit_RectangleAndRectangle(ray_quad, quad)) { return true; }

		p++;
	}

	return false;
}


//----------------------------------------------------------------------------------------------------
//Astar�p��Player��Enemy�̓񎟌����W�쐻

void PlayScene::MakeVector2(tpr::Vector2_int* p_pos, tpr::Vector2_int* e_pos) {

	*p_pos = tpr::Vector2_int{
		(int)Pp->pos.x / GMp->TILE_SIZE_W,
		(int)Pp->pos.y / GMp->TILE_SIZE_H
	};

	*e_pos = tpr::Vector2_int{
		(int)Ep->pos.x / GMp->TILE_SIZE_W,
		(int)Ep->pos.y / GMp->TILE_SIZE_H
	};
}


//----------------------------------------------------------------------------------------------------
// Enemy���n�_�APlayer���I�_�Ƃ����x�N�g���̒P�ʃx�N�g���𓾂�

tpr::Vector2 PlayScene::Normalize() {

	tpr::Vector2 v = tpr::Vector2(Pp->pos.x - Ep->pos.x, Pp->pos.y - Ep->pos.y);

	float magnitude = sqrtf(v.x * v.x + v.y * v.y);

	tpr::Vector2 norm(v.x / magnitude, v.y / magnitude);

	return norm;
}

//----------------------------------------------------------------------------------------------------
//�e�쐬

void PlayScene::MakeBullet(t2k::Vector3 pos, float direction_x, float direction_y, bool t) {

	Bullet* bp = new Bullet(pos.x, pos.y, direction_x, direction_y, t);
	Bp.emplace_back(bp);
	Op.emplace_back(bp);
}


//----------------------------------------------------------------------------------------------------
//�J�������l�������}�E�X���W�̎擾

t2k::Vector3 PlayScene::GetMousePosition() {

	int x, y;
	GetMousePoint(&x, &y);

	t2k::Vector3 pos = { 0,0,0 };

	//�J�������l��
	pos.x = x + cam.pos.x - (GameManager::SCREEN_W >> 1);
	pos.y = y + cam.pos.y - (GameManager::SCREEN_H >> 1);

	return pos;
}

//�J�������l���������W�̎擾

t2k::Vector3 PlayScene::FixPositionVector(t2k::Vector3 pos) {

	t2k::Vector3 pos_ = {
		pos.x - cam.pos.x + (GameManager::SCREEN_W >> 1),
		pos.y - cam.pos.y + (GameManager::SCREEN_H >> 1),
		0
	};

	return pos_;
}

tpr::Vector2 PlayScene::FixPositionVector(tpr::Vector2 pos) {

	tpr::Vector2 pos_ = {
		pos.x - cam.pos.x + (GameManager::SCREEN_W >> 1),
		pos.y - cam.pos.y + (GameManager::SCREEN_H >> 1)
	};

	return pos_;
}


//----------------------------------------------------------------------------------------------------
//������
void PlayScene::Init() {

	if (!_init) { return; }

	LoadBuckGround();

	Pp = new Player();
	Op.emplace_back(Pp);

	Ep = new Enemy(1);
	Op.emplace_back(Ep);

	count = 0;
	_start_flag = false;

	_init = false;

	//�f�o�b�N�p
	Pp->sta.hp_ = 999;
	Ep->sta.hp_ = 999;
}


//----------------------------------------------------------------------------------------------------
//���t���[���Ăяo��
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

	tpr::Vector2_int m;
	GetMousePoint(&m.x, &m.y);

	tpr::Vector2 mf(m.x, m.y);

	DrawFormatString(200, 0, -1, "mx:%f my:%f", mf.x, mf.y);
}

//----------------------------------------------------------------------------------------------------