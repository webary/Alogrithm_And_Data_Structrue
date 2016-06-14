#include "list.h"
#include "string.h"
#include<iostream>
#include<stack>
using namespace std;
//P37-T5:将带头结点的单链表原地逆置.时间O(n),空间O(1)
ListNode* reverseList(ListNode* &head)
{
    ListNode *prev_node=NULL, *cur_node=head->next, *next_node=NULL;
    while(cur_node!=NULL) {
        next_node = cur_node->next;	//保存下一结点
        cur_node->next = prev_node;	//修改下一结点
        prev_node = cur_node;		//保存当前结点
        cur_node = next_node;		//修改当前结点
    }
    head->next = prev_node;
    return head;
}
//使用头插法的思想,对后面每个结点,插到第一个结点前面:O(n),O(1)
ListNode* reverseList2(ListNode* &head)
{
    ListNode *p = head->next, *q=NULL;
    head->next = NULL;
    while(p!=NULL) {
        q = p->next; //保存下一结点
        p->next = head->next; //把*p插到头节点后面第一个结点前
        head->next = p;
        p = q;
    }
}
//T8:找到两个链表的公共结点.让快指针先走几步再比较一趟:时间O(n),空间O(1)
ListNode* findCommonNode(ListNode *list1, ListNode *list2)
{
    unsigned len1 = getLength(list1), len2 = getLength(list2),i;
    ListNode *p = list1, *q = list2;
    for(; len1<len2; ++len1)
        q = q->next;
    for(; len2<len1; ++len2)
        p = p->next;
    while(p!=NULL && p!=q) {
        p = p->next;
        q = q->next;
    }
    return p;
}
//T8:找到两个链表的公共结点.链表1每个结点与链表2的结点比较:时间O(n^2),空间O(1)
ListNode* findCommonNode2(ListNode *list1, ListNode *list2)
{
    for (ListNode *p=list1; p!=NULL; p=p->next) //依次遍历链表1
        for (ListNode *q=list2; q!=NULL; q=q->next) //依次遍历链表2
            if ( p==q ) //如果两个结点地址相同则找到公共结点，返回
                return p;
    return NULL;
}
//T9:递增输出带头结点的链表中各结点的数据.
//每次找到链表中最小的元素输出:时间O(n^2),空间O(1)
void increasedPrint(ListNode *head)
{
    if(head==NULL || head->next==NULL)
        return;
    ElemType minData, lastMin=-99999999;
    int minCount, i;  //计数当前最小值结点的个数
    while(1) {
        ListNode *p = head->next;
        while(p!=NULL && p->data <= lastMin) //找到第一个当前可选的最小值
            p = p->next;
        if(p==NULL) //没找到说明都已经输出了,则退出循环
            break;
        minData = p->data; //暂且把当前结点值作为最小值
        minCount = 1;
        for(p=p->next; p!=NULL; p=p->next) { //对每个结点进行检查
            if(p->data > lastMin && p->data < minData) { //有更小的结点值
                minData = p->data;
                minCount = 1;
            } else if(p->data==minData)
                ++minCount;
        }
        lastMin = minData;
        for(i=0; i<minCount; ++i)
            printf("%d ",minData);
    }
    puts("");
}
//T12:在递增的链表中删除数值相同的元素
//如果连续两个结点值相同则删除后面那个结点:时间O(n),空间O(1)
void delEqualNode(ListNode *head, bool noHead=1)
{
    if(head==NULL || head->next==NULL) //防止无效参数
        return;
    ListNode *p = noHead ? head : head->next, *q = NULL;
    while(p->next != NULL) {
        q = p->next; //指向当前结点的下一个结点
        if(p->data == q->data) { //结点值相等,则删除结点*(p->next)
            p->next = q->next;
            free(q);
        } else  //不相等时才向后走一个结点
            p = q;
    }
}
//T17.判断带头结点的循环(Circle)双(Double)链表是否对称,如 1->2->3->2->1
//因为是循环双链表,所以只需要用两个指针同时移动和比较:时间O(n),空间O(1)
bool isSymmetry_CS(ListNode *head)
{
    if(getLength(head,0)<2) //不足两个结点
        return true;
    ListNode *p = head->next, *q = head->prior;
    for(; p->data == q->data; p=p->next, q=q->prior)
        if(p->next==q || p==q)
            return true;
    return false;
}
//拓展:判断单链表是否对称
//将链表的前[len/2]元素压入栈,然后一边出栈一边比较后面的元素:时间O(n),空间O(n)
bool isSymmetry(ListNode* head,bool noHead=1)
{
    unsigned len = getLength(head,noHead), i;
    if(len<2) //不足两个结点
        return true;
    stack<ElemType> sta;
    ListNode *p = noHead ? head : head->next;
    for(i=0; i<len/2; ++i, p=p->next)  //前一半元素入栈
        sta.push(p->data);
    if(len%2==1)   //结点个数为奇数时跳过中间那个结点
        p = p->next;
    for(; p!=NULL; p=p->next) {
        if(p->data != sta.top())  //出栈比较
            return false;
        sta.pop();
    }
    return true;
}
//2009真题-找带头结点的单链表中倒数第K个结点
//用双指针,一个先走K步,再同时走,直到快的先到表尾:时间O(n),空间O(1)
ListNode* getLastKthNode(ListNode *head, int k)
{
    if(head==NULL || k<=0)
        return NULL;
    ListNode *p1 = head, *p2 = head;
    for(int i=0; i<k && p2!=NULL; ++i)
        p2 = p2->next;
    if(p2==NULL)	//结点个数不足K
        return NULL;
    while(p2!=NULL) {
        p1 = p1->next;
        p2 = p2->next;
    }
    return p1;
}
//拓展:对带头节点的单链表进行排序
//使用插入排序的思想,对每个给定结点,找到它的合适位置:O(n^2),O(1)
void sortList(ListNode *head)
{
    if(head==NULL || head->next==NULL)
        return ;
    ListNode *p = head->next->next; //从第二个结点开始找正确的位置
    head->next->next = NULL;  //先假定只有一个结点是排好序的
    while(p!=NULL) {
        ListNode *q = p->next, *r; //保存下一结点
        for(r=head; r->next!=NULL && r->next->data < p->data; r=r->next)
            ;
        p->next = r->next; //把*p插到*r后面
        r->next = p;
        p = q;
    }
}
//拓展2:对不带头节点的单链表进行排序
void sortList_noHead(ListNode *&head) //参数需要用引用或者二级指针
{
    if(head==NULL || head->next==NULL)
        return ;
    ListNode *p = head->next;  //从第二个结点开始找正确的位置
    head->next = NULL;  //先假定只有一个结点是排好序的
    while(p!=NULL) {
        ListNode *q = p->next, *r; //保存下一结点
        if(head->data > p->data) { //如果待排结点值比第一个结点值小则插到前面
            p->next = head;
            head = p;
        } else {
            for(r=head; r->next!=NULL && r->next->data < p->data; r=r->next)
                ;
            p->next = r->next; //把*p插到*r后面
            r->next = p;
        }
        p = q;
    }
}
//求两个不带头节点的单链表的相似度(jaccard距离)
double getListSimilarity(ListNode *listA, ListNode *listB, int n)
{
    int *saved = new int[2*n+1];
    int commonNum = 0, totalNum = 0;
    memset(saved,0,sizeof(int)*(2*n+1));
    for(; listA!=NULL; listA=listA->next)
        saved[n + listA->data] = 1;
    for(; listB!=NULL; listB=listB->next)
        if(saved[n + listB->data] == 0) //A中未包含该元素
            saved[n + listB->data] = 1;
        else if(saved[n + listB->data] == 1) {//A中包含该元素
            ++saved[n + listB->data];
            ++commonNum;  //公共元素(交集中元素)个数加一
        }
    for(int i=2*n; i>=0; --i)  //统计并集中元素个数
        if(saved[i]!=0)
            ++totalNum;
    delete[] saved;
    return (double)commonNum / totalNum;
}
//将一个不带头结点的链表原地分割成两部分，一部分小于等于0，另一部分大于0
void cutListByZero(ListNode *head, ListNode *&part1, ListNode *&part2)
{
    if(head==NULL)
        return ;
    ListNode *p = head, *part1End, *part2End; //两个部分的尾结点指针
    if(p->data <=0) {  //第一个结点属于第一部分
        part1 = part1End = p;  //分别找到第一部分和第二部分的第一个结点
        while(p!=NULL && p->data <=0) {
            part1End = p;
            p = p->next;
        }
        part2 = part2End = p;
    } else {  //第一个结点属于第二部分
        part2 = part2End = p;  //分别找到第一部分和第二部分的第一个结点
        while(p!=NULL && p->data > 0) {
            part2End = p;
            p = p->next;
        }
        part1 = part1End = p;
    }
    if(p!=NULL)
        p = p->next;
    for(; p!=NULL; p=p->next) { //分别看后面每个结点属于哪一部分
        if(p->data <=0) {
            part1End->next = p; //连到第一部分
            part1End = part1End->next;
        } else {
            part2End->next = p; //连到第二部分
            part2End = part2End->next;
        }
    }
    if(part1End!=NULL)
        part1End->next = NULL;
    if(part2End!=NULL)
        part2End->next = NULL;
}
int main()
{
    bool noHeadNode = 1;
    ListNode* head = NULL , *head2;
    createList_head(head,noHeadNode);
    //createList_head(head2,noHeadNode);
    //cout<<getListSimilarity(head,head2,6)<<endl;
    ListNode * p1, *p2;
    cutListByZero(head,p1,p2);
    showList(p1,"第一部分");
    showList(p2,"第二部分");
    /*
    showList(head,"链表结构如下:",noHeadNode);
    printf("链表长度为: %d\n",getLength(head,noHeadNode));
    cout<<(isSymmetry(head,noHeadNode) ? "链表对称\n" : "链表不对称\n")<<endl;
    reverseList2(head);
    showList(head,"反转后链表结构如下:",noHeadNode);
    cout<<"倒数第二个结点为: "<<getLastKthNode(head,2)->data<<endl;
    sortList(head);
    showList(head,"排序后链表结构如下:",noHeadNode);
    delEqualNode(head,noHeadNode);
    showList(head,"删除相同值结点后链表结构如下:",noHeadNode);
    */
    return 0;
}
/*
//1. 栈的STL实现,假设此处存储int值
class stack {
public:
    void push(int e);	//e入栈
    int top();			//返回栈顶元素
    void pop();  		//出栈
    unsigned size();
    bool empty();
};
//用法
int main()
{
    stack<int> s;	//定义一个可以保存int值的栈
    s.push(111);	//111入栈
    s.push(222);	//222入栈
    int elem = s.top();	//保存栈顶元素
    cout<<elem<<endl;	//输出栈顶元素值:222
    s.pop();			//222出栈
    elem = s.top();		//保存栈顶元素
    cout<<elem<<endl;	//输出栈顶元素值:111
    s.pop();
}
//2. 书上自己定义的栈结构如下:
typedef int ElemType;
typedef struct {
    ElemType data[50];
    int top;
} SqStack;
//下面是几个常用操作
void InitStack(SqStack &S);
bool Push(SqStack &S, ElemType x);  //x入栈
bool Pop(SqStack &S, ElemType &x);  //出栈，栈顶保存到x
bool GetTop(SqStack S, ElemType &x);//取得栈顶元素,存到x
//用法
int main()
{
	SqStack sta;
	InitStack(sta);
	Push(sta,111);	//111入栈
	int x;
	GetTop(sta, x);	//获得栈顶元素的值,并没有出栈
	cout<<x<<endl;	//输出111
	Push(sta,222);	//222入栈
	Pop(sta,x);		//出栈，并保存栈顶元素值到x
	cout<<x<<endl;	//输出222
}
//3. 自己通过数组模拟栈
int main()
{
    ElemType MyStack[50];//定义一个可以容纳50个元素的栈
    int topIndex = -1;   //初始化栈顶索引位置
    MyStack[++topIndex] = 111; //111入栈
    int temp = MyStack[topIndex--]; //出栈，并用temp保存栈顶值
    cout<<temp<<endl;
}
*/
