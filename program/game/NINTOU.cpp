#include "NINTOU.h"
#include "GameManager.h"

extern GameManager* GMp;

NINTOU::NINTOU(tpr::Vector2 pos_, int angle) {

	scroll_img_close = GMp->loadGraph("graphics/scroll/NINTOU_close.png");
	scroll_img_open = GMp->loadGraph("graphics/scroll/NINTOU_open.png");

	this->angle = angle;
}

void NINTOU::Active(tpr::Vector2 pos, float dire_x, float dire_y) {

	int i = 0;
	DrawGraph(pos.x + dire_x * 100, pos.y + dire_y * 100, skill_img[i], true);
	i++;
	_active = true;
	if (i > skill_img.size()) { _active = false; }
}