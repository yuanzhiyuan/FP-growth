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
	if (parent)	delete parent;
	if (children_map) delete children_map;
	//���ɾ��next�ڵ㣬FP-tree.cpp��87��do while��0��������ɾ��dummy�ᵼ�´���
	//if (next) delete next;
}
Node::~Node(){
	
	if (node) delete node;
}