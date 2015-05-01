#ifndef GUARD_FP_tree_h
#define GUARD_FP_tree_h

#include "Node.h"
#include "Transation.h"
#include <vector>
#include <set>

#include <algorithm>
#include <unordered_map>


using std::vector;	using std::set;
class Node;
class Node_;
struct head_node{
	int id;
	unsigned sup;
	Node* node_link;
	void add_sup(unsigned added = 1){ sup += added; }
	head_node(int id):id(id),sup(1),node_link(0){}
	//定义<操作符，便于FP-tree.cpp中，sort_head最后的排序操作（非降序）
	bool operator<(head_node node){ return sup>node.sup; }
};


class FPtree{

public:
	FPtree(unsigned sup) :min_sup(sup),root(new Node(-1,nullptr)),head(new vector<head_node*>),id_sup_map(new unordered_map<int,unsigned>()),id_head_map(new unordered_map<int,head_node*>()),id_index_map(new unordered_map<int,int>()){}
	void construction(const vector<Transation>&);
	void sort_head(const vector<Transation>&);
	void sort_trans(Transation&);
	vector<head_node*>* get_head(){ return head; }
	unordered_map<int, unsigned>* get_map(){ return id_sup_map; }
	unordered_map<int, head_node*>* get_id_head_map(){ return id_head_map; }
	unordered_map<int, int>* get_id_index_map(){ return id_index_map; }
	unsigned get_min_sup() const{ return min_sup; }
	void set_min_sup(unsigned sup){ min_sup = sup; }
	void processTrans(Transation& tran, Node* node);
	void outputTree();
	
private:
	Node* root;//根节点的id为-1
	vector<head_node*>* head;
	//创建冗余信息，便于查找
	unordered_map<int, unsigned>* id_sup_map;
	unordered_map<int, head_node*>* id_head_map;
	//头表中id和顺序的映射
	unordered_map<int, int>* id_index_map;
	unsigned min_sup;



};

struct{
	int id;
	bool operator()(head_node* node){
		if (node->id == id)	return true;
		else return false;
	}
} id_equal;


#endif