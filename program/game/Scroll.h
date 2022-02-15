#pragma once
#include <vector>
#include <iostream>
#include <functional>


//----------------------------------------------------------------------------------------------------
//����t�@�C��

#include "Object.h"
#include "TPRlib/tpr_library.h"

namespace tpr {

	//�����Z
	class Scroll final  {
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

		bool Activate(tpr::Vector2 pos,float dire_x, float dire_y);

		void Kaginawa(tpr::Vector2 pos, float dire_x, float dire_y);
		void Nintou(tpr::Vector2 pos, float dire_x, float dire_y);
		void Torinoko(tpr::Vector2 pos, float dire_x, float dire_y);
		void Kakuremi(tpr::Vector2 pos, float dire_x, float dire_y);
		void Kunai(tpr::Vector2 pos, float dire_x, float dire_y);
		void Blink(tpr::Vector2 pos, float dire_x, float dire_y);
		void Shotgun(tpr::Vector2 pos, float dire_x, float dire_y);
		void Makibisi(tpr::Vector2 pos, float dire_x, float dire_y);
		void Teppo(tpr::Vector2 pos, float dire_x, float dire_y);

		void make_Kaginawa(tpr::Vector2 pos, int angle);
		void make_Nintou(tpr::Vector2 pos, int angle);
		void make_Torinoko(tpr::Vector2 pos, int angle);
		void make_Kakuremi(tpr::Vector2 pos, int angle);
		void make_Kunai(tpr::Vector2 pos, int angle);
		void make_Blink(tpr::Vector2 pos, int angle);
		void make_Shotgun(tpr::Vector2 pos, int angle);
		void make_Makibisi(tpr::Vector2 pos, int angle);
		void make_Teppo(tpr::Vector2 pos, int angle);


		//--------------------------------------------------------------------------------------
		//�ϐ�


		int my_number;

		std::function< void (Scroll, tpr::Vector2 pos, float dire_x, float dire_y) > 
			skill_func[9] = {
			Kaginawa,
			Nintou,
			Torinoko,
			Kakuremi,
			Kunai,
			Blink,
			Shotgun,
			Makibisi,
			Teppo
		};

		std::function< void(Scroll,tpr::Vector2 pos, int angle) >
			make_skill_func[9] = {
			make_Kaginawa,
			make_Nintou,
			make_Torinoko,
			make_Kakuremi,
			make_Kunai,
			make_Blink,
			make_Shotgun,
			make_Makibisi,
			make_Teppo
		};

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