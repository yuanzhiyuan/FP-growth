#include "Transation.h"
#include "FP-tree.h"
#include <vector>

#include <set>
#include <iostream>
#include <algorithm>


using namespace std;


void FPtree::sort_head(const vector<Transation>& trans){
	//����ÿ��item������һ�鵱ǰͷ������ҵ�һ���ģ���sup++�������½�һ��������ٶ�head����sort
	//���Ż���hash��heap
	vector<head_node*>* head = get_head();
	for (Transation t : trans){
		int* cur_items = t.get_items();
		for (unsigned i = 0; i < t.get_count(); i++){
			id_equal.id = cur_items[i];
			vector<head_node*>::iterator j = find_if(head->begin(), head->end(), id_equal);
			if (j != head->end())	(*j)->sup++;
			else{
				//head_node node{ cur_items[i], 0, 0 };
				head_node* pnode = new head_node(cur_items[i]);
				head->push_back(pnode);
			}
		}
	}
	//ɾ��С����С֧�ֶȵ�head�ڵ�
	head->erase(remove_if(head->begin(), head->end(), [=](const head_node* n)->bool{return n->sup < get_min_sup(); }),head->end());
	//��head�ڵ�����
	sort(head->begin(), head->end(), [=](head_node* pnode1, head_node* pnode2)->bool{return pnode1->sup>pnode2->sup; });
	int index = 0;//����¼id_index_map��index
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
	//��items����sup�Ľ������У����map��û�ҵ�id���ﲻ����С֧�ֶȣ����ʹ���һ��pair����Ĭ�Ϲ��캯��
	sort(&items[0], &(items[count]), [=](int a, int b)->bool{return (*index_map)[a] < (*index_map)[b]; });
	unsigned i = 0;
	//�ҵ�С����С֧�ֶȵĿ�ʼλ��
	for (; i < count && (*map)[items[i]] >= min_sup; i++);
	//ɾ��С����С֧�ֶȵ�id
	tran.mod_count(i);
}


//�����Ѿ��ź��������
void FPtree::processTrans(Transation& tran, Node* node){
	unsigned tran_count = tran.get_count();
	if (tran_count == 0)	return;
	int* items = tran.get_items();
	//��ǰ�ĸ��ڵ���ӽڵ�
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


int main(){
	FPtree tree(1);
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
	//cout << "hehe";
	tree.outputTree();

	system("pause");
	return 0;
}