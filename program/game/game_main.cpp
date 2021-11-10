#include "DxLib.h"
#include "../library/t2klib.h"
#include "../support/Support.h"
#include "game_main.h"
#include "../library/t2klib.h"

//----------------------------------------------------------------------------------------------------
//����t�@�C��

#include "GameManager.h"


//----------------------------------------------------------------------------------------------------
//�O���[�o���ϐ�

bool init = true;

GameManager* GMp = nullptr;


//----------------------------------------------------------------------------------------------------

void gameMain( float deltatime ) {

	if (init) {

		GMp = new GameManager();

		init = false;
	}

	if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_ESCAPE)) {
		if (GMp->SPp->Pp->alive_flag) {
			GMp->SPp->SavePlayer();
		}
		exit(0);
	}

	GMp->Update(deltatime);
	GMp->Render(deltatime);
}