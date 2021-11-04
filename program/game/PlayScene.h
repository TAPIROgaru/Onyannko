#pragma once

//----------------------------------------------------------------------------------------------------
//����t�@�C��

#include "Scene.h"

#include "Object.h"
#include "CharaObj.h"
#include "Camera.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"


//----------------------------------------------------------------------------------------------------

class PlayScene :public Scene {
public:

	//------------------------------------------------------------------------------------------------
	//�֐�

	PlayScene();

	void Delete();

	void SavePlayer();


	//------------------------------------------------------------------------------------------------
	//���\�[�X�t�@�C������g���֐�
	
	//�e����
	void MakeBullet(t2k::Vector3, float, float, float);


	//------------------------------------------------------------------------------------------------
	//�ϐ�


	std::list <Object*> Op;     //Object
	std::list <Bullet*> Bp;     //Bullet
	std::list <Enemy*> Ep;      //Enemy
	Player* Pp = nullptr;       //Player

	Camera cam;                 //Camera�N���X


	//------------------------------------------------------------------------------------------------
	//���t���[���Ăяo��

	void Update(float deltatime) override;
	void Render(Camera* cam)     override;


	//------------------------------------------------------------------------------------------------

};