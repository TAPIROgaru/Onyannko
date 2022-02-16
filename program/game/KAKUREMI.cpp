#include "GameManager.h"
#include "KAKUREMI.h"

extern GameManager* GMp;


KAKUREMI::KAKUREMI(tpr::Vector2 pos_, int angle) {

	scroll_img_close = GMp->loadGraph("graphics/scroll/KAKUREMI_close.png");
	scroll_img_open = GMp->loadGraph("graphics/scroll/KAKUREMI_open.png");

	cool_time = 0.0f;
}
void KAKUREMI::Active(tpr::Vector2 pos, float dire_x, float dire_y)
{

}