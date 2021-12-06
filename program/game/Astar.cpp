#include "Astar.h"
#include "GameManager.h"

extern GameManager* GMp;


namespace tpr{

	//-----------------------------------------------------------------------------------------------
	//コンストラクタ
	Astar::Astar(std::vector<std::vector<int>> map) {

		for (auto i : map) {
			std::vector<Node> node_y;
			for (auto k : i) {
				Node Np(k);
				node_y.emplace_back(Np);
			}
			nodes.emplace_back(node_y);
		}
	}


	//-----------------------------------------------------------------------------------------------
	//デストラクタ
	Astar::~Astar() {}


	//-----------------------------------------------------------------------------------------------
	//初期化
	void Astar::Initialize(Vector2 p_pos, Vector2 e_pos) {

		nodes[p_pos.x][p_pos.y].status = GOAL;
		nodes[e_pos.x][e_pos.y].status = START;

		int y = 0;
		for (auto i : nodes) {
			int x = 0;
			for (auto k : i) {
				k.pos = Vector2{ x,y };
				k.est_cost = abs((p_pos.x + p_pos.y) - (y + x));
				x++;
			}
			y++;

			adress_nodes.emplace_back(&i[y]);
		}
	}
}