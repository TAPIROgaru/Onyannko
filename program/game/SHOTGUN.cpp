#include "GameManager.h"
#include "SHOTGUN.h"

extern GameManager* GMp;

SHOTGUN::SHOTGUN(tpr::Vector2 pos_, int angle) {

	scroll_img_close = GMp->loadGraph("graphics/scroll/SHOTGUN_close.png");
	scroll_img_open = GMp->loadGraph("graphics/scroll/SHOTGUN_open.png");

	this->angle = angle;
}

void SHOTGUN::Active(tpr::Vector2 pos, float dire_x, float dire_y) {

}