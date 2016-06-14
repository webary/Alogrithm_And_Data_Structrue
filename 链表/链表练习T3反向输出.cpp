#include "list.h"
#include <string.h>
//存入数组之后反向输出：时间O(n),空间O(n)
void reversedPrint1(const ListNode* head, bool noHead=1)
{
    if(head==NULL)
        return;
    int length = getLength(head,noHead) ,i; //获取结点个数
    if(length==0) {
        puts("当前木有任何结点可以输出喔~");
        return;
    }
    ElemType* nodes = (ElemType*)malloc(sizeof(ElemType)*length);
    const ListNode* p = noHead ? head : head->next;
    for(i=0; i<length; ++i, p=p->next) //把结点按顺序存入数组中
        nodes[i] = p->data;
    for(i=length-1; i>=0; --i) //从数组中反向输出结点的值
        printf("%-3d ",nodes[i]);
    puts("");
    free(nodes);  //释放申请的空间
}
//用递归函数方式反向输出：时间O(n),空间O(1)
void recursivePrint(const ListNode* pNode)
{
    if(pNode->next)
        recursivePrint(pNode->next);
    printf("%-3d ",pNode->data);
}
void reversedPrint2(const ListNode* head, bool noHead=1)
{
    if(head==NULL)
        return;
    int length = getLength(head,noHead) ,i;
    if(length==0) {
        puts("当前木有任何结点可以输出喔~");
        return;
    }
    if(!noHead) //有头节点的情况特殊处理
        head = head->next;
    recursivePrint(head); //递归输出每个结点的值
    puts("");
}
//先反转链表再依次输出,时间O(n),空间O(1),但破坏原结构,不推荐

//第一遍遍历找到结点最小值,第二遍删除最小值的结点
void delMinNode(ListNode* &head, bool noHead=1)
{
    if(head==NULL)
        return;
    int length = getLength(head,noHead);
    if(length==0) //没有结点直接返回
        return;
    else if(length==1) { //只有一个结点
        ListNode* &firstNode = noHead ? head : head->next;
        free(firstNode); //释放这个结点空间
        firstNode = NULL;//头节点指针域置空或头指针置空
        return;
    }
    ListNode *p = noHead ? head : head->next, *q;
    ElemType minData = p->data; //防止删除了minNode之后又要使用
    int minCount = 1; //保存当前最小结点的个数,以及最小值的结点
    for(p=p->next; p!=NULL; p=p->next) {
        if(p->data < minData) { //找到更小值的结点
            minData = p->data;
            minCount = 1;  //重新计数
        } else if(p->data == minData)
            ++minCount;    //最小结点个数累加
    }
    //前面的判断已经能保证至少包含两个结点!
    if(noHead) { //没有头节点
        while(head->data==minData) { //第一个结点需要删除
            p = head;
            head = head->next;
            free(p);
            --minCount;
        }
    }
    p = head;
    while(minCount>0 && p!=NULL) { //还有结点的值为最小值且p不需要删除
        if(p->next->data == minData) {
            q = p->next;
            p->next = p->next->next; //指向下一个结点的下一个结点
            free(q);
            --minCount;
        }else
			p = p->next;
    }
}

void delAbsEqualNode(ListNode *head, int maxValue)
{
	if(head==NULL)
		return ;
	bool *saved = (bool*)malloc(sizeof(bool)*(maxValue+1));//new bool[maxValue+1](0)
	memset(saved,0,sizeof(bool)*(maxValue+1)); //全部初始化为0
	while(head->next!=NULL) {
		if(saved[abs(head->next->data)]==0) {//等于0表示前面没有存储过该值
			saved[abs(head->next->data)] = 1;
			head = head->next;
		}else {  //已存储过该值则需要删除这个结点
			ListNode *nextNode = head->next->next;
			free(head->next);
			head->next = nextNode;
		}
	}
	free(saved); //delete[] saved;
}
int main()
{
    bool noHeadNode = 0;
    ListNode* head = NULL;
    createList_head(head,noHeadNode);
    showList(head,"链表结构如下:",noHeadNode);
    printf("链表长度为: %d\n",getLength(head,noHeadNode));

	puts("逆向输出为:");
    reversedPrint1(head,noHeadNode);
    reversedPrint2(head,noHeadNode);
    delMinNode(head,noHeadNode);
    showList(head,"删除最小值后链表结构如下:",noHeadNode);
    delAbsEqualNode(head,5);
    showList(head,"删除相同绝对值结点后链表结构如下:",noHeadNode);
    return 0;
}
