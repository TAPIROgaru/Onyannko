#include "Scroll.h"
#include "GameManager.h"
#include "PlayScene.h"
#include "BLINK.h"
#include "KAGINAWA.h"
#include "KAKUREMI.h"
#include "KUNAI.h"
#include "MAKIBISI.h"
#include "NINTOU.h"
#include "SHOTGUN.h"
#include "TEPPO.h"
#include "TORINOKO.h"

extern GameManager *GMp;


namespace tpr {
	//------------------------------------------------------------------------------------------------
	//�R���X�g���N�^
	Scroll::Scroll(int num, char c, tpr::Vector2 pos_) {

		my_number = num;
		int angle;

		tpr::Vector2 pos__(pos_.x, pos_.y - 50);
		
		if (c == 'u') {

			angle = 0;
		}
		else if (c == 'a') {

			angle = 120;
			pos__ = Rotation::RotaVec2(pos__, pos_, Angle::DegChangeRad(angle));
		}
		else if (c == 'b') {

			angle = 240;
			pos__ = Rotation::RotaVec2(pos__, pos_, Angle::DegChangeRad(angle));
		}

		make_skill_func[my_number](this, pos__, angle);

	}


	//------------------------------------------------------------------------------------------------
	//����
	void Scroll::Activate(tpr::Vector2 pos,float dire_x, float dire_y) {

		skill_func[my_number](this, pos, dire_x, dire_y);
	}


	//------------------------------------------------------------------------------------------------
	//�����Ȃ�@(��������)
	void Scroll::Kaginawa(tpr::Vector2 pos, float dire_x, float dire_y) {

	}
	void Scroll::make_Kaginawa(tpr::Vector2 pos, int angle) {

		kaginawa = new KAGINAWA();
	}


	//------------------------------------------------------------------------------------------------
	//�ɂ�Ƃ��@(�O��)
	void Scroll::Nintou(tpr::Vector2 pos, float dire_x, float dire_y) {


	}
	void Scroll::make_Nintou(tpr::Vector2 pos, int angle) {


	}


	//------------------------------------------------------------------------------------------------
	//�Ƃ�̂��@(�΂�����)
	void Scroll::Torinoko(tpr::Vector2 pos, float dire_x, float dire_y) {

	}
	void Scroll::make_Torinoko(tpr::Vector2 pos, int angle) {

	}


	//------------------------------------------------------------------------------------------------
	//������݁@(�������ɂ���)
	void Scroll::Kakuremi(tpr::Vector2 pos, float dire_x, float dire_y) {

	}
	void Scroll::make_Kakuremi(tpr::Vector2 pos, int angle) {

	}


	//------------------------------------------------------------------------------------------------
	//���Ȃ��@������(���E����)
	void Scroll::Kunai(tpr::Vector2 pos, float dire_x, float dire_y) {

	}
	void Scroll::make_Kunai(tpr::Vector2 pos, int angle) {

	}


	//------------------------------------------------------------------------------------------------
	//�u�����N
	void Scroll::Blink(tpr::Vector2 pos, float dire_x, float dire_y) {

	}
	void Scroll::make_Blink(tpr::Vector2 pos, int angle) {

	}


	//------------------------------------------------------------------------------------------------
	//�U�e
	void Scroll::Shotgun(tpr::Vector2 pos, float dire_x, float dire_y) {

	}
	void Scroll::make_Shotgun(tpr::Vector2 pos, int angle) {

	}


	//------------------------------------------------------------------------------------------------
	//�܂��т��@(�g���b�v)
	void Scroll::Makibisi(tpr::Vector2 pos, float dire_x, float dire_y) {

	}
	void Scroll::make_Makibisi(tpr::Vector2 pos, int angle) {

	}


	//------------------------------------------------------------------------------------------------
	//�O�b�e
	void Scroll::Teppo(tpr::Vector2 pos, float dire_x, float dire_y) {

	}
	void Scroll::make_Teppo(tpr::Vector2 pos, int angle) {

	}


	//----------------------------------------------------------------------------------------------------
	//���t���[���Ăяo��

	void Scroll::Update(float deltatime, tpr::Vector2 pos_) {
	}
	void Scroll::Render(Camera* cam) {
	}
}