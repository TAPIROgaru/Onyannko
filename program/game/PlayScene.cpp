#include "PlayScene.h"
#include "Camera.h"
#include "GameManager.h"
#include "Player.h"
#include "Square.h"


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
}


//----------------------------------------------------------------------------------------------------
//�w�i
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
//�X�^�[�g
void PlayScene::Start(float deltatime) {

	if (!_switch || count >= 5) { return; }

	count += deltatime;

	if (count < 3) {

		DrawFormatString(0, 0, -1, "��[���@%f", count);
		return;
	}

	if (count < 5) {
		DrawString(0, 0, "�X�^�[�g", -1);
		_start_flag = true;
		return;
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
//�Q�[���I�[�o�[
void PlayScene::isOver() {

	if (Pp->_hp == 0 || Ep->sta.HP == 0) {

		GMp->SRp->_switch = true;
	}
}


//----------------------------------------------------------------------------------------------------
//�����蔻��

//�e
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

//��
int PlayScene::isHit_wall(t2k::Vector3 pos, t2k::Vector3  prev_pos, float r) {

	//pos�ɋ߂����Ƀ\�[�g
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
			p->size_w_,
			pos
		);

		if (isHit_DotAndCircle(pos_, pos, r)) {

			int num = CollisionDirection(pos_, pos, prev_pos);

			return num;
		}

		return 0;
	}
}

//�_�Ɖ~�̓����蔻��
bool PlayScene::isHit_DotAndCircle(t2k::Vector3 dot_pos, t2k::Vector3 cir_pos, float r) {

	float x = dot_pos.x - cir_pos.x;
	float y = dot_pos.y + cir_pos.y;

	if (x * x + y * y <= r * r) {

		return true;
	}

	return false;
}

//�Փ˂�������
int PlayScene::CollisionDirection(t2k::Vector3 dot_pos, t2k::Vector3 cir_pos, t2k::Vector3 prev_pos) {

	float x = (cir_pos - dot_pos).x;



	float y = (cir_pos - dot_pos).y;


	return 1;
}

//�ǂ��Q���̓����蔻��(���W�␳������)�@���~�Ɠ_�̂�
void PlayScene::ActionCorrectionPosition(t2k::Vector3& pos, t2k::Vector3 prev_pos, float r) {

	int num = isHit_wall(pos, prev_pos, r);

	if (0 == num) { return; }


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


//----------------------------------------------------------------------------------------------------
//������
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
//���t���[���Ăяo��
void PlayScene::Update(float deltatime) {

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

	Start(deltatime);

	cam.render();
}

//----------------------------------------------------------------------------------------------------