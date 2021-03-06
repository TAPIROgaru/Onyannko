#pragma once
#include <vector>
#include <list>

//--------------------------------------------------------------------------------------------------
//自作ファイル

#include "Node.h"


//--------------------------------------------------------------------------------------------------

namespace tpr {
	class Astar {
	public:

		//------------------------------------------------------------------------------------------
		//関数

		Astar(std::vector<std::vector<int>> map);
		~Astar();

		//=======================================================
		// Astarの実行
		//=======================================================
		std::list<Node*> Astar_Exe(Vector2_int p_pos, Vector2_int e_pos);


		int img = 0;

	private:

		//=======================================================
		// 初期化
		// 1. 二次元座標上のPlayer
		// 2. 二次元座標上のEnemy
		//=======================================================
		void Initialize(Vector2_int p_pos, Vector2_int e_pos);


		//=======================================================
		// オープン可能なマスか確認
		// 1. オープン予定の二次元配列上の座標
		// 
		// return true できる　false できない
		//=======================================================
		bool isOpen(Vector2_int pos);


		//=======================================================
		// 経路探索実行
		// 1. 二次元座標上で開くノード
		// 2. 二次元座標上のPlayer
		// 
		// return true ゴール発見　false 到達不可(想定してない)
		//=======================================================
		bool AstarPlay(Node* _now, Vector2_int p_pos);


		//=======================================================
		// オープン済のノードで一番スコアが低いノードを得る
		// 
		// return オープン済のノードで一番スコアが低いノード
		//=======================================================
		Node* GetNextNode();


		//------------------------------------------------------------------------------------------
		//変数

		std::vector<Node*> adress_nodes;              //ノードの各行の先頭アドレス
		std::list<Node*> open_nodes;                  //OPEN状態のノード

		std::vector<std::vector<Node>> nodes;         //二次元座標のノード
		std::vector<std::vector<Node>> origin_nodes;  //二次元座標のノードのオリジナル

		std::list<Node*> route;                       //スタートからゴールまでの経路

		std::size_t map_w = 0;
		std::size_t map_h = 0;


		//------------------------------------------------------------------------------------------------
		//ステータス

		enum {

			OPEN,
			CLOSE,
			YES,
			NO,
			START,
			GOAL
		};

		//------------------------------------------------------------------------------------------
	};
}