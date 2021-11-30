#pragma once

namespace tpr {

	//υZ
	class Scroll final {
	//finalΝp³³ΉΘ’

	public:


		//------------------------------------------------------------------------------------------------
		//Φ

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
		//Ο

		int my_number;
		float cool_time;


		//------------------------------------------------------------------------------------------------
		//υZκ
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