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
	//�X�N���[���T�C�Y�@�t�B�[���h�T�C�Y�@�^�C���T�C�Y

	static constexpr int SCREEN_W = 960;
	static constexpr int SCREEN_H = 540;

	static constexpr int FIELD_W = 576;   // 1152
	static constexpr int FIELD_H = 400;   // 800

	static constexpr int TILE_SIZE_W = 32;
	static constexpr int TILE_SIZE_H = 32;

	static constexpr int TILE_VALUE_W = 40;
	static constexpr int TILE_VALUE_H = 28;

	static constexpr int TILE_VALUE_W_WALL = 6;
	static constexpr int TILE_VALUE_H_WALL = 6;

	static constexpr bool WINDOW_MODE = true;

	//------------------------------------------------------------------------------------------------

	//�R���X�g���N�^
	GameManager();


	//------------------------------------------------------------------------------------------------
	//�֐�

	void ChangeScene();

	void Init();

	//------------------------------------------------------------------------------------------------
	//���\�[�X�t�@�C������g���֐�

	//�摜�Ăяo��
	int loadGraph(std::string);

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