#include "DxLib.h"
#include "../library/t2klib.h"
#include "../support/Support.h"
#include "game_main.h"
#include "../library/t2klib.h"

//----------------------------------------------------------------------------------------------------
//自作ファイル

#include "GameManager.h"


//----------------------------------------------------------------------------------------------------
//グローバル変数

bool init = true;

GameManager* GMp = nullptr;


//----------------------------------------------------------------------------------------------------

void gameMain( float deltatime ) {

	if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_ESCAPE)) {

		GMp->SPp->SavePlayer();
		exit(0);
	}

	if (init) {

		GMp = new GameManager();

		init = false;
	}

	GMp->Update(deltatime);
	GMp->Render(deltatime);
}