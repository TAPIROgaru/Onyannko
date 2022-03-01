#pragma once
#include "DxLib.h"
#include <list>
#include <string>
#include <unordered_map>
using namespace std;

//----------------------------------------------------------------------------------------------------
//����t�@�C��



//----------------------------------------------------------------------------------------------------
//�N���X�̑O���錾

class Scene;
class PlayScene;
class TitleScene;
class MenuScene;
class ResultScene;


//----------------------------------------------------------------------------------------------------

class GameManager {
public:

	//------------------------------------------------------------------------------------------------
	//�T�C�Y�ꗗ ���̑��ݒ�

	static constexpr int SCREEN_W = 960;
	static constexpr int SCREEN_H = 540;

	static constexpr int FIELD_W = 576;   // 
	static constexpr int FIELD_H = 400;   // 

	static constexpr int TILE_SIZE_W = 32;
	static constexpr int TILE_SIZE_H = 32;

	static constexpr int TILE_VALUE_W = 40;
	static constexpr int TILE_VALUE_H = 28;

	static constexpr int TILE_VALUE_W_WALL = 6;
	static constexpr int TILE_VALUE_H_WALL = 6;

	static constexpr bool WINDOW_MODE = true;


	static constexpr int BULLET_RADIUS = 7;


	static constexpr int PLAYER_TAG = 1;
	static constexpr int ENEMY_TAG = 2;


	static constexpr float START_POSITION_PLAYER_W = 50.0f;
	static constexpr float START_POSITION_ENEMY_W = 1050.0f;
	static constexpr float START_POSITION_H = 300.0f;

	static constexpr bool DEBUG_MODE = true;
	                 bool ENEMY_MODE = true;


	//------------------------------------------------------------------------------------------------

	//�R���X�g���N�^
	GameManager();


	//------------------------------------------------------------------------------------------------
	//�֐�

	void ChangeScene();

	void Init();

	//------------------------------------------------------------------------------------------------
	//���\�[�X�t�@�C������g���֐�

	//=======================================================
	// �摜�Ăяo��
	// 1.�O���t�B�b�N�n���h��
	// 
	//  return �摜�f�[�^
	//=======================================================
	int loadGraph(std::string str);

	//=======================================================
	// �摜�Ăяo��
	// ���K���߂�l�̃|�C���^��delete���邱�Ɓ�
	// 
	// 1. �O���t�B�b�N�n���h��
	// 
	// return �摜�f�[�^�z��̐擪�A�h���X
	//=======================================================
	std::vector<int> loadDivGraph(std::vector<std::string> str,int img_value);

	//------------------------------------------------------------------------------------------------
	//�ϐ�

	std::vector<std::vector<std::string>>datas;
	std::unordered_map<std::string, int> image;

	bool _init = true;

	int img_aim;
	int img_mouse;


	//------------------------------------------------------------------------------------------------
	//���X�g�@�|�C���^

	std::list <Scene*> Sp;      //Scene
	PlayScene* SPp = nullptr;   //Play
	TitleScene* STp = nullptr;  //Title
	MenuScene* SMp = nullptr;   //Menu
	ResultScene* SRp = nullptr; //Result


	//------------------------------------------------------------------------------------------------
	//���t���[���Ăяo��

	void Update(float deltatime);
	void Render(float deltatime);


	//------------------------------------------------------------------------------------------------
};