#include "FPgrowth.h"
#include "FP-tree.h"
#include <algorithm>
#include <iterator>
#include <iostream>
//经过构造后，发现不满足最小支持度要求的item1，怎么处理含item1的transation
//条件tree要不要去掉不满足最小支持度的item
using namespace std;
void FPgrowth::growth(){
	/*typedef vector<head_node*>::reverse_iterator iter;
	vector<head_node*>* head = tree->get_head();
	for (iter i = head->rbegin(); i != head->rend(); i++){
		growth(tree, *i, nullptr);
	}*/
	growth(tree, new int, 0);
}

void FPgrowth::growth(FPtree* tree, int* cond,int cond_len){
	if (tree->isEmpty())	return;
	bool is_single = tree->check_single();
	vector<head_node*>* head = tree->get_head();
	if (is_single){
		set<freq_items*> items = gen_comb(tree);
		//还要把cond加进去
		if (cond != nullptr){
			for_each(items.begin(), items.end(), [=](freq_items* i){
			for (int index = 0; index < cond_len; index++){
				i->items[i->count++] = cond[index];
			}
			});
		}
		result->insert(items.begin(), items.end());
		//copy(items.begin(), items.end(), back_inserter(*result));
	}
	else{
		typedef vector<head_node*>::reverse_iterator iter;
		//vector<head_node*>* head = tree->get_head();
		for (iter i = head->rbegin(); i != head->rend(); i++){
			growth(tree, *i, cond,cond_len);
		}
	}
}



void FPgrowth::growth(FPtree* tree, head_node* item_node, int* cond_item,int cond_len){
	if (item_node->node_link == 0)	return;
	FPtree* cond_tree = new FPtree(tree->get_min_sup());
	vector<head_node*>* cond_head = cond_tree->get_head();
	Node* now = item_node->node_link;
	//条件树的头表
	//cond_head = new vector<head_node*>();
	//记录条件模式基
	vector<Transation*>* cond_items = new vector<Transation*>();
	//记录每个条件模式基（转化成的tran）的times
	unsigned* trans_times = new unsigned;
	int ind=0;
	while (now != 0){
		//now_用来往上遍历树的节点
		
		Node* now_ = now->get_parent();
		int* items = new int;
		int tran_count = 0;
		//当前遍历到的节点的count就是该节点条件模式基的count
		unsigned count = now->getsup();
		trans_times[ind++] = count;
		while (now_->getid() != -1){
			*(items + tran_count) = now_->getid();
			tran_count++;
			my_equal me;
			me.id = now_->getid();
			vector<head_node*>::iterator i = find_if(cond_head->begin(), cond_head->end(), me);
			if (i != cond_head->end()){
				(*i)->add_sup(count);
			}
			else{
				cond_head->push_back(new head_node(now_->getid(), count));
			}
			
			
			now_ = now_->get_parent();
		}
		::reverse(items, items + tran_count);
		cond_items->push_back(new Transation(tran_count, items));


		now = now->get_next();
	}//now=nullptr，此headnode遍历结束
	//对条件树的head进行sort，并去掉小于最小支持度的item
	cond_tree->sort_head();


	//下面的工作是构造条件tree，并连上headnode的nodelink
	ind = 0;
	for (Transation* tran : *cond_items){
		cond_tree->processTrans(*tran, trans_times[ind], cond_tree->get_root());
		ind++;
	}
	//条件tree构造好了
	*(cond_item + cond_len) = item_node->id;
	cond_len++;
	growth(cond_tree, cond_item,cond_len);


}
//前提是tree是singlepath
set<freq_items*> FPgrowth::gen_comb(FPtree* tree){
	vector<int> items;
	set<freq_items*> result;
	Node* now = tree->get_root();
	while (now->getChildren() != 0 && now->getChildren()->size() != 0){
		now = now->getChildren()->begin()->second;
		items.push_back(now->getid());
	}
	int bits = items.size();
	int total = pow(2, bits);
	vector<int> indices(bits);
	for (int i = 1; i < total; i++){
		freq_items* fi = new freq_items();
		for (int j = 0; j < bits; j++){
			indices[j] = (i << (31 - j)) >> 31;
			if (indices[j]){
				
				fi->items[fi->count++] = items[j];
			}
		}
		fi->times = tree->get_map()->find(fi->items[fi->count - 1])->second;
		result.insert(fi);
		
	}

	return result;

}


void FPgrowth::output(){
	cout << endl;
	for (freq_items* fi : *result){
		for_each(fi->items, fi->items + fi->count, [=](int a){cout << char(a) << "  "; });
		cout << "times:" << fi->times;

		cout << endl;
	}
}

int main(){
	FPtree tree(3);
	int items1[] = { 'a', 'b', 'd', 'e' };
	Transation tran1(4, items1);
	int items2[] = { 'b', 'c', 'e' };
	Transation tran2(3, items2);
	int items3[] = { 'a', 'b', 'd', 'e' };
	Transation tran3(4, items3);
	int items4[] = { 'a', 'b', 'c', 'e' };
	Transation tran4(4, items4);
	int items5[] = { 'a', 'b', 'c', 'd', 'e' };
	Transation tran5(5, items5);
	int items6[] = { 'b', 'c', 'd' };
	Transation tran6(3, items6);

	vector<Transation> trans;
	trans.push_back(tran1);
	trans.push_back(tran2);
	trans.push_back(tran3);
	trans.push_back(tran4);
	trans.push_back(tran5);
	trans.push_back(tran6);


	tree.construction(trans);
	FPgrowth fpgrowth;
	fpgrowth.set_FPtree(&tree);
	fpgrowth.growth();
	fpgrowth.output();



	//cout << "hehe";
	//tree.outputTree();

	system("pause");
	return 0;
}