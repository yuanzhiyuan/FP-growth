#ifndef GUARD_FP_tree_h
#define GUARD_FP_tree_h
#include "Node.h"
#include <vector>
#include <set>
#include "Transation.h"
using std::vector;	using std::set;
struct head_node{
	int id;
	unsigned sup;
	Node* node_link;
	//定义<操作符，便于FP-tree.cpp中，sort_head最后的排序操作（非降序）
	bool operator<(head_node node){ return sup>node.sup; }
};


class FPtree{

public:
	FPtree();
	void construction(const vector<Transation>&);
	void sort_head(const vector<Transation>&);
	vector<head_node>& get_head(){ return head; }
	unsigned get_min_sup() const{ return min_sup; }
private:
	Node* root;
	vector<head_node> head;
	unsigned min_sup;



};

struct{
	int id;
	bool operator()(head_node node){
		if (node.id == id)	return true;
		else return false;
	}
} id_equal;


#endif