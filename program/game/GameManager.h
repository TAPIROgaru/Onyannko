#pragma once
#include "DxLib.h"
#include <list>

//----------------------------------------------------------------------------------------------------
//����t�@�C��

#include "Object.h"
#include "CharaObj.h"
#include "Camera.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"


//----------------------------------------------------------------------------------------------------

class GameManager {
public:

	//------------------------------------------------------------------------------------------------
	//�X�N���[���T�C�Y�@�t�B�[���h�T�C�Y

	static constexpr int SCREEN_W = 1920 / 2;
	static constexpr int SCREEN_H = 1080 / 2;

	static constexpr int FIELD_W = 1920;
	static constexpr int FIELD_H = 1080;

	//------------------------------------------------------------------------------------------------

	//�R���X�g���N�^
	GameManager();

	//������
	void Init();

	//�^�C�g���V�[��
	bool Title(const float);
	//�v���C�V�[��
	bool Play(const float);


	//------------------------------------------------------------------------------------------------
	//�֐�

	void Delete();   //�폜

	void SavePlayer();


	//------------------------------------------------------------------------------------------------
	//���\�[�X�t�@�C������g���֐�

	//�J�������W���l�������}�E�X���W���擾�ł���֐�
	t2k::Vector3 GetMousePosition();

	//�J�������W���l���������W���擾�ł���֐�
	t2k::Vector3 FixPositionVector(t2k::Vector3);

	//�e����
	void MakeBullet(t2k::Vector3, float, float, float);


	//------------------------------------------------------------------------------------------------
	//�ϐ�

	 //�������t���O
	bool _init = true;

	//�V�[���Ǘ�
	t2k::Sequence<GameManager*> seq =
		t2k::Sequence<GameManager*>(this, &GameManager::Title);

	int img;

	t2k::Vector3 img_pos1 = { -SCREEN_W * 1.5, -SCREEN_H * 1.5,0 };
	t2k::Vector3 img_pos2 = { SCREEN_W * 1.5, SCREEN_H * 1.5,0 };

	//------------------------------------------------------------------------------------------------
	//���X�g�@�|�C���^

	std::list <Object*> Op;   //Object�N���X
	std::list <Bullet*> Bp;   //Bullet�N���X
	std::list <Enemy*> Ep;    //Enemy�N���X

	Camera cam;               //Camera�N���X

	Player* Pp = nullptr;     //Player�N���X


	//------------------------------------------------------------------------------------------------
	//���t���[���Ăяo��

	void Update(float deltatime);
	void Render(float deltatime);


	//------------------------------------------------------------------------------------------------
};