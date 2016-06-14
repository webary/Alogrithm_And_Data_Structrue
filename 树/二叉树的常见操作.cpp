#include<stdio.h>
#include<iostream>
#include<stack>   //STL
#include<queue>   //STL
using namespace std;
//124##57##8##3#6##
class BiTree {
    typedef char ElemType;
    ElemType data;
    BiTree *left;
    BiTree *right;
public:
    BiTree()
    {
        left = right = NULL;
    }
    ~BiTree() {};

    static void createTree(BiTree* &node);
    static void destroyTree(BiTree* &node);
    //递归的遍历二叉树各结点
    void preOrderVisit(BiTree *T);
    void inOrderVisit(BiTree *T);
    void lastOrderVisit(BiTree *T);
    //非递归的遍历二叉树各结点
    void levelOrderVisit();
    void noRecursivePreVisit();
    void noRecursiveInVisit();
    void noRecursiveLastVisit();

    //计算树的深度
    static int getDepth(const BiTree *T)
    {
        return T == NULL ? 0 : 1 + max(getDepth(T->left), getDepth(T->right));
    }
    //计算树的带权路径长度
    static int getWPL(const BiTree *head, int depth = 0)
    {
        if (head == NULL) {
            return 0;
        }
        if (head->left == NULL && head->right == NULL) {
            return depth * head->data;    //如果是char类型*(head->data-48)
        }
        return getWPL(head->left, depth + 1) + getWPL(head->right, depth + 1);
    }
    //求树的第K层节点个数
    static int getLevelNode(const BiTree *T, int k, int level = 1)
    {
        if (T == NULL) {
            return 0;
        }
        if (level == k) {
            return 1;
        }
        return getLevelNode(T->left, k, level + 1) + getLevelNode(T->right, k, level + 1);
    }
    //求树的第K层叶子节点个数
    static int getLevelLeaf(const BiTree *T, int k, int level = 1)
    {
        if (T == NULL) {
            return 0;
        }
        if (level == k && NULL == T->left && NULL == T->right) {
            return 1;
        }
        if (level >= k) { //如果这个第K层的结点不是叶结点，就不需要看它的孩子
            return 0;
        }
        return getLevelLeaf(T->left, k, level + 1) + getLevelLeaf(T->right, k, level + 1);
    }
    //找给定结点值的父节点
    static ElemType findParent(const BiTree *T, ElemType x)
    {
        if (T == NULL || T->left == NULL && T->right == NULL) {
            return 0;    // 找到空结点或叶节点
        }
        if (T->left && T->left->data == x || T->right && T->right->data == x) {
            return T->data;    // 如果当前结点就是它的父，直接返回
        }
        ElemType pa = findParent(T->left, x); // 找左子树
        return pa != 0 ? pa : findParent(T->right, x); //左子树没有再找右子树
    }
    //显示父节点
    static void showParent(const BiTree *T, ElemType x)
    {
        ElemType pa = findParent(T, x);
        if (pa == 0) {
            cout << "node " << x << " have no parent!" << endl;
        } else {
            cout << "the parent of " << x << " is " << pa << endl;
        }
    }
    //判断二叉树是否为平衡二叉树
    static bool isBalanced(BiTree *T, int *pDepth = 0)
    {
        if (NULL == T) {
            if (0 != pDepth) {
                *pDepth = 0;
            }
            return 1;
        }
        int depthLeft = 0, depthRight = 0;
        if (isBalanced(T->left, &depthLeft) && isBalanced(T->right, &depthRight)) {
            int maxD = max(depthLeft, depthRight), minD = min(depthLeft, depthRight);
            if (0 != pDepth) {
                *pDepth = maxD + 1;
            }
            return maxD - minD < 2; //左右均平衡则看深度之差
        }
        return 0; //左右子树任意一个不平衡则不平衡
    }
    //求根到给定值结点的路径
    static void root2Node(BiTree *T, ElemType x)
    {
        stack<BiTree *>S;
        BiTree *p = T;
        BiTree *p_visited = NULL;
        while (!S.empty() || p != NULL) {
            while (p != NULL) {
                S.push(p);
                p = p->left;
            }
            p = S.top();
            if (p->right == NULL || p->right == p_visited) {
                if (p->data == x) {
                    while (!S.empty()) {
                        cout << S.top()->data << " ";
                        S.pop();
                    }
                    cout << endl;
                    return ;
                }
                p_visited = p;
                p = NULL;
                S.pop();
            } else {
                p = p->right;
            }
        }
    }
};

