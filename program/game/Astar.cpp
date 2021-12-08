#include "Astar.h"
#include "GameManager.h"

extern GameManager* GMp;


namespace tpr{

	//-----------------------------------------------------------------------------------------------
	//コンストラクタ
	Astar::Astar(std::vector<std::vector<int>> map) {

		img = GMp->loadGraph("graphics/debug.png");

		bool _init = true;

		map_h = map.size();

		for (auto i : map) {
			std::vector<Node> node_y;
			if (_init) { map_w = i.size(); _init = false; }

			for (auto k : i) {
				Node Np(k);
				node_y.emplace_back(Np);
			}
			origin_nodes.emplace_back(node_y);
		}
	}


	//-----------------------------------------------------------------------------------------------
	//デストラクタ
	Astar::~Astar() {}


	//-----------------------------------------------------------------------------------------------
	//Astarの実行

	std::list<Node*> Astar::Astar_Exe(Vector2 p_pos, Vector2 e_pos) {

		Initialize(p_pos, e_pos);
		AstarPlay(&nodes[e_pos.y][e_pos.x], p_pos);

		return route;
	}


	//-----------------------------------------------------------------------------------------------
	//初期化

	void Astar::Initialize(Vector2 p_pos, Vector2 e_pos) {

		nodes = origin_nodes;

		adress_nodes.clear();
		open_nodes.clear();
		route.clear();
		
		nodes[p_pos.y][p_pos.x].status = GOAL;
		nodes[e_pos.y][e_pos.x].status = START;

		for (int y = 0; y < GameManager::TILE_VALUE_H - GameManager::TILE_VALUE_H_WALL; y++) {
			for (int x = 0; x < GameManager::TILE_VALUE_W - GameManager::TILE_VALUE_W_WALL; x++) {
				nodes[y][x].pos = Vector2{ x,y };
				nodes[y][x].est_cost = (abs(p_pos.x - x) + abs(p_pos.y - y));
			}
		}

		auto it = nodes.begin();
		while (it!=nodes.end()) {

			adress_nodes.emplace_back((*it).data());

			it++;
		}
	}


	//-----------------------------------------------------------------------------------------------
	//経路探索実行

	bool Astar::AstarPlay(Node* _now ,Vector2 p_pos) {

		//スタート地点のスコア計算
		if (START == _now->status) {
			_now->score = _now->act_cost + _now->est_cost;
		}

		//縦横斜めの8方向の座標
		Vector2 dire[8] = {
			Vector2(-1,-1),Vector2( 0,-1),Vector2( 1,-1),
			Vector2(-1, 0),/*           */Vector2( 1, 0),
			Vector2(-1, 1),Vector2( 0, 1),Vector2( 1, 1)
		};

		//8方向調べて可能ならオープン
		for (int i = 0; i < 8; i++) {

			Vector2 next = _now->pos + dire[i];

			//オープン可能かどうか
			if (!isOpen(next)) { continue; }

			if (GOAL == adress_nodes[next.y][next.x].status) {

				//ゴールの保存
				*route.emplace_front(&adress_nodes[next.y][next.x]);

				//ゴール一歩手前から自分の親ノードを記録
				Node* p = _now;
				while (nullptr != p) {
					*route.emplace_front(p);
					p = p->parent;
				}

				return true;
			}

			//オープンできるノードの処理
			adress_nodes[next.y][next.x].status = OPEN;
			adress_nodes[next.y][next.x].parent = _now;
			adress_nodes[next.y][next.x].act_cost = _now->act_cost + 1;
			adress_nodes[next.y][next.x].score =
				adress_nodes[next.y][next.x].act_cost + adress_nodes[next.y][next.x].est_cost;
			open_nodes.emplace_back(&adress_nodes[next.y][next.x]);
		}

		//オープンしたら自分はクローズ
		if (START != _now->status) {
			_now->status = CLOSE;

			//リストから自分をデリート
			std::list<Node*>::iterator Npit = open_nodes.begin();
			while (Npit != open_nodes.end()) {
				if ((*Npit)->pos == _now->pos) {
					Npit = open_nodes.erase(Npit);
					continue;
				}
				Npit++;
			}
		}

		//オープンしているノードの中から一番スコアの小さいノードを取得
		Node* node = GetNextNode();

		//nodeがNULLなら到達不可(想定外の処理)
		if (node == nullptr) { 
			return false;
		}

		return AstarPlay(node, p_pos);
	}


	//-----------------------------------------------------------------------------------------------
	//オープン可能なマスか確認

	bool Astar::isOpen(Vector2 pos) {

		if (pos.x < 0) { return false; }
		if (pos.y < 0) { return false; }
		if (pos.x >= map_w ) { return false; }
		if (pos.y >= map_h ) { return false; }
		if (OPEN == adress_nodes[pos.y][pos.x].status) { return false; }
		if (START == adress_nodes[pos.y][pos.x].status) { return false; }
		if (YES == adress_nodes[pos.y][pos.x].status) { return true; }
		if (GOAL == adress_nodes[pos.y][pos.x].status) { return true; }

		return false;
	}


	//-----------------------------------------------------------------------------------------------
	//オープン済のノードで一番スコアが低いノードを得る

	Node* Astar::GetNextNode() {

		Node* smallNode = nullptr;

		for (auto p : open_nodes) {

			//smallNodeがNULLならとりあえず代入
			if (smallNode == nullptr) { smallNode = p; }

			//smallNodeよりスコアが低いなら代入
			if (smallNode->score > p->score) { smallNode = p; }

			//smallNodeとスコアが同じとき
			else if (smallNode->score == p->score) {
				//コストを比較してsmallNodeより低いなら代入
				if (smallNode->act_cost > p->act_cost) {
					smallNode = p;
				}
			}
		}

		return smallNode;
	}
}