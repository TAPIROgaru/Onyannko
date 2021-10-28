#pragma once
#include "DxLib.h"
#include <list>

//----------------------------------------------------------------------------------------------------
//����t�@�C��

#include "Object.h"
#include "CharaObj.h"
#include "Camera.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"


//----------------------------------------------------------------------------------------------------

class GameManager {
public:

	//------------------------------------------------------------------------------------------------
	//�֐�

	GameManager();
	void Init();     //������

	void Delete();   //�폜

	void MakeBullet(t2k::Vector3);  //�e����

	void SavePlayer();


	//------------------------------------------------------------------------------------------------
	//�ϐ�

	bool _init = true; //�������t���O


	//------------------------------------------------------------------------------------------------
	//�X�N���[���T�C�Y

	static constexpr int SCREEN_W = 1024;
	static constexpr int SCREEN_H = 768;


	//------------------------------------------------------------------------------------------------
	//���X�g�@�|�C���^

	std::list <Object*> Op;   //Object�N���X
	std::list <Bullet*> Bp;   //Bullet�N���X
	std::list <Enemy*> Ep;    //Enemy�N���X

	Camera cam;               //Camera�N���X

	Player* Pp = nullptr;     //Player�N���X


	//------------------------------------------------------------------------------------------------
	//���t���[���Ăяo��

	void Update(float deltatime);
	void Render(float deltatime);


	//------------------------------------------------------------------------------------------------
};