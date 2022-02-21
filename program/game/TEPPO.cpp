#include "GameManager.h"
#include "TEPPO.h"
#include "TPRlib/tpr_library.h"
#include "Player.h"
#include "Enemy.h"

extern GameManager* GMp;

TEPPO::TEPPO(tpr::Vector2 pos_, int angle) {

	scroll_img_close = GMp->loadGraph("graphics/scroll/TEPPO_close.png");
	scroll_img_open = GMp->loadGraph("graphics/scroll/TEPPO_open.png");

	this->angle = angle;
}

void TEPPO::Active(tpr::Vector2 pos, float dire_x, float dire_y, CharaObj* p) {

}