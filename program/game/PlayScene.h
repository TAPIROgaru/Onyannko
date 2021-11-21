#pragma once
#include <unordered_map>
#include "../library/math.h"

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
#include "Square.h"


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

	void DrawBuckGround();

	void isHit_bullet();


	//------------------------------------------------------------------------------------------------
	//���\�[�X�t�@�C����������g���֐�

	
	//=======================================================
	//�e����
	// 1.�������W
	// 2.x�p�x
	// 3.y�p�x
	// 4.�w�c
	//=======================================================
	void MakeBullet(t2k::Vector3, float, float, bool);


	//=======================================================
	//�J�������W���l�������}�E�X���W���擾�ł���֐�
	// 
	// return �}�E�X���W
	//=======================================================
	t2k::Vector3 GetMousePosition();


	//=======================================================
	//�J�������W���l���������W���擾�ł���֐�
	// 1.�C������Vector���W
	// 
	// return �C�����ꂽVector���W
	//=======================================================
	t2k::Vector3 FixPositionVector(t2k::Vector3);


	//=======================================================
	// �ǂ̓����蔻��
	// 1. Vector���W
	// 2. �~�̔��a
	// 
	// return true �������Ă�@false �������ĂȂ�
	//=======================================================
	inline bool isHit_wall(t2k::Vector3,float );


	//=======================================================
	// �_�Ɖ~�̓����蔻��
	// 1. �_��Vector���W
	// 2. �~��Vector���W
	// 3. �~�̔��a
	// 
	// return true �������Ă�@false �������ĂȂ�
	//=======================================================
	inline bool isHit_DotAndCircle(t2k::Vector3, t2k::Vector3, float);


	//=======================================================
	//	�ǂ��Q���̓����蔻��(���W�␳������)�@���~�Ɠ_�̂�
	// 1. �␳�Ώۂ�Vector���W
	// 2. 1�t���[���O�̍��W
	// 3. �~�̔��a
	//=======================================================
	void ActionCorrectionPosition(t2k::Vector3&,t2k::Vector3,float);


	//------------------------------------------------------------------------------------------------
	//�ϐ�


	std::list <Object*> Op;      //Object
	std::list <Bullet*> Bp;      //Bullet
	std::list <Square*> Sp;      //Square
	std::list <Square*> Sp_wall; //Square
	Enemy* Ep  = nullptr;        //Enemy
	Player* Pp = nullptr;        //Player

	Camera cam;                  //Camera�N���X

	std::vector<std::vector<std::string>>datas;
	std::vector<std::vector<std::string>>map;

	bool _start_flag = false;

	bool _over = false;

	bool _init = true;

	float count = 0;
	float start = 3;


	//------------------------------------------------------------------------------------------------
	//�}�X�̎��

	enum {

		FLOOR,
		OUTSIDE_WALL,
		INSIDE_WALL,
		ROCK
	};


	//------------------------------------------------------------------------------------------------
	//���t���[���Ăяo��

	void Update(float deltatime) override;
	void Render(float deltatime) override;


	//------------------------------------------------------------------------------------------------

};