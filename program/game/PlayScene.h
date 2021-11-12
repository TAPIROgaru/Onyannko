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
#include "CircleHit.h"


//----------------------------------------------------------------------------------------------------

class PlayScene :public Scene {
public:

	//------------------------------------------------------------------------------------------------
	//�֐�

	PlayScene();

	void Delete();

	void SavePlayer();

	void Start(float);

	void isOver();

	void Init();

	void isHit();

	void DrawBuckGround();


	//------------------------------------------------------------------------------------------------
	//���\�[�X�t�@�C������g���֐�
	
	//�e����
	void MakeBullet(t2k::Vector3, float, float, float, bool);

	//�J�������W���l�������}�E�X���W���擾�ł���֐�
	t2k::Vector3 GetMousePosition();

	//�J�������W���l���������W���擾�ł���֐�
	t2k::Vector3 FixPositionVector(t2k::Vector3);


	//------------------------------------------------------------------------------------------------
	//�ϐ�


	std::list <Object*> Op;     //Object
	std::list <Bullet*> Bp;     //Bullet
	Enemy* Ep  = nullptr;       //Enemy
	Player* Pp = nullptr;       //Player

	Camera cam;                 //Camera�N���X

	std::vector<std::vector<std::string>>datas;
	std::vector<std::vector<std::string>>map;

	bool _start_flag = false;

	bool _over = false;

	bool _init = true;

	float count = 0;
	float start = 3;


	//------------------------------------------------------------------------------------------------
	//���t���[���Ăяo��

	void Update(float deltatime) override;
	void Render(float deltatime) override;


	//------------------------------------------------------------------------------------------------

};