#include "Astar.h"
#include "../GameManager.h"

extern GameManager* GMp;


namespace tpr{

	//-----------------------------------------------------------------------------------------------
	//�R���X�g���N�^
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
	//�f�X�g���N�^
	Astar::~Astar() {}


	//-----------------------------------------------------------------------------------------------
	//Astar�̎��s

	std::list<Node*> Astar::Astar_Exe(Vector2_int p_pos, Vector2_int e_pos) {

		Initialize(p_pos, e_pos);
		AstarPlay(&nodes[e_pos.y][e_pos.x], p_pos);

		return route;
	}


	//-----------------------------------------------------------------------------------------------
	//������

	void Astar::Initialize(Vector2_int p_pos, Vector2_int e_pos) {

		nodes = origin_nodes;

		adress_nodes.clear();
		open_nodes.clear();
		route.clear();
		
		nodes[p_pos.y][p_pos.x].status = GOAL;
		nodes[e_pos.y][e_pos.x].status = START;

		for (int y = 0; y < GameManager::TILE_VALUE_H - GameManager::TILE_VALUE_H_WALL; y++) {
			for (int x = 0; x < GameManager::TILE_VALUE_W - GameManager::TILE_VALUE_W_WALL; x++) {
				nodes[y][x].pos = Vector2_int{ x,y };
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
	//�o�H�T�����s

	bool Astar::AstarPlay(Node* _now , Vector2_int p_pos) {

		//�X�^�[�g�n�_�̃X�R�A�v�Z
		if (START == _now->status) {
			_now->score = _now->act_cost + _now->est_cost;
		}

		//�c���΂߂�8�����̍��W
		Vector2_int dire[8] = {
			Vector2_int(-1,-1),Vector2_int( 0,-1),Vector2_int( 1,-1),
			Vector2_int(-1, 0),/*                   */Vector2_int( 1, 0),
			Vector2_int(-1, 1),Vector2_int( 0, 1),Vector2_int( 1, 1)
		};

		//8�������ׂĉ\�Ȃ�I�[�v��
		for (int i = 0; i < 8; i++) {

			Vector2_int next = _now->pos + dire[i];

			//�I�[�v���\���ǂ���
			if (!isOpen(next)) { continue; }

			if (GOAL == adress_nodes[next.y][next.x].status) {

				//�S�[���̕ۑ�
				*route.emplace_front(&adress_nodes[next.y][next.x]);

				//�S�[�������O���玩���̐e�m�[�h���L�^
				Node* p = _now;
				while (nullptr != p) {
					*route.emplace_front(p);
					p = p->parent;
				}

				return true;
			}

			//�I�[�v���ł���m�[�h�̏���
			adress_nodes[next.y][next.x].status = OPEN;
			adress_nodes[next.y][next.x].parent = _now;
			adress_nodes[next.y][next.x].act_cost = _now->act_cost + 1;
			adress_nodes[next.y][next.x].score =
				adress_nodes[next.y][next.x].act_cost + adress_nodes[next.y][next.x].est_cost;
			open_nodes.emplace_back(&adress_nodes[next.y][next.x]);
		}

		//�I�[�v�������玩���̓N���[�Y
		if (START != _now->status) {
			_now->status = CLOSE;

			//���X�g���玩�����f���[�g
			std::list<Node*>::iterator Npit = open_nodes.begin();
			while (Npit != open_nodes.end()) {
				if ((*Npit)->pos == _now->pos) {
					Npit = open_nodes.erase(Npit);
					continue;
				}
				Npit++;
			}
		}

		//�I�[�v�����Ă���m�[�h�̒������ԃX�R�A�̏������m�[�h���擾
		Node* node = GetNextNode();

		//node��NULL�Ȃ瓞�B�s��(�z��O�̏���)
		if (node == nullptr) { 
			return false;
		}

		return AstarPlay(node, p_pos);
	}


	//-----------------------------------------------------------------------------------------------
	//�I�[�v���\�ȃ}�X���m�F

	bool Astar::isOpen(Vector2_int pos) {

		if (pos.x < 0) { return false; }
		if (pos.y < 0) { return false; }
		if (unsigned(pos.x) >= map_w ) { return false; }
		if (unsigned(pos.y) >= map_h ) { return false; }
		if (OPEN == adress_nodes[pos.y][pos.x].status) { return false; }
		if (START == adress_nodes[pos.y][pos.x].status) { return false; }
		if (YES == adress_nodes[pos.y][pos.x].status) { return true; }
		if (GOAL == adress_nodes[pos.y][pos.x].status) { return true; }

		return false;
	}


	//-----------------------------------------------------------------------------------------------
	//�I�[�v���ς̃m�[�h�ň�ԃX�R�A���Ⴂ�m�[�h�𓾂�

	Node* Astar::GetNextNode() {

		Node* smallNode = nullptr;

		for (auto p : open_nodes) {

			//smallNode��NULL�Ȃ�Ƃ肠�������
			if (smallNode == nullptr) { smallNode = p; }

			//smallNode���X�R�A���Ⴂ�Ȃ���
			if (smallNode->score > p->score) { smallNode = p; }

			//smallNode�ƃX�R�A�������Ƃ�
			else if (smallNode->score == p->score) {
				//�R�X�g���r����smallNode���Ⴂ�Ȃ���
				if (smallNode->act_cost > p->act_cost) {
					smallNode = p;
				}
			}
		}

		return smallNode;
	}
}