#pragma once

//--------------------------------------------------------------------------------------------------
//自作ファイル

#include "Vector2.h"


//--------------------------------------------------------------------------------------------------

namespace tpr {
	//------------------------------------------------------------------------------------------
	//経路探索用ノード
	class Node {
	public:

		Node(int sta) :
			status(sta),
			est_cost(0),
			act_cost(0),
			score(0),
			parent(nullptr)
		{}

		Vector2 pos;       //マスの座標
		int     status;    //マスの状態
		int     est_cost;  //推定のコスト
		int     act_cost;  //実際のコスト
		int     score;     //スコア
		Node*   parent;    //親ノード


		//ソート用operator
		bool operator < (const Node& node) const {
			return score > node.score;
		}
	};
}