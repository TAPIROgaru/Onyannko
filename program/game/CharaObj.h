#pragma once


//----------------------------------------------------------------------------------------------------
//����t�@�C��

#include "Object.h"
#include "Scroll.h"


//----------------------------------------------------------------------------------------------------

class CharaObj :public Object {
public:

	//------------------------------------------------------------------------------------------------
	//�֐�



	//------------------------------------------------------------------------------------------------
	//�ϐ�

	//------------------------------------------------------------------------------------------------
	//�X�e�[�^�X

	static constexpr int name_length = 11;  //���O�̒���
	static constexpr int status_value = 6;  //�X�e�[�^�X�̐�

	char name[name_length] = { 0 };  //���O�@��10����

	class Status {
	public:

		int HP;                     //�q�b�g�|�C���g
		int hp_;                    //��������HP
		int move_speed;             //�ړ����x
		int attack;                 //�U����
		int defense;                //�h���
		int attack_speed;           //�U�����x      1�b�Ԃɉ���U�����邩
	};

	int chara_handle = 0;         //�摜�n���h��

	Status sta;

	tpr::Scroll* ult;
	tpr::Scroll* skillA;
	tpr::Scroll* skillB;

	float secconds_AS = 0;   //1�U�����b��
	float timecount = 0;     //���Ԍv��


	//------------------------------------------------------------------------------------------------
	//�A�r���e�B
	class Ability {
	public:

		int ult = 0;             //�E���g
		float ult_cooltime = 0;  //���̃N�[���^�C��

		int skill_a = 0;         //A�X�L��
		float a_cooltime = 0;    //���̃N�[���^�C��

		int skill_b = 0;         //B�X�L��
		float b_cooltime = 0;    //���̃N�[���^�C��
	};

	Ability abi;
};