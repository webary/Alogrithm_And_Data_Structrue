/*
求两个链表的交集和并集.例如：
a链表的值为：10 20 30 40 50 60
b链表的值为：10 15 30 50 55 60 75 98
交集为：10 30 50 60
并集为：10 15 2030 40 50 55 60 75 98
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef int datatype;
typedef struct ListNode {
    datatype data;
    ListNode *next;
} ListNode, *linklist;

void print(linklist head)
{
	if(head==NULL){
		puts("链表为空！");
		return;
	}
    puts("该链表为：");
    linklist p=head->next;
    while(p) {
        printf("%-d -> ",p->data);
        p=p->next;
    }
    printf("NULL\n");
}
linklist creat()
{
    linklist head,s,p;
    datatype x;
    head=p=(linklist)malloc(sizeof(ListNode));
    printf("请输入链表数据，以0为结束标志：\n");
    scanf("%d",&x);
    while(x) {
        s=(linklist)malloc(sizeof(ListNode));
        s->data=x;
        p->next=s;
        p=s;
        scanf("%d",&x);
    }
    p->next=NULL;
    return head;
}
linklist jiaoji(linklist head1,linklist head2)//求两个集合的交集
{
    linklist p,q,head,r,pre,s;
    head=r=(linklist)malloc(sizeof(ListNode));
    p=head1->next;
    while(p) {
        q=head2->next;
        while(q) {
            if(p->data==q->data) {
                s=(linklist)malloc(sizeof(ListNode));
                s->data=p->data;
                r->next=s;
                r=s;
                break;
            }
            q=q->next;
        }
        p=p->next;
    }
    r->next=NULL;
    return head;
}
linklist bingji(linklist head1,linklist head2)
{
    linklist p,q,head,r,pre,s;
    datatype flag;
    head=r=(linklist)malloc(sizeof(ListNode));
    p=head1->next;
    while(p) {
        flag=0;
        q=head2->next;
        while(q) {
            if(p->data==q->data) {
                flag=1;
                break;
            }
            q=q->next;
        }
        if(flag==0) {
            s=(linklist)malloc(sizeof(ListNode));
            s->data=p->data;
            r->next=s;
            r=s;
        }
        p=p->next;
    }
    r->next=head2->next;
    return head;
}

//返回一个结点类型：值表示公共结点个数,指针表示第一个公共结点
ListNode findFirstCommonNode(ListNode* pHead1, ListNode* pHead2)
{
	if(pHead1==NULL || pHead2==NULL)
		return {0};
	ListNode *pFast = pHead1, *pSlow = pHead2, *pSync = NULL, *pSlowLast = NULL;
	while(pFast->next!=NULL && pSlow->next!=NULL){
		pFast = pFast->next;
		pSlow = pSlow->next;
	}
	//某个链表到达了尾结点
	if(pFast->next==NULL){	//链表1更短
		pSlowLast = pFast;	//记录短链表的最后一个结点
		pSync = pSlow;
		pFast = pHead2;		//记录长链表
		pSlow = pHead1;		//记录短链表
	}else{
		pSlowLast = pSlow;	//记录短链表的最后一个结点
		pSync = pFast;
		pFast = pHead1;		//记录长链表
		pSlow = pHead2;		//记录短链表
	}
	while(pSync->next!=NULL){
		pSync = pSync->next;
		pFast = pFast->next;
	}
	if(pSync!=pSlowLast)	//最后一个结点不同,则没有公共结点
		return {0};
	while(pFast!=pSlow){
		pFast = pFast->next;
		pSlow = pSlow->next;
	}//这里一定已经找到公共结点
	unsigned length = 1;	//记录公共结点长度
	while(pSlow!=pSlowLast){
		pSlow = pSlow->next;
		++length;
	}
	return {length,pFast};
}
int main()
{
    linklist head1,head2,head3;
    head1=creat();
    print(head1);
    head2=creat();
    print(head2);
    head2->next = head1->next;
    ListNode node = findFirstCommonNode(head1,head2);
    printf("公共结点个数为:%d\n",node.data);
    print(node.next);
    //head3=bingji(head1,head2);
    //print(head3);
    return 0;
}
