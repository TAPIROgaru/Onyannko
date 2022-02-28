#pragma once

//----------------------------------------------------------------------------------------------
//����t�@�C��

#include "CharaObj.h"
#include "TPRlib/tpr_library.h"

//----------------------------------------------------------------------------------------------------
//�N���X�̑O���錾

class tpr::Astar;


//----------------------------------------------------------------------------------------------

class Enemy :public CharaObj {
public:

	//------------------------------------------------------------------------------------------
	//�֐�

	Enemy(int);
	~Enemy();


	void Move(float);       //����
	void LoadStatus(int);   //�v���C���[�X�e�[�^�X�̃��[�h
	void FireBullet(float); //�e������
	void FindPlayer(float); //�v���C���[�Ƃ̈ʒu�֌W


	//------------------------------------------------------------------------------------------
	//�ϐ�

	int search_range_palyer = 370;      //���G�͈�

	float bullet_direction_x = 0;       //�e�𔭎˂������X
	float bullet_direction_y = 0;       //�e�𔭎˂������Y

	float angle = 0;                    //�p�x

	bool _fire = false;

	tpr::Astar* astar = nullptr;        //�o�H�T��

	unsigned int flame_count = 0;       //�t���[���̃J�E���g

	std::list<tpr::Node*> route;        //�������[�g

	std::vector<tpr::Vector2_int> move_pos; //���[���h���W
	int move_count = 0;
	bool _astar_falg = true;

	tpr::Vector2 avo_dire;


	//------------------------------------------------------------------------------------------
	//���t���[���Ăяo��

	void Update(float deltatime) override;
	void Render(Camera* cam)     override;


	//------------------------------------------------------------------------------------------

};