//构造树
void BiTree::createTree(BiTree* &node)
{
    ElemType temp;
    static unsigned cur_size = 0;
    if (cur_size == 0) {
        cout << "输入各节点的数据(#表示空)：" << endl;
    }
    cin >> temp;
    if (temp == '#' || temp == -1) {
        node = NULL;
    } else {
        node = new BiTree;
        node->data = temp;
        cur_size++;
        createTree(node->left);
        createTree(node->right);
    }
}

void BiTree::destroyTree(BiTree* &node)
{
    if (node->left != NULL) {
        destroyTree(node->left);
    }
    if (node->right != NULL) {
        destroyTree(node->right);
    }
    delete node;
    node = NULL;
}
//先序遍历树
void BiTree::preOrderVisit(BiTree *T)
{
    if (T != NULL) {
        cout << T->data << "  ";
        preOrderVisit(T->left);
        preOrderVisit(T->right);
    }
}
//中序遍历树
void BiTree::inOrderVisit(BiTree *T)
{
    if (T != NULL) {
        inOrderVisit(T->left);
        cout << T->data << "  ";
        inOrderVisit(T->right);
    }
}
//后序遍历树
void BiTree::lastOrderVisit(BiTree *T)
{
    if (T != NULL) {
        lastOrderVisit(T->left);
        lastOrderVisit(T->right);
        cout << T->data << "  ";
    }
}
//层次遍历——非递归
void BiTree::levelOrderVisit()
{
    queue<BiTree *>Q;
    Q.push(this);
    BiTree *temp = NULL;
    while (!Q.empty()) {
        temp = Q.front();
        cout << temp->data << "  ";
        Q.pop();
        if (temp->left) {
            Q.push(temp->left);
        }
        if (temp->right) {
            Q.push(temp->right);
        }
    }
}
//非递归先序遍历
void BiTree::noRecursivePreVisit()
{
    stack<BiTree *>S;  //用来保存树节点的栈
    BiTree *p = this;
    while (!S.empty() || p != NULL) {
        if (p != NULL) { //p非空
            S.push(p);
            cout << p->data << "  ";
            p = p->left;
        } else {
            p = S.top();
            S.pop();
            p = p->right;
        }
    }
}
//非递归中序遍历
void BiTree::noRecursiveInVisit()
{
    stack<BiTree *>S;  //用来保存树节点的栈
    BiTree *p = this;
    while (!S.empty() || p != NULL) {
        if (p != NULL) { //p非空
            S.push(p);
            p = p->left;
        } else {
            p = S.top();
            S.pop();
            cout << p->data << "  ";
            p = p->right;
        }
    }
}
//非递归后序遍历
void BiTree::noRecursiveLastVisit()
{
    stack<BiTree *>S;
    BiTree *p = this;
    BiTree *p_visited = NULL;
    while (!S.empty() || p != NULL) {
        while (p != NULL) {
            S.push(p);
            p = p->left;
        }
        p = S.top();
        if (p->right == NULL || p->right == p_visited) {
            cout << p->data << "  ";
            p_visited = p;
            p = NULL;
            S.pop();
        } else {
            p = p->right;
        }
    }
}
//  124##57##8##3#6##
int main()
{
    BiTree* mytree;
    BiTree::createTree(mytree);
    cout << "树的深度是：" << BiTree::getDepth(mytree) << endl;
    cout << "先序遍历" << endl;
    mytree->preOrderVisit(mytree);
    cout << endl;
    cout << "中序遍历" << endl;
    mytree->inOrderVisit(mytree);
    cout << endl;
    cout << "后序遍历" << endl;
    mytree->lastOrderVisit(mytree);
    cout << endl;
    cout << "层次遍历" << endl;
    mytree->levelOrderVisit();
    cout << endl << endl;
    cout << "非递归先序遍历" << endl;
    mytree->noRecursivePreVisit();
    cout << endl;
    cout << "非递归中序遍历" << endl;
    mytree->noRecursiveInVisit();
    cout << endl;
    cout << "非递归后序遍历" << endl;
    mytree->noRecursiveLastVisit();

    cout << "树的带权路径长度为: " << BiTree::getWPL(mytree) << endl;
    for (int i = 0; i < 5; ++i) {
        cout << "第" << i << "层节点数为: " << BiTree::getLevelNode(mytree, i)
             << endl;
        cout << "第" << i << "层叶子节点数为: " << BiTree::getLevelLeaf(mytree, i)
             << endl;
    }
    BiTree::root2Node(mytree, '7');
    cout << (BiTree::isBalanced(mytree) ? "平衡" : "不平衡") << endl;
    for (char c = '1'; c < '9'; c++) {
        BiTree::showParent(mytree, c);
    }
    BiTree::destroyTree(mytree);
    cout << endl;
    return 0;
}
