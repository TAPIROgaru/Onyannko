#pragma once
#include "DxLib.h"

//---------------------------------------------------------------------------------------------
//����t�@�C��

#include "Vector2_deci.h"


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
			D_pos(0,0)
		{}

		//=======================================================
		// ��`�̏ꍇ(2�_�w��)
		// 1. ����̍��W
		// 2. �E���̍��W
		//=======================================================
		Quadrilateral(Vector2_deci upper_left_pos, Vector2_deci bottom_right_pos) :
			A_pos(upper_left_pos),
			B_pos(Vector2_deci{ bottom_right_pos.x ,upper_left_pos.y }),
			C_pos(bottom_right_pos),
			D_pos(Vector2_deci{ upper_left_pos.x ,bottom_right_pos.y })
		{}

		//=======================================================
		// �l�ӌ`�̏ꍇ(4�_�w��)
		// 1. ����̍��W
		// 2. �E��̍��W
		// 3. �E���̍��W
		// 4. �����̍��W
		//=======================================================
		Quadrilateral(
			Vector2_deci upper_left_pos, Vector2_deci upper_right_pos,
			Vector2_deci bottom_left_pos, Vector2_deci bottom_right_pos):

			A_pos(upper_left_pos),
			B_pos(upper_right_pos),
			C_pos(bottom_right_pos),
			D_pos(bottom_left_pos)
		{}

		//-------------------------------------------------------------------------------------
		//�֐�

		void DrawBox() {

			DrawLine((int)A_pos.x, (int)A_pos.y, (int)B_pos.x, (int)B_pos.y, -1);
			DrawLine((int)B_pos.x, (int)B_pos.y, (int)C_pos.x, (int)C_pos.y, -1);
			DrawLine((int)C_pos.x, (int)C_pos.y, (int)D_pos.x, (int)D_pos.y, -1);
			DrawLine((int)D_pos.x, (int)D_pos.y, (int)A_pos.x, (int)A_pos.y, -1);
		}

		//-------------------------------------------------------------------------------------
		//�ϐ�

		Vector2_deci A_pos; //����
		Vector2_deci B_pos; //�E��
		Vector2_deci C_pos; //�E��
		Vector2_deci D_pos; //����
	};
}