#pragma once
#include "DxLib.h"

//---------------------------------------------------------------------------------------------
//����t�@�C��

#include "Line.h"
#include "Rotation.h"
#include "Color.h"


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
			A_pos(0, 0),
			B_pos(0, 0),
			C_pos(0, 0),
			D_pos(0, 0),
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
			B_pos(bottom_right_pos.x, upper_left_pos.y),
			C_pos(bottom_right_pos),
			D_pos(upper_left_pos.x, bottom_right_pos.y),
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
		// ��`�̏ꍇ(���S���W�ƃT�C�Y�Ɖ�])
		// 1. ���S���W
		// 2. ��
		// 3. ����
		// 4. ��](���W�A��)
		//=======================================================
		Quadrilateral(Vector2 pos, int size_w, int size_h, float rad) :

			A_pos(Rotation::RotaVec2(Vector2(pos.x - (size_w >> 1), pos.y - (size_h >> 1)), pos, rad)),
			B_pos(Rotation::RotaVec2(Vector2(pos.x + (size_w >> 1), pos.y - (size_h >> 1)), pos, rad)),
			C_pos(Rotation::RotaVec2(Vector2(pos.x + (size_w >> 1), pos.y + (size_h >> 1)), pos, rad)),
			D_pos(Rotation::RotaVec2(Vector2(pos.x - (size_w >> 1), pos.y + (size_h >> 1)), pos, rad)),
			upper_line(A_pos, B_pos),
			right_line(B_pos, C_pos),
			bottom_line(C_pos, D_pos),
			left_line(D_pos, A_pos)
		{}

		//=======================================================
		// ��`�̏ꍇ(��_�����ɂ����T�C�Y�Ɖ�])
		// 1. �n�_
		// 2. �I�_
		// 3. ��
		// 4. ��](���W�A��)
		//=======================================================
		Quadrilateral(Vector2 start_pos, Vector2 end_pos, int size_w, float rad) {

			Vector2 pos_c = Vector2::CenterPointCalc(start_pos, end_pos);

			int size_h = Vector2::DistanceCalc(start_pos, end_pos);

			*this = Quadrilateral(pos_c, size_w, size_h, rad);

			upper_line = Line(A_pos, B_pos);
			right_line = Line(B_pos, C_pos);
			bottom_line = Line(C_pos, D_pos);
			left_line = Line(D_pos, A_pos);
		}

		//=======================================================
		// �l�ӌ`�̏ꍇ(4�_�w��)
		// 1. ����̍��W
		// 2. �E��̍��W
		// 3. �E���̍��W
		// 4. �����̍��W
		//=======================================================
		Quadrilateral(
			Vector2 upper_left_pos, Vector2 upper_right_pos,
			Vector2 bottom_left_pos, Vector2 bottom_right_pos) :

			A_pos(upper_left_pos),
			B_pos(upper_right_pos),
			C_pos(bottom_right_pos),
			D_pos(bottom_left_pos),
			upper_line(A_pos, B_pos),
			right_line(B_pos, C_pos),
			bottom_line(C_pos, D_pos),
			left_line(D_pos, A_pos)
		{}

		//-------------------------------------------------------------------------------------
		//�I�y���[�^

		inline Quadrilateral operator = (const Quadrilateral p) {

			return Quadrilateral(
				A_pos = p.A_pos,
				B_pos = p.B_pos,
				C_pos = p.C_pos,
				D_pos = p.D_pos
			);
		}


		//-------------------------------------------------------------------------------------
		//�֐�

		//=======================================================
		// ���̕`��
		// 1. �F
		//=======================================================
		void DrawBox(unsigned int c);

		//=======================================================
		// ���̕`��
		// 1. �F
		//=======================================================
		void DrawBox(Color c);

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