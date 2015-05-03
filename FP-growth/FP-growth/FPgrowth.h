#ifndef GUARD_FPgrowth_h
#define GUARD_FPgrowth_h
#include "FP-tree.h"
#include <set>
struct freq_items{
	//数组大小
	freq_items():items(new int),count(0),times(0){}
	unsigned count;
	int* items;
	//支持度
	unsigned times;
};

class FPgrowth{
public:
	FPgrowth():tree(0),result(0){}
	void set_FPtree(FPtree* ptree){ tree = ptree; }
	
	void growth();
	
	void output();
private:
	void growth(FPtree* tree, int* cond, int cond_len);
	void growth(FPtree* tree, head_node* item_node, int* cond_item, int cond_len);
	set<freq_items*> gen_comb(FPtree* tree);
private:
	FPtree* tree;
	set<freq_items*>* result;
};

#endif