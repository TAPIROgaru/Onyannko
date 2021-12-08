#include "DxLib.h"
#include "../library/t2klib.h"
#include "../support/Support.h"
#include "game_main.h"
#include "../library/t2klib.h"
#include <time.h>

//----------------------------------------------------------------------------------------------------
//自作ファイル

#include "GameManager.h"
#include "PlayScene.h"


//----------------------------------------------------------------------------------------------------
//グローバル変数

bool init = true;

GameManager* GMp = nullptr;


//----------------------------------------------------------------------------------------------------

void gameMain( float deltatime ) {

	if (init) {

		GMp = new GameManager();

		srand((unsigned int)time(0));

		init = false;
	}
	
	if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_ESCAPE)) {
		if (GMp->SPp->Pp != nullptr) {
			GMp->SPp->SavePlayer();
		}
		exit(0);
	}

	GMp->Update(deltatime);
	GMp->Render(deltatime);

	printfDx("%f\n",deltatime);
}