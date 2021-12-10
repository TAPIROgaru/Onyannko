#pragma once


//---------------------------------------------------------------------------------------------
//����t�@�C��

#include "Vector2.h"


//---------------------------------------------------------------------------------------------

namespace tpr {

	//�p�x
	class Angle {
	public:

		//-------------------------------------------------------------------------------------
		//�R���X�g���N�^

		Angle() {};


		//-------------------------------------------------------------------------------------
		//�֐�

		//=======================================================
		// ��_�Ԃ̊p�x���v�Z
		// 1. �n�_
		// 2. �I�_
		// 
		// return �ʓx�@�̊p�x
		//=======================================================
		static float RadCalc(Vector2 start_pos, Vector2 end_pos);

		//=======================================================
		// ��_�Ԃ̊p�x���v�Z
		// 1. �n�_
		// 2. �I�_
		// 
		// return �x���@�̊p�x
		//=======================================================
		static int DegCalc(Vector2 start_pos, Vector2 end_pos);

		//=======================================================
		// �x���@���ʓx�@�ɒ���
		// 1. �x���@�̊p�x
		// 
		// return �ʓx�@�̊p�x
		//=======================================================
		static float DegChangeRad(int degree);

		//=======================================================
		// �ʓx�@��x���@�ɒ���
		// 1. �ʓx�@�̊p�x
		// 
		// return �x���@�̊p�x
		//=======================================================
		static int RadChangeDeg(float radian);


	private:

		//=======================================================
		// �_A�𒆐S��X��Y���ŕ��������Ƃ��_B���ǂ��ɂ��邩
		// 1. �n�_
		// 2. �I�_
		// 
		// return
		// info 0	X���܂���Y����ɂ���
		// info 1	�E��
		// info 2	����
		// info 3	����
		// info 4	�E��
		//=======================================================
		inline static int SearchSide(Vector2 start_pos, Vector2 end_pos);


	};
}