#include<iostream>
#include<stack>   //STL
#include<queue>
using namespace std;
//124##57##8##3#6##
class Tree {
    char data;
    Tree *leftChild;
    Tree *rightChild;
public:
    Tree()
    {
        leftChild = rightChild = NULL;
    }
    ~Tree() {};

    static void CreateTree(Tree* &node);
    static void destroyTree(Tree* &node);
    //成员函数
    //递归的遍历二叉树
    void PreOrderVisit(Tree *T);
    void InOrderVisit(Tree *T);
    void LastOrderVisit(Tree *T);
    void LevelOrderVisit();
    //非递归的调用二叉树
    void NoRecursivePreVisit();
    void NoRecursiveInVisit();
    void NoRecursiveLastVisit();
    //计算树的深度
    static int getDepth(const Tree *T);
    //找给定结点值的父节点
    static char findParent(const Tree *bt, char x) {
        if(bt==NULL || bt->leftChild==NULL && bt->rightChild==NULL)//找到空结点或叶节点
            return 0;
        if(bt->leftChild && bt->leftChild->data==x
                || bt->rightChild && bt->rightChild->data==x)
            return bt->data;//如果当前结点就是它的父，直接返回
        char pa = findParent(bt->leftChild,x);//找左子树
        if(pa==0) //如果左子树没找到，再去右子树找
            pa = findParent(bt->rightChild,x);
        return pa;
    }
    //显示父节点
    static void showParent(const Tree *bt, char x) {
    	char pa = findParent(bt,x);
        if(pa==0)
            cout<<"node "<<x<<" have no parent!"<<endl;
        else
            cout<<"the parent of "<<x<<" is "<<pa<<endl;
    }
};

//构造树
void Tree::CreateTree(Tree* &node)
{
    char temp;
    static unsigned cur_size = 0;
    if(cur_size==0)
        cout<<"输入各节点的数据(#表示空)："<<endl;
    cin>>temp;
    if(temp=='#') {
        node = NULL;
    } else {
        node = new Tree;
        node->data = temp;
        cur_size++;
        CreateTree(node->leftChild);
        CreateTree(node->rightChild);
    }
}

void Tree::destroyTree(Tree* &node)
{
    if(node->leftChild!=NULL)
        destroyTree(node->leftChild);
    if(node->rightChild!=NULL)
        destroyTree(node->rightChild);
    delete node;
    node = NULL;
}
//先序遍历树
void Tree::PreOrderVisit(Tree *T)
{
    if(T!=NULL) {
        cout<<T->data<<"  ";
        PreOrderVisit(T->leftChild);
        PreOrderVisit(T->rightChild);
    }
}
//中序遍历树
void Tree::InOrderVisit(Tree *T)
{
    if(T!=NULL) {
        InOrderVisit(T->leftChild);
        cout<<T->data<<"  ";
        InOrderVisit(T->rightChild);
    }
}
//后序遍历树
void Tree::LastOrderVisit(Tree *T)
{
    if(T!=NULL) {
        LastOrderVisit(T->leftChild);
        LastOrderVisit(T->rightChild);
        cout<<T->data<<"  ";
    }

}
//层次遍历——非递归
void Tree::LevelOrderVisit()
{
    queue<Tree *>Q;
    Q.push(this);
    Tree *temp=NULL;
    while(!Q.empty()) {
        temp=Q.front();
        cout<<temp->data<<"  ";
        Q.pop();
        if(temp->leftChild)
            Q.push(temp->leftChild);
        if(temp->rightChild)
            Q.push(temp->rightChild);
    }
}
//非递归先序遍历
void Tree::NoRecursivePreVisit()
{
    stack<Tree *>S;  //用来保存树节点的栈
    Tree *p = this;
    while(!S.empty() || p!=NULL) {
        if(p!=NULL) { //p非空
            S.push(p);
            cout<<p->data<<"  ";
            p = p->leftChild;
        } else {
            p = S.top();
            S.pop();
            p = p->rightChild;
        }
    }
}
//非递归中序遍历
void Tree::NoRecursiveInVisit()
{
    stack<Tree *>S;  //用来保存树节点的栈
    Tree *p = this;
    while(!S.empty() || p!=NULL) {
        if(p!=NULL) { //p非空
            S.push(p);
            p = p->leftChild;
        } else {
            p = S.top();
            S.pop();
            cout<<p->data<<"  ";
            p = p->rightChild;
        }
    }
}
//非递归后序遍历
void Tree::NoRecursiveLastVisit()
{
    stack<Tree *>S;
    Tree *p = this;
    Tree *p_visited = NULL;
    while(!S.empty() || p!=NULL) {
        while(p!=NULL) {
            S.push(p);
            p = p->leftChild;
        }
        p=S.top();
        if(p->rightChild==NULL || p->rightChild==p_visited) {
            cout<<p->data<<"  ";
            p_visited = p;
            p = NULL;
            S.pop();
        } else
            p=p->rightChild;
    }
    cout<<endl;
}
int Tree::getDepth(const Tree *T)
{
    if(T==NULL)
        return 0;
    return 1+max(getDepth(T->leftChild),getDepth(T->rightChild));
}
//	124##57##8##3#6##
int main()
{
    Tree* mytree = NULL;
    while(1) {
        Tree::CreateTree(mytree);
        cout<<"树的深度是："<<Tree::getDepth(mytree)<<endl;
        cout<<"先序遍历"<<endl;
        mytree->PreOrderVisit(mytree);
        cout<<endl;
        cout<<"中序遍历"<<endl;
        mytree->InOrderVisit(mytree);
        cout<<endl;
        cout<<"后序遍历"<<endl;
        mytree->LastOrderVisit(mytree);
        cout<<endl;
        cout<<"层次遍历"<<endl;
        mytree->LevelOrderVisit();
        cout<<endl<<endl;
        cout<<"非递归先序遍历"<<endl;
        mytree->NoRecursivePreVisit();
        cout<<endl;
        cout<<"非递归中序遍历"<<endl;
        mytree->NoRecursiveInVisit();
        cout<<endl;
        cout<<"非递归后序遍历"<<endl;
        mytree->NoRecursiveLastVisit();
        for(char c='1'; c<'9'; c++)
            Tree::showParent(mytree,c);

        Tree::destroyTree(mytree);
        cout<<endl;
    }
    cin.get();
    return 0;
}
