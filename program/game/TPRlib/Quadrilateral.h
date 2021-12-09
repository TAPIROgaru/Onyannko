#pragma once
#include "DxLib.h"

//---------------------------------------------------------------------------------------------
//����t�@�C��

#include "Line.h"


//---------------------------------------------------------------------------------------------

namespace tpr {

	// �l�ӌ`
	class Quadrilateral {
	public:

		//-------------------------------------------------------------------------------------
		//�R���X�g���N�^

		//=======================================================
		// �ϐ��錾�̂�
		//=======================================================
		Quadrilateral() :

			A_pos(0,0),
			B_pos(0,0),
			C_pos(0,0),
			D_pos(0,0),
			upper_line(A_pos, B_pos),
			right_line(B_pos, C_pos),
			bottom_line(C_pos, D_pos),
			left_line(D_pos, A_pos)
		{}

		//=======================================================
		// ��`�̏ꍇ(2�_�w��)
		// 1. ����̍��W
		// 2. �E���̍��W
		//=======================================================
		Quadrilateral(Vector2 upper_left_pos, Vector2 bottom_right_pos) :

			A_pos(upper_left_pos),
			B_pos(bottom_right_pos.x ,upper_left_pos.y),
			C_pos(bottom_right_pos),
			D_pos(upper_left_pos.x ,bottom_right_pos.y),
			upper_line(A_pos, B_pos),
			right_line(B_pos, C_pos),
			bottom_line(C_pos, D_pos),
			left_line(D_pos, A_pos)
		{}

		//=======================================================
		// ��`�̏ꍇ(���S�ƃT�C�Y)
		// 1. ���S���W
		// 2. ��
		// 3. ����
		//=======================================================
		Quadrilateral(Vector2 pos, int size_w, int size_h) :

			A_pos(pos.x - (size_w >> 1), pos.y - (size_h >> 1)),
			B_pos(pos.x + (size_w >> 1), pos.y - (size_h >> 1)),
			C_pos(pos.x + (size_w >> 1), pos.y + (size_h >> 1)),
			D_pos(pos.x - (size_w >> 1), pos.y + (size_h >> 1)),
			upper_line(A_pos, B_pos),
			right_line(B_pos, C_pos),
			bottom_line(C_pos, D_pos),
			left_line(D_pos, A_pos)
		{}

		//=======================================================
		// �l�ӌ`�̏ꍇ(4�_�w��)
		// 1. ����̍��W
		// 2. �E��̍��W
		// 3. �E���̍��W
		// 4. �����̍��W
		//=======================================================
		Quadrilateral(
			Vector2 upper_left_pos, Vector2 upper_right_pos,
			Vector2 bottom_left_pos, Vector2 bottom_right_pos):

			A_pos(upper_left_pos),
			B_pos(upper_right_pos),
			C_pos(bottom_right_pos),
			D_pos(bottom_left_pos),
			upper_line(A_pos,B_pos),
			right_line(B_pos,C_pos),
			bottom_line(C_pos,D_pos),
			left_line(D_pos,A_pos)
		{}

		//-------------------------------------------------------------------------------------
		//�I�y���[�^

		Quadrilateral operator = (const Quadrilateral quad) {

			return Quadrilateral(
				A_pos = quad.A_pos,
				B_pos = quad.B_pos,
				C_pos = quad.C_pos,
				D_pos = quad.D_pos
			);
		}


		//-------------------------------------------------------------------------------------
		//�֐�

		void DrawBox() {

			upper_line.DrawLine();
			bottom_line.DrawLine();
			left_line.DrawLine();
			right_line.DrawLine();
		}


		//-------------------------------------------------------------------------------------
		//�ϐ�

		Vector2 A_pos; //����
		Vector2 B_pos; //�E��
		Vector2 C_pos; //�E��
		Vector2 D_pos; //����

		Line upper_line;    //���
		Line bottom_line;   //���
		Line left_line;     //����
		Line right_line;    //�E��
	};
}