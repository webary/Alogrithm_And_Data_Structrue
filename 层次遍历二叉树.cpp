#include<iostream>
#include<vector>
#include<deque>
using namespace std;

#define PRINT(x) cout<<endl<<#x<<":"<<endl;x;

typedef struct tree_node_s {
	char data;
	struct tree_node_s *lchild;
	struct tree_node_s *rchild;
}tree_node_t, *Tree;

void create_tree(Tree *T) {
	char c;
	cin>>c;
	if (c == '#') {
		*T = NULL;
	} else {
		*T = new tree_node_t;
		(*T)->data = c;
		create_tree(&(*T)->lchild);
		create_tree(&(*T)->rchild);
	}
}

void print_tree(Tree T) {
	if (T) {
		cout << T->data << " ";
		print_tree(T->lchild);
		print_tree(T->rchild);
	}
}
//递归遍历
int print_at_level(const Tree T, int level) {
	if (!T || level < 0)
		return 0;
	if (0 == level) {
		cout << T->data << " ";
		return 1;
	}
	return print_at_level(T->lchild, level - 1) + print_at_level(T->rchild, level - 1);
}

void print_by_level_1(const Tree T) {
	for (int i = 0; ; i++) {
		if (!print_at_level(T, i))
			break;
		cout<<endl;
	}
	cout << endl;
}
//用两个队列实现，空间复杂度有点高
void print_by_level_2(const Tree T) {
	deque<tree_node_t*> q_first, q_second;
	q_first.push_back(T);
	while(!q_first.empty()) {
		while (!q_first.empty()) {
			tree_node_t *temp = q_first.front();
			q_first.pop_front();
			cout << temp->data << " ";
			if (temp->lchild)
				q_second.push_back(temp->lchild);
			if (temp->rchild)
				q_second.push_back(temp->rchild);
		}
		cout << endl;
		q_first.swap(q_second);
	}
}
//设置双指针，一个指向访问当层开始的节点，一个指向访问当层结束节点的下一个位置
void print_by_level_3(const Tree T) {
	vector<tree_node_t*> vec;
	vec.push_back(T);
	unsigned cur = 0;
	unsigned end = 1;
	while (cur < vec.size()) {
		end = vec.size();
		while (cur < end) {
			cout << vec[cur]->data << " ";
			if (vec[cur]->lchild)
				vec.push_back(vec[cur]->lchild);
			if (vec[cur]->rchild)
				vec.push_back(vec[cur]->rchild);
			cur++;
		}
		cout << endl;
	}
}
//	124##57##8##3#6##
int main(int argc, char *argv[]) {
	Tree T = NULL;
	create_tree(&T);
	print_tree(T);
	cout << endl;
	PRINT(print_by_level_1(T));
	PRINT(print_by_level_2(T));
	PRINT(print_by_level_3(T));
	cin.get();
	cin.get();
	return 0;
}
/*				   1
		  2		     	  3
	4	      5			      6
			7   8
*/
