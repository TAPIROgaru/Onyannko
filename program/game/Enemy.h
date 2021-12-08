#pragma once

//----------------------------------------------------------------------------------------------
//����t�@�C��

#include "CharaObj.h"
#include "Astar.h"
#include "Node.h"


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

	int search_range_palyer = 750;      //���G�͈�
	int search_range_bullet = 800;      //�e�̔F���͈�

	float bullet_direction_x = 0;       //�e�𔭎˂������X
	float bullet_direction_y = 0;       //�e�𔭎˂������Y

	float angle = 0;                    //�p�x

	t2k::Vector3 prev_pos;              //1�t���[���O�̍��W

	tpr::Astar* astar = nullptr;        //�o�H�T��

	unsigned int flame_count = 0;       //�t���[���̃J�E���g

	std::list<tpr::Node*> route;        //�������[�g

	std::vector<tpr::Vector2> move_pos; //���[���h���W
	int move_count = 0;
	bool _astar_falg = true;


	//------------------------------------------------------------------------------------------
	//���t���[���Ăяo��

	void Update(float deltatime) override;
	void Render(Camera* cam)     override;


	//------------------------------------------------------------------------------------------

};