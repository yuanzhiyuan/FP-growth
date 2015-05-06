#include "Transation.h"
#include "FP-tree.h"
#include <vector>

#include <set>
#include <iostream>
#include <algorithm>


using namespace std;

void FPtree::sort_head(){
	//删掉小于最小支持度的head节点
	head->erase(remove_if(head->begin(), head->end(), [=](const head_node* n)->bool{return n->sup < get_min_sup(); }), head->end());
	//对head节点排序
	sort(head->begin(), head->end(), [=](head_node* pnode1, head_node* pnode2)->bool{return pnode1->sup>pnode2->sup; });
	int index = 0;//来记录id_index_map的index
	for (head_node* pnode : *head){
		id_sup_map->insert(make_pair(pnode->id, pnode->sup));
		id_head_map->insert(make_pair(pnode->id, pnode));
		id_index_map->insert(make_pair(pnode->id, index));
		index++;
	}
}
void FPtree::sort_head(const vector<Transation>& trans){
	//对于每个item，都找一遍当前头表，如果找到一样的，则sup++，否则新建一个。最后再对head进行sort
	//待优化，hash、heap
	vector<head_node*>* head = get_head();
	for (Transation t : trans){
		int* cur_items = t.get_items();
		for (unsigned i = 0; i < t.get_count(); i++){
			my_equal me;
			me.id = cur_items[i];
			vector<head_node*>::iterator j = find_if(head->begin(), head->end(), me);
			if (j != head->end())	(*j)->sup++;
			else{
				//head_node node{ cur_items[i], 0, 0 };
				head_node* pnode = new head_node(cur_items[i]);
				head->push_back(pnode);
			}
		}
	}
	//删掉小于最小支持度的head节点
	head->erase(remove_if(head->begin(), head->end(), [=](const head_node* n)->bool{return n->sup < get_min_sup(); }),head->end());
	//对head节点排序
	sort(head->begin(), head->end(), [=](head_node* pnode1, head_node* pnode2)->bool{return pnode1->sup>pnode2->sup; });
	int index = 0;//来记录id_index_map的index
	for (head_node* pnode : *head){
		id_sup_map->insert(make_pair(pnode->id, pnode->sup));
		id_head_map->insert(make_pair(pnode->id, pnode));
		id_index_map->insert(make_pair(pnode->id, index));
		index++;
	}

}

void FPtree::sort_trans(Transation& tran){
	int* items = tran.get_items();
	unsigned count = tran.get_count();
	unordered_map<int, unsigned>* map = get_map();
	unordered_map<int, int>* index_map = get_id_index_map();
	//对items进行sup的降序排列，如果map中没找到id（达不到最小支持度），就创建一个pair调用默认构造函数
	sort(&items[0], &(items[count]), [=](int a, int b)->bool{return (*index_map)[a] < (*index_map)[b]; });
	unsigned i = 0;
	//找到小于最小支持度的开始位置
	for (; i < count && (*map)[items[i]] >= min_sup; i++);
	//删除小于最小支持度的id
	tran.mod_count(i);
}


//输入已经排好序的事物
void FPtree::processTrans(Transation& tran, Node* node){
	unsigned tran_count = tran.get_count();
	if (tran_count == 0)	return;
	int* items = tran.get_items();
	//当前的根节点的子节点
	unordered_map<int, Node*>* children_map = node->getChildren();
	unordered_map<int, head_node*>* id_head_map = get_id_head_map();
	if (tran_count != 0){
		
		unordered_map<int,Node*>::iterator i = children_map->find(items[0]);
		if (i != children_map->end()){
			Node* inode = i->second;//node*
			inode->add_count();
			tran.go();
			processTrans(tran, inode);
			
		}
		else{
			
			Node* new_node = new Node(items[0], node);
			do{
				Node dummy(id_head_map->find(items[0])->second->node_link);
				if (dummy.get_next() == 0){
					id_head_map->find(items[0])->second->node_link = new_node;
					break;
				}
				Node* now = &dummy;
				while (now->get_next() != 0){
					now = now->get_next();
				}
				now->mod_next(new_node);
			} while (0);

			new_node->add_count();
			children_map->insert(make_pair(items[0], new_node));
			tran.go();
			processTrans(tran, new_node);

		}
	}

}

void FPtree::processTrans(Transation& tran, unsigned times,Node* node){
	unsigned tran_count = tran.get_count();
	if (tran_count == 0)	return;
	int* items = tran.get_items();
	//当前的根节点的子节点
	unordered_map<int, Node*>* children_map = node->getChildren();
	unordered_map<int, head_node*>* id_head_map = get_id_head_map();
	if (tran_count != 0){
		if (id_head_map->find(items[0]) == id_head_map->end())	return;
		unordered_map<int, Node*>::iterator i = children_map->find(items[0]);
		if (i != children_map->end()){
			Node* inode = i->second;//node*
			inode->add_count(times);
			tran.go();
			processTrans(tran, times,inode);

		}
		else{

			Node* new_node = new Node(items[0], node);
			do{
				Node dummy(id_head_map->find(items[0])->second->node_link);
				if (dummy.get_next() == 0){
					id_head_map->find(items[0])->second->node_link = new_node;
					break;
				}
				Node* now = &dummy;
				while (now->get_next() != 0){
					now = now->get_next();
				}
				now->mod_next(new_node);
			} while (0);

			new_node->add_count(times);
			children_map->insert(make_pair(items[0], new_node));
			tran.go();
			processTrans(tran, times,new_node);

		}
	}

}

bool FPtree::isEmpty(){

	return root->getChildren() == 0 || root->getChildren()->size() == 0;
}


void FPtree::construction(const vector<Transation>& trans){
	if (trans.size() == 0)	return;
	sort_head(trans);

	for (Transation tran : trans){
		if (tran.get_count() == 0)	continue;
		sort_trans(tran);
		processTrans(tran, root);
	}
}


void FPtree::outputTree(){
	for (head_node* node : *head){
		Node dummy(node->node_link);
		Node* cur = &dummy;
		while (cur != nullptr){
			cout << " |id:| " << cur->getid() << " |count:| " << cur->getsup() << "----->";
			cur = cur->get_next();
		}
		cout << endl;
	}
}

bool FPtree::check_single(){
	Node* now = root;
	while (now != nullptr){
		if (now->getChildren()->size() > 1)	return false;
		if (now->getChildren()&&now->getChildren()->size() == 0)	break;
		now = now->getChildren()->begin()->second;
	}
	return true;

}



