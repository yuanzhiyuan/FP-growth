#ifndef GUARD_Node_h
#define GUARD_Node_h

class Node_{
public:
	Node_();
	~Node_();

	int id;
	unsigned count; //���нڵ��count��С�ڵ���support��
	Node* parent;
	set<Node>* children;
	Node* next;
};


class Node{
public:

	Node(const Node& n);
	~Node();

	int getid() const{ return node->id; }
	int getsup() const{ return node->sup; }
	set<Node>* getChildren() const{ return node->children; }
	

private:
	Node_* node;
};


#endif