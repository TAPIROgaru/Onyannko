#pragma once
#include "DxLib.h"
#include <list>

//----------------------------------------------------------------------------------------------------
//����t�@�C��

#include "Scene.h"
#include "PlayScene.h"
#include "TitleScene.h"
#include "MenuScene.h"

#include "Camera.h"


//----------------------------------------------------------------------------------------------------

class GameManager {
public:

	//------------------------------------------------------------------------------------------------
	//�X�N���[���T�C�Y�@�t�B�[���h�T�C�Y

	static constexpr int SCREEN_W = 960;
	static constexpr int SCREEN_H = 540;

	static constexpr int FIELD_W = SCREEN_W * 1.2;
	static constexpr int FIELD_H = SCREEN_H * 1.2;

	static constexpr bool WINDOW_MODE = true;

	//------------------------------------------------------------------------------------------------

	//�R���X�g���N�^
	GameManager();


	//------------------------------------------------------------------------------------------------
	//�֐�

	void DrawBuckGround();

	void ChangeScene();

	void Init();

	//------------------------------------------------------------------------------------------------
	//���\�[�X�t�@�C������g���֐�



	//------------------------------------------------------------------------------------------------
	//�ϐ�

	bool _init = true;

	int img = 0;

	t2k::Vector3 img_pos1 = { -FIELD_W, -FIELD_H,0 };
	t2k::Vector3 img_pos2 = { FIELD_W, FIELD_H,0 };


	//------------------------------------------------------------------------------------------------
	//���X�g�@�|�C���^

	std::list <Scene*> Sp;      //Scene
	PlayScene* SPp = nullptr;   //Play
	TitleScene* STp = nullptr;  //Title
	MenuScene* SMp = nullptr;   //Menu


	//------------------------------------------------------------------------------------------------
	//���t���[���Ăяo��

	void Update(float deltatime);
	void Render(float deltatime);


	//------------------------------------------------------------------------------------------------
};