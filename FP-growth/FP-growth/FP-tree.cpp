#include "FP-tree.h"
#include <vector>
#include <set>
#include <iostream>
#include <algorithm>
using namespace std;


void FPtree::sort_head(const vector<Transation>& trans){
	//����ÿ��item������һ�鵱ǰͷ������ҵ�һ���ģ���sup++�������½�һ��������ٶ�head����sort
	//���Ż���hash��heap
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
	//ɾ��С����С֧�ֶȵ�head�ڵ�
	head.erase(remove_if(head.begin(), head.end(), [=](const head_node& n)->bool{return n.sup < get_min_sup(); }),head.end());
	//��head�ڵ�����
	sort(head.begin(), head.end());

}

