#include "FP-tree.h"
#include <vector>
#include <set>
#include <iostream>
#include <algorithm>
using namespace std;


void FPtree::sort_head(const vector<Transation>& trans){
	//对于每个item，都找一遍当前头表，如果找到一样的，则sup++，否则新建一个。最后再对head进行sort
	//待优化，hash、heap
	vector<head_node> head = get_head();
	for (Transation t : trans){
		int* cur_items = t.get_items();
		for (unsigned i = 0; i < t.get_count(); i++){
			id_equal.id = cur_items[i];
			vector<head_node>::iterator j = find_if(head.begin(), head.end(), id_equal);
			if (j != head.end())	j->sup++;
			else{
				head_node node{ cur_items[i], 0, 0 };
				head.push_back(node);
			}
		}
	}
	//删掉小于最小支持度的head节点
	head.erase(remove_if(head.begin(), head.end(), [=](const head_node& n)->bool{return n.sup < get_min_sup(); }),head.end());
	//对head节点排序
	sort(head.begin(), head.end());

}

