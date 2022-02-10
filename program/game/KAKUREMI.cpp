#include "GameManager.h"
#include "KAKUREMI.h"

extern GameManager* GMp;


KAKUREMI::KAKUREMI() {

	scroll_img_close = GMp->loadGraph("graphics/scroll/KAKUREMI_close.png");
	scroll_img_open = GMp->loadGraph("graphics/scroll/KAKUREMI_open.png");

	cool_time = 0.0f;
}