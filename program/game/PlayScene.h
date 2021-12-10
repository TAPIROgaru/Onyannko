#pragma once
#include <unordered_map>
#include "../library/math.h"

//----------------------------------------------------------------------------------------------------
//����t�@�C��

#include "Scene.h"

#include "Object.h"
#include "CharaObj.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Square.h"
#include "TPRlib/tpr_library.h"


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

	void LoadBuckGround();

	void isHit_bullet();


	//------------------------------------------------------------------------------------------------
	//���\�[�X�t�@�C��������g���֐�

	
	//=======================================================
	// �e����
	// 1. �������W
	// 2. x�p�x
	// 3. y�p�x
	// 4. �w�c
	//=======================================================
	void MakeBullet(t2k::Vector3, float, float, bool);


	//=======================================================
	// �J�������W���l�������}�E�X���W���擾�ł���֐�
	// 
	// return �}�E�X���W
	//=======================================================
	t2k::Vector3 GetMousePosition();


	//=======================================================
	// �J�������W���l���������W���擾�ł���֐�(Vector3)
	// 1. �C������Vector���W
	// 
	// return �C�����ꂽVector���W
	//=======================================================
	t2k::Vector3 FixPositionVector(t2k::Vector3);


	//=======================================================
	// �J�������W���l���������W���擾�ł���֐�(Vector2)
	// 1. �C������Vector���W
	// 
	// return �C�����ꂽVector���W
	//=======================================================
	tpr::Vector2 FixPositionVector(tpr::Vector2);


	//=======================================================
	// �ǂ̓����蔻��(�␳����)
	// 1. Vector���W
	// 2. 1�t���[���O�̍��W
	// 3. �~�̔��a
	//=======================================================
	void isHit_Wall(t2k::Vector3& pos, t2k::Vector3 prev_pos, float r);


	//=======================================================
	// �ǂ̓����蔻��(�␳����)
	// 1. Vector���W
	// 2. �~�̔��a
	// 
	// return true �������Ă�@false �������ĂȂ�
	//=======================================================
	bool isHit_Wall(t2k::Vector3 pos, float r);


	//=======================================================
	// �_�Ɖ~�̓����蔻��
	// 1. �_��Vector���W
	// 2. �~��Vector���W
	// 3. �~�̔��a
	// 
	// return true �������Ă�@false �������ĂȂ�
	//=======================================================
	inline bool isHit_DotAndCircle(t2k::Vector3 dot_pos, t2k::Vector3 cir_pos, float r);


	//=======================================================
	//	�~�Ǝl�p�`�̓����蔻���̍��W�␳
	// 1. �␳�Ώۂ�Vector���W
	// 2. �~�̔��a
	// 3. �Փ˂����l�p�`��Vector���W
	// 4. �������Ă������
	//=======================================================
	inline void isHit_ActionCorrectionPosition(t2k::Vector3& pos, float r, t2k::Vector3 dot_pos,int num);


	//=======================================================
	// Astar�p��Player��Enemy�̓񎟌����W�쐻
	// 1. Player�pVector2�ϐ��̃A�h���X
	// 2. Enemy�pVector2�ϐ��̃A�h���X
	//=======================================================
	void MakeVector2(tpr::Vector2_int* p_pos, tpr::Vector2_int* e_pos);


	//=======================================================
	// //Player��Enemy�̊Ԃɏ�Q�������邩
	// 
	// return true ����@false �Ȃ�
	//=======================================================
	bool isHit_RayAndWall();


	//=======================================================
	// �����̐��������𓾂�
	// 1.
	// 2.
	// 
	// return �����̐�������
	//=======================================================
	tpr::Vector2 Vertical(tpr::Vector2 first_pos, tpr::Vector2 second_pos);


	//------------------------------------------------------------------------------------------------
	//�ϐ�

	//=======================================================
	//�N���X�̃|�C���^
	std::list <Object*> Op;      //Object
	std::list <Bullet*> Bp;      //Bullet
	std::list <Square*> Sp;      //Square
	std::list <Square*> Sp_wall; //Square
	Enemy* Ep  = nullptr;        //Enemy
	Player* Pp = nullptr;        //Player
	Camera cam;                  //Camera

	//=======================================================
	//CSV�Ǘ��p�ϐ�
	std::vector<std::vector<std::string>>datas; //�L�����f�[�^
	std::vector<std::vector<std::string>>map;   //�}�b�v�f�[�^

	//=======================================================
	//�J�n�ƏI���Ə������p�ϐ�
	bool _start_flag = false;

	bool _over = false;

	bool _init = true;

	float count = 0;
	float start = 3;

	//=======================================================
	//Astar�p�ϐ�
	std::vector<std::vector<int>>astar_map;

	tpr::Vector2_int e_pos = { 0,0 };
	tpr::Vector2_int p_pos = { 0,0 };


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