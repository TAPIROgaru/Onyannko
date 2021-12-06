#pragma once

//----------------------------------------------------------------------------------------------
//����t�@�C��

#include "CharaObj.h"
#include "Astar.h"


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

	int search_range_palyer = 750; //���G�͈�
	int search_range_bullet = 800;

	float bullet_direction_x = 0;  //�e�𔭎˂������
	float bullet_direction_y = 0;

	float angle = 0;               //�p�x

	tpr::Astar* astar = nullptr;  //�o�H�T��


	//------------------------------------------------------------------------------------------
	//���t���[���Ăяo��

	void Update(float deltatime) override;
	void Render(Camera* cam)     override;


	//------------------------------------------------------------------------------------------

};