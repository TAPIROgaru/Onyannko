#include "Skill.h"
#include "GameManager.h"
#include "PlayScene.h"

extern GameManager* GMp;


void Skill::Update(float deltatime, tpr::Vector2 pos_) {

	tpr::Vector2 v(pos_.x, pos_.y - 50);

	tpr::Vector2 v2 = tpr::Rotation::RotaVec2(v, pos_, tpr::Angle::DegChangeRad(angle));
	pos = t2k::Vector3(v2.x, v2.y, 0);

	angle++;
	count += deltatime;
};
void Skill::Render(Camera* cam) {

	t2k::Vector3 pos_ = GMp->SPp->FixPositionVector(pos);
	DrawRotaGraph(pos_.x, pos_.y, 0.5, 0, scroll_img_open, true);
};