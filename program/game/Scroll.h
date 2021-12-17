#pragma once
#include <vector>


//----------------------------------------------------------------------------------------------------
//����t�@�C��

#include "Object.h"
#include "TPRlib/tpr_library.h"

namespace tpr {

	//�����Z
	class Scroll final :public Object  {
	//final�͌p�������Ȃ�

	public:


		//------------------------------------------------------------------------------------------------
		//�֐�

		//=======================================================
		// �X�L���̐���(�R���X�g���N�^)
		// 1. ��������X�L���̔ԍ�
		//    �w�b�_�[���̑����Z�ꗗ(enum)�Q��
		// 2. ult�Ȃ�u skillA�Ȃ�a skillB�Ȃ�b
		// 3. �X�L�����L�҂̍��W
		//======================================================
		Scroll(int num,char c, tpr::Vector2 pos_);
		~Scroll() {};

		bool Activate(float);

		void Kaginawa();
		void Nintou();
		void Torinoko();
		void Kakuremi();
		void Kunai();
		void Blink();
		void Shotgun();
		void Makibisi();
		void Teppo();


		//--------------------------------------------------------------------------------------
		//�ϐ�

		int my_number;
		float cool_time;
		std::vector<int> skill_img;
		int scroll_img_close;
		int scroll_img_open;

		int angle;

		//--------------------------------------------------------------------------------------
		//�����Z�ꗗ
		enum ult {

			KAGINAWA,
			NINTOU,
			TORINOKO,
		};
		enum skill {

			KAKUREMI = 3,
			KUNAI,
			BLINK,
			SHOTGUN,
			MAKIBISI,
			TEPPO,
		};
		
		
		//--------------------------------------------------------------------------------------
		//���t���[���Ăяo��

		void Update(float deltatime, tpr::Vector2 pos_);
		void Render(Camera* cam);
	};
}