#pragma once
#include "DxLib.h"


//---------------------------------------------------------------------------------------------
//����t�@�C��

#include "Vector2.h"


//---------------------------------------------------------------------------------------------

namespace tpr {

	class Hitpoints {
	public:

		//-------------------------------------------------------------------------------------
		//�R���X�g���N�^

		//=======================================================
		// �ϐ��錾�̂�
		//=======================================================
		Hitpoints():
			size_w(0),
			size_h(0)
		{}


		//=======================================================
		// ���l�w��
		// 1.��
		// 2.����
		//=======================================================
		Hitpoints(int w,int h) :
			size_w(w),
			size_h(h)
		{}


		//=======================================================
		// �Q�[�W�̕\��
		// 1.���S���W
		// 2.�g�̐F(������)
		// 3.�ő�HP
		// 4.���݂�HP
		//=======================================================
		void DrawGauge(Vector2 pos, int c, float max, float now);


		//-------------------------------------------------------------------------------------
		//�ϐ�

		int size_w;
		int size_h;
	};
}