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
	//如果删掉next节点，FP-tree.cpp第87行do while（0）结束后删除dummy会导致错误
	//if (next) delete next;
}
Node::~Node(){
	
	if (node) delete node;
}