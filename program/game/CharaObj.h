#pragma once


//----------------------------------------------------------------------------------------------------
//自作ファイル

#include "Object.h"
#include "Scroll.h"
#include "Skill.h"


//----------------------------------------------------------------------------------------------------

class CharaObj :public Object {
public:

	//------------------------------------------------------------------------------------------------
	//関数



	//------------------------------------------------------------------------------------------------
	//変数

	//------------------------------------------------------------------------------------------------
	//ステータス

	static constexpr int name_length = 11;  //名前の長さ
	static constexpr int status_value = 6;  //ステータスの数

	char name[name_length] = { 0 };  //名前　※10文字

	class Status {
	public:

		int HP;                     //ヒットポイント
		int hp_;                    //増減するHP
		int move_speed;             //移動速度
		int attack;                 //攻撃力
		int defense;                //防御力
		int attack_speed;           //攻撃速度      1秒間に何回攻撃するか
	};

	int chara_handle = 0;         //画像ハンドル

	Status sta;

	Scroll* ult;
	Scroll* skillA;
	Scroll* skillB;

	float secconds_AS = 0;   //1攻撃何秒か
	float timecount = 0;     //時間計測


	//------------------------------------------------------------------------------------------------
	//アビリティ
	class Ability {
	public:

		int ult = 0;             //ウルト
		float ult_cooltime = 0;  //↑のクールタイム

		int skill_a = 0;         //Aスキル
		float a_cooltime = 0;    //↑のクールタイム

		int skill_b = 0;         //Bスキル
		float b_cooltime = 0;    //↑のクールタイム
	};

	Ability abi;
};