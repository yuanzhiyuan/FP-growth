#include "Node.h"
//#include <unordered_map>



using namespace std;
Node_::Node_(int id, Node* parent) : id(id), count(0), parent(parent), next(0),children_map(0){
	children_map = new unordered_map<int, Node*>();

}

Node::Node(int id, Node* parent){
	node = new Node_(id, parent);
}
Node::Node(Node* next){
	node = new Node_(next);
}
Node_::~Node_(){
	//if (parent)	delete parent;
	if (children_map){
		//delete children_map;
	}
	//���ɾ��next�ڵ㣬FP-tree.cpp��87��do while��0��������ɾ��dummy�ᵼ�´���
	//if (next) delete next;
}
Node::~Node(){
	
	if (node) delete node;
}

void Node::remove_children(){
	if (!node->children_map) return;
	for (auto i = node->children_map->begin(); i != node->children_map->end(); i++){
		i->second->remove_children();
	}
	delete node->children_map;
	
	node->children_map = 0;
	delete node;
	node = 0;
}