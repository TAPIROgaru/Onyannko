#pragma once

//--------------------------------------------------------------------------------------------------
//����t�@�C��

#include "Vector2.h"


//--------------------------------------------------------------------------------------------------

namespace tpr {
	//------------------------------------------------------------------------------------------
	//�o�H�T���p�m�[�h
	class Node {
	public:

		Node(int sta) :
			status(sta),
			est_cost(0),
			act_cost(0),
			score(0),
			parent(nullptr)
		{}

		Vector2 pos;       //�}�X�̍��W
		int     status;    //�}�X�̏��
		int     est_cost;  //����̃R�X�g
		int     act_cost;  //���ۂ̃R�X�g
		int     score;     //�X�R�A
		Node*   parent;    //�e�m�[�h


		//�\�[�g�poperator
		bool operator < (const Node& node) const {
			return score > node.score;
		}
	};
}