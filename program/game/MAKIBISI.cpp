#include "GameManager.h"
#include "MAKIBISI.h"

extern GameManager* GMp;


MAKIBISI::MAKIBISI(tpr::Vector2 pos_, int angle) {

	scroll_img_close = GMp->loadGraph("graphics/scroll/MAKIBISI_close.png");
	scroll_img_open = GMp->loadGraph("graphics/scroll/MAKIBISI_open.png");

	skill_img.emplace_back(GMp->loadGraph("graphics/NINGU/MAKIBISI.png"));

	cool_time = 0.0f;
}
void MAKIBISI::Active(tpr::Vector2 pos, float dire_x, float dire_y)
{

}