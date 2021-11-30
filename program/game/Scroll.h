#pragma once

namespace tpr {

	//�����Z
	class Scroll final {
	//final�͌p�������Ȃ�

	public:


		//------------------------------------------------------------------------------------------------
		//�֐�

		Scroll(int);
		~Scroll() {};

		bool Activate(float);

		void Beam();
		void AirStrike();
		void Madness();
		void Barrier();
		void Tracking();
		void Blink();
		void Shotgun();
		void Turret();
		void ArmorPiercing();


		//------------------------------------------------------------------------------------------------
		//�ϐ�

		int my_number;
		float cool_time;


		//------------------------------------------------------------------------------------------------
		//�����Z�ꗗ
		enum ult {

			BEAM,
			AIR_STRIKE,
			MADNESS,
		};
		enum skill {

			BARRIER = 3,
			TRACKING,
			BLINK,
			SHOTGUN,
			TURRET,
			ARMOR_PIERCING,
		};


		//------------------------------------------------------------------------------------------------
	};
}