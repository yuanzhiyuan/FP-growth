#ifndef GUARD_Node_h
#define GUARD_Node_h

class Node_{
public:
	Node_(int id, Node* parent) :id(id), count(0), parent(parent), children_map(new unordered_map<int,Node*>()), next(0){}
	~Node_();

	int id;
	unsigned count; //���нڵ��count��С�ڵ���support��
	Node* parent;
	//set<Node>* children;
	//key:id val:Node ��map�����ڲ��Ҷ�Ӧid��children
	unordered_map<int, Node*>* children_map;
	Node* next;
};


class Node{
public:

	Node(const Node& n);
	Node(int id, Node* parent);
	//Ϊ�˴���dummy
	Node(Node* next);
	~Node();

	int getid() const{ return node->id; }
	int getsup() const{ return node->count; }
	unordered_map<int,Node*>* getChildren(){ return node->children_map; }
	void add_count(unsigned added = 1){ node->count++; }
	Node* get_next(){ return node->next; }
	void mod_next(Node* new_next){ node->next = new_next; }

private:
	Node_* node;
};


#endif