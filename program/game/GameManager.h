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

	static constexpr int SCREEN_W = 960;   //�E�B���h�E�̉���
	static constexpr int SCREEN_H = 540;   //�E�B���h�E�̏c��

	static constexpr int FIELD_W = 576;   //�t�B�[���h�̉���
	static constexpr int FIELD_H = 400;   //�t�B�[���h�̏c��

	static constexpr int TILE_SIZE_W = 32;   //1�}�X�̉���
	static constexpr int TILE_SIZE_H = 32;   //1�}�X�̏c��

	static constexpr int TILE_VALUE_W = 40;   //���̃}�X�ڂ̐�
	static constexpr int TILE_VALUE_H = 28;   //�c�̃}�X�ڂ̐�

	static constexpr int TILE_VALUE_W_WALL = 6;   //���E�̍��v�����ǂ̐�
	static constexpr int TILE_VALUE_H_WALL = 6;   //�㉺�̍��v�����ǂ̐�

	static constexpr bool WINDOW_MODE = false;    //�X�N���[�����[�h�@true �t���@false �E�B���h�E


	static constexpr int BULLET_RADIUS = 7;   //�e�̔��a


	static constexpr int PLAYER_TAG = 1;   //Player�̃^�O�ԍ�
	static constexpr int ENEMY_TAG = 2;   //Enemy�̃^�O�ԍ�


	static constexpr float START_POSITION_PLAYER_W = 50.0f;   //Player�̏������WX
	static constexpr float START_POSITION_ENEMY_W = 1050.0f;   //Enemy�̏������WX
	static constexpr float START_POSITION_H = 300.0f;   //�����̏������WY

	static constexpr bool DEBUG_MODE = true;   //�f�o�b�O���[�h
	                 bool ENEMY_MODE = true;   //�G�̍s�����邩���Ȃ���


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

	//=======================================================
	// �����Ăяo��
	// 1.�n���h��
	// 
	//  return �f�[�^
	//=======================================================
	int loadSoundMem(std::string str);

	//------------------------------------------------------------------------------------------------
	//�ϐ�

	std::vector<std::vector<std::string>>datas;
	std::unordered_map<std::string, int> image;
	std::unordered_map<std::string, int> sound;

	bool _init = true;

	int img_aim;
	int img_mouse;

	int scene_sou = 0;


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