#pragma once
#include <vector>


//----------------------------------------------------------------------------------------------------
//����t�@�C��

#include "Object.h"
#include "TPRlib/tpr_library.h"
#include "my_skill/skill_list.h"

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

		void Activate(tpr::Vector2 pos, float dire_x, float dire_y, bool _team_);

		void Kaginawa(tpr::Vector2 pos, float dire_x, float dire_y, bool _team_);
		void Nintou(tpr::Vector2 pos, float dire_x, float dire_y, bool _team_);
		void Torinoko(tpr::Vector2 pos, float dire_x, float dire_y, bool _team_);
		void Kakuremi(tpr::Vector2 pos, float dire_x, float dire_y, bool _team_);
		void Kunai(tpr::Vector2 pos, float dire_x, float dire_y, bool _team_);
		void Blink(tpr::Vector2 pos, float dire_x, float dire_y, bool _team_);
		void Shotgun(tpr::Vector2 pos, float dire_x, float dire_y, bool _team_);
		void Makibisi(tpr::Vector2 pos, bool _team_);
		void Teppo(tpr::Vector2 pos, float dire_x, float dire_y, bool _team_);


		//--------------------------------------------------------------------------------------
		//�ϐ�

		int my_number;
		float count = 0;
		float cool_time;
		bool _active = false;

		std::vector<int> skill_img;
		int skill_img_num = 0;
		tpr::Vector2 skill_img_pos;
		float skill_img_rad;
		int flame_count = 0;

		int scroll_img_close=0;
		int scroll_img_open=0;

		int angle = 0.0f;

		KAGINAWA* kagi = nullptr;
		KUNAI*    kuna = nullptr;
		MAKIBISI* maki = nullptr;
		NINTOU*   nint = nullptr;
		SHOTGUN*  shot = nullptr;
		TEPPO*    tepp = nullptr;
		TORINOKO* tori = nullptr;

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

		void Update(float deltatime, tpr::Vector2 pos_) override;
		void Render(Camera* cam)override;
	};
}