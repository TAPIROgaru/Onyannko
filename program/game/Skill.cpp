#include "Skill.h"
#include "GameManager.h"
#include "PlayScene.h"
#include "CharaObj.h"

extern GameManager* GMp;


//----------------------------------------------------------------------------------------------
//’e‚Æ“G’e‚Ì“–‚½‚è”»’è

bool Skill::isHit_Bullet() {

	for (auto p : GMp->SPp->Bp) {
		if (p->_team == _team) { continue; }

		if (tpr::isHit_CircleAndCircle(
			tpr::Vector2(p->pos.x, p->pos.y), p->r, pos_b, r)) {

			p->alive_flag = false;

			return true;
		}
	}

	return false;
}


//----------------------------------------------------------------------------------------------
//’e‚Æ“G‚Ì“–‚½‚è”»’è

bool Skill::isHit_Enemy(tpr::Vector2 pos) {

	CharaObj* p = nullptr;

	if (_team) { p = GMp->SPp->Ep; }
	else if (!_team) { p = GMp->SPp->Pp; }

	if (tpr::isHit_CircleAndCircle(tpr::Vector2(p->pos.x, p->pos.y), p->r, pos, r)) {

		return true;
	}

	return false;
}


//----------------------------------------------------------------------------------------------
//–ˆƒtƒŒ[ƒ€ŒÄ‚Ño‚µ

void Skill::Skill_UpDateMain(float deltatime, tpr::Vector2 pos_) {

	Skill_UpDate(deltatime);

	tpr::Vector2 v(pos_.x, pos_.y - 50);

	tpr::Vector2 v2 = tpr::Rotation::RotaVec2(v, pos_, tpr::Angle::DegChangeRad(angle));
	pos = t2k::Vector3(v2.x, v2.y, 0);

	angle++;
	if (_active) {
		cool_time_count += deltatime;
		if (cool_time_count > cool_time) {
			_active = false;
			_effect = false;
			cool_time_count = 0.0f;
		}
	}
}
void Skill::Skill_RenderMain(Camera* cam) {

	Skill_Render(cam);
	if (_active)return;

	t2k::Vector3 pos_ = GMp->SPp->FixPositionVector(pos);
	DrawRotaGraph(pos_.x, pos_.y, 0.5, 0, scroll_img_open, true);
}