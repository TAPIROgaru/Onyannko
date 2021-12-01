#pragma once

#include "Object.h"

namespace tpr {

	//ëïîıãZ
	class Scroll final :public Object  {
	//finalÇÕåpè≥Ç≥ÇπÇ»Ç¢

	public:


		//------------------------------------------------------------------------------------------------
		//ä÷êî

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
		//ïœêî

		int my_number;
		float cool_time;


		//------------------------------------------------------------------------------------------------
		//ëïîıãZàÍóó
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